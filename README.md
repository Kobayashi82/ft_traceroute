<div align="center">

![System & Kernel](https://img.shields.io/badge/System-brown?style=for-the-badge)
![Network Communication](https://img.shields.io/badge/Network-Communication-blue?style=for-the-badge)
![ICMP Protocol](https://img.shields.io/badge/Protocol-UDP--TCP--ICMP-green?style=for-the-badge)
![C Language](https://img.shields.io/badge/Language-C-red?style=for-the-badge)

*Una reimplementación del comando traceroute*

</div>

# ft_traceroute

## 🎯 Descripción

**ft_traceroute** es una implementación desde cero del comando `traceroute`, una herramienta esencial para el diagnóstico y análisis de rutas de red. Este proyecto explora el funcionamiento de enrutamiento IP y la topología de redes, utilizando técnicas avanzadas de manipulación de TTL (Time To Live).

### ¿Qué es Traceroute?

Traceroute es una utilidad de red que:

- **Mapea la ruta** que siguen los paquetes desde el origen hasta el destino
- **Identifica routers intermedios** (saltos/hops) en el camino
- **Mide latencia** de cada salto individual
- **Diagnostica problemas** de enrutamiento y puntos de fallo
- **Utiliza TTL decremental** para revelar la topología de red

### Funcionamiento Técnico

```
TTL=1  [Cliente] -----> [Router1] (TTL expired)
         ^                  |
         |<--- ICMP Time Exceeded ---
         
TTL=2  [Cliente] -----> [Router1] -----> [Router2] (TTL expired)
         ^                                   |
         |<--------- ICMP Time Exceeded ----
         
TTL=3  [Cliente] -----> [Router1] -----> [Router2] -----> [Destino]
         ^                                                     |
         |<-------------- ICMP Echo Reply -------------------
```

#### Algoritmo Básico

1. **Inicialización**: Comienza con TTL = 1
2. **Envío de sondas**: Envía múltiples paquetes (típicamente 3) con el mismo TTL
3. **Recepción de respuestas**: 
   - ICMP Time Exceeded → Router intermedio identificado
   - ICMP Echo Reply → Destino alcanzado
4. **Incremento de TTL**: TTL++ para el siguiente salto
5. **Repetición**: Continúa hasta alcanzar el destino o máximo TTL

### Tipos de Sondas

ft_traceroute puede usar diferentes protocolos para las sondas:

| Protocolo |  Puerto  |   Detección    |
|-----------|----------|----------------|
| **UDP**   | 33434+   | Puerto cerrado |
| **ICMP**  | N/A      | Echo Reply     |
| **TCP**   | Variable | SYN/ACK o RST  |
|

## 🔧 Compilación

```bash
git clone https://github.com/Kobayashi82/ft_traceroute.git
cd ft_traceroute
make
```

## 🖥️ Uso

### Permisos

```bash
# ft_traceroute requiere privilegios root para raw sockets
sudo ./ft_traceroute destino.com

# Alternativa: configurar capabilities
sudo setcap cap_net_raw+ep ./ft_traceroute
./ft_traceroute destino.com
```

### Ejecución

```bash
sudo ./ft_traceroute [opciones] <destino> [packetlen]
```

|  Argumento  |     Tipo      |                     Descripción                      |         Ejemplo         |
|-------------|---------------|------------------------------------------------------|-------------------------|
| `destino`   | IPv4/Hostname | Dirección IP o nombre de host                        | `8.8.8.8`, `google.com` |
| `packetlen` | Número        | Longitud del paquete (default: IP header + 40 bytes) | `60`, `1500`            |
|

#### Básicas
|   Opción   | Forma Larga |         Descripción          |
|------------|-------------|------------------------------|
| `-h`, `-?` | `--help`    | Muestra información de ayuda |
| `-V`       | `--version` | Versión del programa         |
|            | `--usage`   | Mensaje corto de uso         |
|

#### Control de Ruta
| Opción |     Forma Larga     | Parámetro |                                             Descripción                                             |
|--------|---------------------|-----------|-----------------------------------------------------------------------------------------------------|
| `-m`   | `--max-hops=NUM`    | Número    | Máximo número de saltos (default: 30)                                                               |
| `-f`   | `--first-hop=NUM`   | Número    | TTL inicial (default: 1)                                                                            |
| `-q`   | `--queries=NUM`     | Número    | Número de sondas por salto (default: 3)                                                             |
| `-w`   | `--wait=NUM`        | Segundos  | Tiempo de espera por respuesta (default: 5)                                                         |
| `-N`   | `--sim-queries=NUM` | Número    | Número de sondas simultáneas (default: 16)                                                          |
| `-z`   | `--sendwait=NUM`    | Segundos  | Intervalo mínimo entre sondas (default: 0). Si NUM es mayor que 10, se interpreta como milisegundos |
|

#### Configuración de Sondas
| Opción |    Forma Larga    | Parámetro |                 Descripción                  |
|--------|-------------------|-----------|----------------------------------------------|
| `-p`   | `--port=NUM`      | Puerto    | Puerto base para sondas UDP (default: 33434) |
| `-s`   | `--source=ADDR`   | IP        | Dirección IP origen                          |
| `-t`   | `--tos=NUM`       | Número    | Type of Service (TOS)                        |
| `-F`   | `--dont-fragment` | -         | Activa flag Don't Fragment                   |
|

#### Métodos de Sondeo
| Opción | Forma Larga |              Descripción              |
|--------|-------------|---------------------------------------|
| `-I`   | `--icmp`    | Usa ICMP Echo Request en lugar de UDP |
| `-T`   | `--tcp`     | Usa TCP SYN para sondas               |
| `-U`   | `--udp`     | Usa UDP (comportamiento por defecto)  |
|

#### Opciones de Red
| Opción |     Forma Larga      |  Parámetro  |                  Descripción                  |
|--------|----------------------|-------------|-----------------------------------------------|
| `-n`   | `--numeric`          | -           | No resuelve direcciones IP a nombres          |
| `-d`   | `--debug`            | -           | Activa depuración a nivel de socket           |
| `-i`   | `--interface=DEVICE` | Dispositivo | Especifica interfaz de red a usar             |
| `-r`   | -                    | -           | Evita enrutamiento normal, envía directamente |
|

#### Valores TOS (Type of Service)

La opción `-t` permite configurar el campo TOS del header IP:

| Valor |         Tipo         |    Descripción     |
|-------|----------------------|--------------------|
| 16    | Low Delay            | Baja latencia      |
| 4     | High Reliability     | Alta confiabilidad |
| 8     | High Throughput      | Alto rendimiento   |
| 136   | High Priority        | Alta prioridad     |
| 184   | Expedited Forwarding | Reenvío expedito   |
|

## 📡 Funcionamiento Interno

### Manipulación de TTL

El campo TTL (Time To Live) en el header IP es fundamental:

```c
struct ip_header {
    uint8_t  version_ihl;     // Versión (4 bits) + IHL (4 bits)
    uint8_t  tos;             // Type of Service
    uint16_t total_length;    // Longitud total del paquete
    uint16_t identification;  // ID de fragmentación
    uint16_t flags_fragment;  // Flags (3 bits) + Fragment offset (13 bits)
    uint8_t  ttl;             // Time To Live ← Campo clave
    uint8_t  protocol;        // Protocolo (UDP=17, ICMP=1, TCP=6)
    uint16_t checksum;        // Checksum del header
    uint32_t source_addr;     // Dirección IP origen
    uint32_t dest_addr;       // Dirección IP destino
};
```

### Procesamiento de Respuestas

#### Time Exceeded (Tipo 11)
```c
struct icmp_time_exceeded {
    uint8_t  type;            // 11 (Time Exceeded)
    uint8_t  code;            // 0 (TTL exceeded in transit)
    uint16_t checksum;        // Checksum ICMP
    uint32_t unused;          // Campo reservado
    // Header IP original + 8 bytes de datos originales
    struct ip_header original_ip;
    uint8_t original_data[8];
};
```

#### Destination Unreachable (Tipo 3)
| Código |      Descripción       |               Significado                |
| ------ | ---------------------- | ---------------------------------------- |
| 0      | Network Unreachable    | Red no alcanzable                        |
| 1      | Host Unreachable       | Host no alcanzable                       |
| 2      | Protocol Unreachable   | Protocolo no soportado                   |
| 3      | Port Unreachable       | Puerto cerrado (UDP traceroute)          |
| 4      | Fragmentation Required | Fragmentación necesaria pero DF activado |
|

### Detección de Finalización

La traza termina cuando:

1. **Echo Reply recibido** (para ICMP traceroute)
2. **Port Unreachable** (para UDP traceroute)
3. **TCP SYN/ACK** o **RST** (para TCP traceroute)
4. **Máximo TTL alcanzado** (timeout o límite)

## 🗺️ Interpretación de Resultados

### Formato de Salida Estándar

```
traceroute to google.com (142.250.185.14), 30 hops max, 60 byte packets
 1  gateway (192.168.1.1)  1.234 ms  1.567 ms  1.890 ms
 2  10.0.0.1 (10.0.0.1)  15.234 ms  14.567 ms  16.890 ms
 3  * * *
 4  72.14.194.226 (72.14.194.226)  45.123 ms  44.567 ms  43.890 ms
```

### Interpretación de Símbolos

| Símbolo |       Significado        |            Causa Probable            |
| ------- | ------------------------ | ------------------------------------ |
| `*`     | Sin respuesta            | Firewall, router silencioso, timeout |
| `!H`    | Host Unreachable         | Destino no alcanzable                |
| `!N`    | Network Unreachable      | Red no existe o no enrutada          |
| `!P`    | Protocol Unreachable     | Protocolo bloqueado                  |
| `!X`    | Communication Prohibited | Filtrado administrativo              |
|

### Análisis de Latencias

```bash
# Latencias normales
 5  router.normal.com  25.123 ms  24.567 ms  26.890 ms

# Latencias inconsistentes
 5  router.congestionado.com  125.123 ms  45.567 ms  186.890 ms

# Pérdida de paquetes
 5  router.perdidas.com  35.123 ms  *  37.890 ms
```
## ⚠️ Limitaciones y Consideraciones

### Comportamiento de Routers

- **Load Balancing**: Rutas pueden cambiar entre paquetes
- **ICMP Rate Limiting**: Algunos routers limitan respuestas ICMP
- **Filtrado Selectivo**: Firewalls pueden bloquear ciertos TTL
- **Respuestas Asimétricas**: Router A puede responder por Router B

### Precisión de Medición

- **Variabilidad de red**: Latencias pueden fluctuar significativamente
- **Procesamiento ICMP**: Prioridad baja en muchos routers
- **Caché de ARP**: Primeras mediciones pueden ser inexactas
- **QoS**: Type of Service puede afectar el tratamiento de paquetes

### Consideraciones de Seguridad

⚠️ **Uso responsable:**
- **Respetar políticas** de red organizacionales
- **Evitar reconocimiento** no autorizado
- **Considerar rate limiting** para evitar detección como ataque

### Detección y Contramedidas

Algunos sistemas pueden detectar:
- **Patrones de escaneo de puertos** (con TCP traceroute)
- **Sondeo repetitivo** (múltiples trazas consecutivas)
- **Patrones anómalos de TTL** (saltos no secuenciales)
- **Sondeo de alta frecuencia** (intervalos muy cortos)

## 📄 Licencia

Este proyecto está licenciado bajo la WTFPL – [Do What the Fuck You Want to Public License](http://www.wtfpl.net/about/).

---

<div align="center">

**🌐 Desarrollado como parte del curriculum de 42 School 🌐**

*"From source to destination, every step uncovered"*

</div>
