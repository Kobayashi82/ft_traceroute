# Implementación de opciones `-i` y `-s` en traceroute

---

## Opción `-i` (interfaz de salida)

### Objetivo
Forzar que los paquetes salgan por una interfaz de red concreta, ignorando la tabla de rutas del kernel.

### Validación
Usar `if_nametoindex(iface)`. Si devuelve `0`, la interfaz no existe → error y salir.

### Qué aplicar y dónde

| Socket | Qué aplicar | Cómo |
|---|---|---|
| Envío (UDP/raw) | `SO_BINDTODEVICE` | `setsockopt()` con el nombre de la interfaz como string |
| Recepción (raw ICMP) | `SO_BINDTODEVICE` | `setsockopt()` con el nombre de la interfaz como string |

### Notas
- `SO_BINDTODEVICE` recibe el **nombre** de la interfaz, no el índice numérico.
- Requiere privilegios de **root**.
- El kernel sigue construyendo el header IP automáticamente. No hay que tocarlo.

---

## Opción `-s` (IP de origen)

### Objetivo
Especificar qué IP de la máquina se usará como origen en los paquetes enviados.

### Restricción de diseño
La IP indicada **debe pertenecer a una de las interfaces de la máquina**. Si no es así → error y salir. Esto evita tener que construir el header IP manualmente y cubre el 100% de los casos de uso legítimos.

### Validación
Recorrer las interfaces con `getifaddrs()` y comprobar que alguna tiene esa IP asignada. La comparación se hace en formato binario usando `inet_pton()` para convertir el string del usuario, y comparando con `sin_addr.s_addr` de cada interfaz.

### Qué aplicar y dónde

| Socket | Qué aplicar | Cómo |
|---|---|---|
| Envío (UDP/raw) | `bind()` con la IP indicada | Estructura `sockaddr_in` con la IP en formato binario |
| Recepción (raw ICMP) | **Nada** | No se aplica `bind()`. Filtrar manualmente por identificador/secuencia ICMP |

### Notas
- El `bind()` le indica al kernel qué IP usar como origen al construir el header IP.
- No se hace `bind()` en el socket de recepción porque en raw ICMP puede interferir con la recepción de paquetes.
- Las respuestas ICMP van dirigidas a la IP de origen, así que llegarán correctamente.

---

## Combinación `-i` y `-s` juntos

### Validación adicional
No basta con que la IP sea de la máquina. Hay que verificar que esa IP pertenece **específicamente a la interfaz indicada**. Si la IP es de otra interfaz → error y salir.

Esto se resuelve en la misma función de validación: al recorrer `getifaddrs()`, exigir que coincidan tanto el nombre de la interfaz como la IP.

### Qué aplicar y dónde

| Socket | Qué aplicar |
|---|---|
| Envío | `SO_BINDTODEVICE` con el nombre de la interfaz + `bind()` con la IP |
| Recepción | `SO_BINDTODEVICE` con el nombre de la interfaz |

### Orden de aplicación en el socket de envío
Primero `setsockopt` con `SO_BINDTODEVICE`, luego `bind()` con la IP.

---

## Resumen de funciones clave

| Función | Para qué |
|---|---|
| `if_nametoindex()` | Validar que una interfaz existe |
| `getifaddrs()` / `freeifaddrs()` | Recorrer interfaces y sus IPs asignadas |
| `inet_pton()` | Convertir IP string a binario para comparar |
| `setsockopt()` con `SO_BINDTODEVICE` | Vincular socket a una interfaz concreta |
| `bind()` con `sockaddr_in` | Establecer IP de origen en el socket de envío |

---

---

## Opción `-N` (sondas simultáneas)

### Objetivo
Controlar cuántas sondas pueden estar en vuelo al mismo tiempo, acelerando el trazado considerablemente.

### Valores
- **Por defecto:** 16
- **Mínimo:** 1 (comportamiento secuencial clásico)
- **Máximo:** no hay límite formal, pero valores altos pueden provocar que routers throttleen las respuestas ICMP y se pierdan

### Concepto clave
Es una ventana deslizante. No piensa en saltos, piensa en sondas individuales. Mientras el número de sondas en vuelo sea menor que `-N`, se puede enviar la siguiente sonda de la cola, independientemente del salto al que pertenezca.

### Estructuras necesarias

Una estructura por sonda individual:
```c
typedef struct s_probe
{
	int		ttl;
	int		seq;
	struct timeval	sent_at;
	int		done;
	char		from_ip[INET_ADDRSTRLEN];
	double		rtt;
	int		timed_out;
}	t_probe;
```

Una estructura por salto que agrupa sus sondas:
```c
typedef struct s_hop
{
	int		ttl;
	t_probe		probes[MAX_PROBES];
	int		done;
}	t_hop;
```

Estado global del traceroute:
```c
typedef struct s_traceroute
{
	t_hop		hops[MAX_HOPS];
	t_probe		*in_flight[MAX_N];  // punteros, no copias
	int		in_flight_count;
	int		next_to_send;       // índice de la próxima sonda a enviar
	int		next_to_print;      // próximo salto que toca mostrar
}	t_traceroute;
```

### Gestión de in_flight
Cuando una sonda se resuelve (respuesta o timeout), se pone su posición en `in_flight` a `NULL` y se decrementa `in_flight_count`. No se compacta el array, simplemente se comprueba `!= NULL` en cada iteración. Para un máximo de 16-20 elementos es más que suficiente.

### Orden de visualización
Los saltos se muestran en orden aunque las respuestas lleguen desordenadas. Un salto se considera completo cuando todas sus sondas tienen resultado. `next_to_print` apunta al siguiente salto que toca mostrar. Cuando ese salto está completo, se muestra y se avanza el puntero. Si el salto N+1 ya está resuelto pero el N no, se espera.

---

## Opción `-z` (tiempo mínimo entre envíos)

### Objetivo
Introducir una pausa mínima entre el envío de cada sonda. Útil para evitar saturar routers que limitan el rate de respuestas ICMP.

### Valores
- **Por defecto:** 0 (sin espera)
- **Interpretación:** si el valor es mayor que 10 → milisegundos. Si es menor o igual a 10 → segundos. Se permiten decimales (`-z 0.5` es medio segundo, `-z 500` son 500ms)
- **Mínimo:** 0
- **Máximo:** no hay límite formal

### Dónde actúa
Antes de cada `sendto()`. No afecta al timeout de recepción ni a la lógica del `select`. Solo introduce una espera entre envíos.

---

## Bucle principal con -N y -z

El núcleo de la implementación es un único bucle que gestiona envío y recepción a la vez usando `select` con timeout dinámico.

```
while (quedan sondas por enviar o hay sondas en vuelo)

    calcular tiempo hasta próximo envío permitido (-z)
    calcular timeout de la sonda más antigua en vuelo (5s - tiempo transcurrido)
    timeout_select = el menor de los dos

    select(socket_recepcion, timeout_select)

    si llegó respuesta → identificar sonda, guardar RTT e IP, marcar done=1, NULL en in_flight
    revisar sondas en in_flight → marcar timeout las que hayan expirado
    si in_flight_count < N y ha pasado tiempo -z → enviar siguiente sonda

    si hops[next_to_print].done → mostrar salto, avanzar next_to_print
```

### Identificación de respuestas
Las respuestas ICMP llegan desordenadas. Cada sonda necesita un identificador único para saber a qué TTL y número de sonda corresponde. Normalmente se usa el puerto destino UDP (que varía por sonda) o el campo identificador ICMP.

---

## Flujo de decisión al inicializar los sockets

```
¿Hay -i?
  └─ Validar con if_nametoindex() → error si no existe
  └─ setsockopt SO_BINDTODEVICE en socket envío
  └─ setsockopt SO_BINDTODEVICE en socket recepción

¿Hay -s?
  └─ ¿Hay también -i?
       └─ SÍ: verificar que la IP pertenece a ESA interfaz concreta → error si no
       └─ NO: verificar que la IP pertenece a cualquier interfaz → error si no
  └─ bind() con la IP en socket de envío
```
