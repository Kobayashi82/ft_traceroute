# ft_traceroute

## Cómo funciona

- Envía paquetes **UDP** o **ICMP** con TTL incremental (1, 2, 3...) hacia puertos altos (desde 33434)
- Cada router que recibe un paquete con TTL=0 devuelve un **ICMP Time Exceeded**
- Cuando llega al destino, si el puerto no está en uso, devuelve **ICMP Port Unreachable** o **Echo Replay**
- Escucha las respuestas ICMP con un **raw socket ICMP**

---

## Flujo

- Resolver hostname
- Mostrar cabecera (traceroute to X, Y hops max)
- setsockopt IP_TTL = TTL actual
- Guardar timestamp
- Enviar paquetes UDP/ICMP (puertos 33434, 33435, 33436...)
- Esperar respuestas con select (timeout)
- Verificar que es nuestra respuesta
- Calcular tiempo transcurrido
- Guardar IP  y tiempo en su posición (1, 2, 3...)
- Actualizar tiempo restante del timeout
- Si timeout expira, las posiciones sin respuesta = *
- Imprimir salida del salto actual
- Si recibimos Port Unreachable o Echo Replay terminar

---

## Sockets

- **Socket UDP** (`SOCK_DGRAM`) → para enviar (UDP)
- **Raw socket ICMP** (`SOCK_RAW, IPPROTO_ICMP`) → para enviar (ICMP)

- **Raw socket ICMP** (`SOCK_RAW, IPPROTO_ICMP`) → para recibir

---

## Puertos

- Rango de puertos usado: **33434 a 33534** (100 puertos)
- Wrap around vuelve a **33434** al superar **33534**
- Empieza en **33434** y se incrementa con cada paquete enviado
- TTL=1 → puertos 33434, 33435, 33436
- TTL=2 → puertos 33437, 33438, 33439
- Y así sucesivamente...

Cuándo el modo es ICMP,  se incrementa el valor de la secuencia (Seq)

---

## Timeout

- Guardar el timestamp antes de enviar los paquetes
- En cada llamada a `select` calcular cuánto tiempo queda: `tiempo_restante = timeout - tiempo_transcurrido`
- Así el salto nunca supera timeout, independientemente de cuántas respuestas lleguen

---

## Respuestas

Los paquetes pueden llegar en cualquier orden

### ICMP

**Time Exceeded (11)**

- Castear a `struct iphdr`
- Avanzar `(ihl * 4) + 8`
- Castear a `struct iphdr`
- Avanzar `ihl * 4`
- Castear a `struct icmphdr` → ID y Seq

**Echo Reply (0)**

- Castear a `struct iphdr`
- Castear a `struct icmphdr` → ID y Seq

Verificar:
- ID coincide con PID del proceso
- Secuencia está en nuestro rango activo

### UDP

**Time Exceeded (11)** y **Port Unreachable (3)**

- Castear a `struct iphdr`
- Avanzar `(ihl * 4) + 8`
- Castear a `struct iphdr` → IP detino
- Avanzar `ihl * 4`
- Castear a `struct udphdr` → Puerto destino

Los 8 bytes del header UDP:
- 2 bytes: puerto origen
- 2 bytes: puerto destino
- 2 bytes: longitud
- 2 bytes: checksum

Verificar:
- IP destino del header IP interno coincide con nuestro destino
- Puerto destino del header UDP interno está en nuestro rango activo

---

## Condiciones de terminación

| Condición | Acción |
|---|---|
| ICMP Port Unreachable recibido | Terminar |
| ICMP Reply | Terminar |
| TTL máximo alcanzado | Terminar |
| Timeout en un salto | Mostrar `*` |
| ICMP Time Exceeded | Mostrar IP y tiempo |
| Señal recibida | Terminar |

---

## Formato de salida

```
# Esto está por ver

 1  192.168.1.1  1.2 ms  1.1 ms  1.3 ms
 2  10.0.0.1 (router.isp.com)  5.2 ms  10.0.0.2 (router2.isp.com)  6.1 ms  5.8 ms
 3  * * *
```

Reglas de impresión:
- Si la IP de la respuesta es la misma que la anterior → tiempo
- Si es diferente → IP y tiempo
- Si no hay respuesta → `*`

---

## Opciones

| Opción | Descripción | Default | Máximo |
|---|---|---|---|
| `-m` | TTL máximo | 30 | 1-255 |
| `-p` | Puerto destino inicial | 33434 | 1-65535 |
| `-q` | Paquetes por salto | 3 | 1-20 |
| `-t` | TOS con `IP_TOS` | 0 | 255 |
| `-f` | TTL inicial | 1 | 1-255 (error si `-f` > `-m`) |
| `-w` | Timeout de espera | 5 | 1-60 |
| `-n` | Desactiva DNS inverso por salto | off | — |
| `-I` | Usa ICMP Echo en vez de UDP | off | — |
| `-F` | Bit Don't Fragment con `IP_MTU_DISCOVER` | off | — |
| `-r` | Bypass routing table con `SO_DONTROUTE` | off | — |

Además de las opciones de ayuda, versión y uso
