# Guía Completa de Sockets en C

## Índice
1. [Introducción](#introducción)
2. [Función socket()](#función-socket)
3. [Primer Argumento: DOMAIN](#primer-argumento-domain)
4. [Segundo Argumento: TYPE](#segundo-argumento-type)
5. [Tercer Argumento: PROTOCOL](#tercer-argumento-protocol)
6. [Niveles de Control](#niveles-de-control)
7. [Casos Prácticos](#casos-prácticos)
8. [Compatibilidad entre Argumentos](#compatibilidad-entre-argumentos)

## Introducción

Los sockets son la interfaz de programación estándar para comunicación de red en sistemas Unix/Linux. Permiten diferentes niveles de control, desde aplicaciones de alto nivel hasta manipulación directa de frames Ethernet.

## Función socket()

```c
int socket(int domain, int type, int protocol);
```

**Retorna:** File descriptor del socket o -1 en caso de error.

---

## Primer Argumento: DOMAIN

El domain especifica la **familia de direcciones** y determina qué tipo de direcciones usarás.

### AF_INET (IPv4) - El más común
```c
socket(AF_INET, SOCK_STREAM, 0);
```
- **Direcciones:** 32 bits (192.168.1.1, 8.8.8.8)
- **Estructura:** `struct sockaddr_in`
- **Uso:** Internet, redes locales IPv4
- **Limitación:** ~4 mil millones de direcciones

### AF_INET6 (IPv6) - Sucesor de IPv4
```c
socket(AF_INET6, SOCK_STREAM, 0);
```
- **Direcciones:** 128 bits (2001:db8::1, ::1)
- **Estructura:** `struct sockaddr_in6`
- **Uso:** Internet moderno, futuro de las redes
- **Ventaja:** Espacio de direcciones prácticamente infinito

### AF_PACKET - Raw Ethernet
```c
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
```
- **Direcciones:** Direcciones MAC + interfaz de red
- **Estructura:** `struct sockaddr_ll`
- **Uso:** Análisis de red, herramientas como tcpdump, wireshark
- **Control:** Frame Ethernet completo
- **Requiere:** Root o CAP_NET_RAW

### AF_LOCAL / AF_UNIX - Comunicación local
```c
socket(AF_LOCAL, SOCK_STREAM, 0);
```
- **Direcciones:** Rutas del filesystem (/tmp/socket, /var/run/mysql.sock)
- **Estructura:** `struct sockaddr_un`
- **Uso:** IPC (Inter-Process Communication) entre procesos del mismo sistema
- **Ventajas:** Muy rápido, no pasa por red, permisos del filesystem

#### **Notas:** Hay más dominios, pero no se detallan en este documento
---

## Segundo Argumento: TYPE

El argumento type determina **cómo se comporta** la comunicación: confiable vs rápida, con conexión vs sin conexión.

### SOCK_STREAM - Flujo confiable
```c
socket(AF_INET, SOCK_STREAM, 0);
```
**Características:**
- **Orientado a conexión** - requiere ```connect()``` / ```accept()```
- **Confiable** - garantiza entrega y orden
- **Flujo de bytes** - no preserva límites de mensajes
- **Control de flujo** - maneja congestión automáticamente
- **Full-duplex** - bidireccional simultáneo

**Protocolo típico:** TCP  
**Uso:** HTTP, HTTPS, SSH, FTP, bases de datos  
**Ventaja:** Sin pérdida de datos, orden garantizado  
**Desventaja:** Más overhead, más lento

### SOCK_DGRAM - Datagramas
```c
socket(AF_INET, SOCK_DGRAM, 0);
```
**Características:**
- **Sin conexión** - envío directo con ```sendto()```
- **No confiable** - puede perder, duplicar, desordenar
- **Preserva límites** - cada send() = un datagrama
- **Rápido** - mínimo overhead
- **Sin estado** - no mantiene conexiones

**Protocolo típico:** UDP  
**Uso:** DNS, DHCP, streaming, juegos, broadcasting  
**Ventaja:** Velocidad, simplicidad  
**Desventaja:** Sin garantías de entrega

### SOCK_RAW - Acceso de bajo nivel
```c
socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
```
**Características:**
- **Control de headers** - puedes crear headers de protocolos
- **Sin procesamiento** - el kernel no interpreta el contenido
- **Máximo control** - para herramientas especializadas
- **Requiere** - root o CAP_NET_RAW

**Uso:** ping, traceroute, nmap, sniffers  
**Ventaja:** Control total del protocolo  
**Desventaja:** Complejidad, requiere permisos

### FLAGS adicionales - Puedes combinar con ```|```

**SOCK_NONBLOCK:**
```c
socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
```
- **No bloqueante** - operaciones retornan inmediatamente
- **Equivale a:** crear socket + fcntl(O_NONBLOCK)

**SOCK_CLOEXEC:**
```c
socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
```
- **Close-on-exec** - se cierra automáticamente en ```exec()```
- **Equivale a:** crear socket + fcntl(FD_CLOEXEC)
- **Ventaja:** Evita race conditions en programas multithreaded

---

## Tercer Argumento: PROTOCOL

El protocol determina **exactamente qué protocolo** manejas, especialmente crítico en raw sockets.

### Valor 0 - Protocolo por defecto
```c
socket(AF_INET, SOCK_STREAM, 0);    // TCP
socket(AF_INET, SOCK_DGRAM, 0);     // UDP
socket(AF_INET, SOCK_RAW, 0);       // IP
```

### Para AF_INET/AF_INET6 + SOCK_RAW

**Protocolos IP estándar:**
```c
socket(AF_INET, SOCK_RAW, IPPROTO_IP);      // 0   - IP
socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);    // 1   - ICMP
socket(AF_INET, SOCK_RAW, IPPROTO_IGMP);    // 2   - IGMP  
socket(AF_INET, SOCK_RAW, IPPROTO_TCP);     // 6   - TCP
socket(AF_INET, SOCK_RAW, IPPROTO_UDP);     // 17  - UDP
socket(AF_INET, SOCK_RAW, IPPROTO_IPV6);    // 41  - IPv6-in-IPv4
socket(AF_INET, SOCK_RAW, IPPROTO_GRE);     // 47  - GRE
socket(AF_INET, SOCK_RAW, IPPROTO_ESP);     // 50  - IPSec ESP
socket(AF_INET, SOCK_RAW, IPPROTO_AH);      // 51  - IPSec AH
socket(AF_INET, SOCK_RAW, IPPROTO_OSPF);    // 89  - OSPF
socket(AF_INET, SOCK_RAW, IPPROTO_RAW);     // 255 - Cualquiera
```

### Para AF_PACKET
```c
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));      // 0x0003 - Todos los protocolos
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));       // 0x0800 - IPv4
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IPV6));     // 0x86DD - IPv6
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));      // 0x0806 - ARP
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_8021Q));    // 0x8100 - VLAN
```

### Comportamiento especial de IPPROTO_RAW
```c
socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
```
**Diferencias:**
- **Fuerza IP_HDRINCL=1** - siempre debes crear IP header
- **Sin filtrado** - puedes enviar cualquier protocolo IP
- **Control total** - tú decides el campo protocol en IP header
- **Más flexible** - para herramientas que necesitan múltiples protocolos

---

## Niveles de Control

### 1. Sockets de aplicación (normales)
```c
// TCP - kernel maneja todo salvo datos
socket(AF_INET, SOCK_STREAM, 0);

// UDP - kernel maneja todo salvo datos  
socket(AF_INET, SOCK_DGRAM, 0);
```
**Control:** Solo datos de aplicación  
**Kernel crea:** Ethernet + IP + TCP/UDP headers

### 2. Raw sockets IP
```c
// Para ICMP
socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

// Para TCP (sin conexión)
socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

// Para cualquier protocolo IP
socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
```
**Control:** IP header + protocolo superior  
**Kernel crea:** Ethernet header

### 3. Raw sockets Ethernet
```c
// Control total de frame Ethernet
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
```
**Control:** Frame Ethernet completo  
**Kernel crea:** Nada

### Control del IP Header con IP_HDRINCL

**Sin IP_HDRINCL (por defecto):**
```c
int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
// Tú creas: ICMP header
// Kernel crea: Ethernet + IP header
```

**Con IP_HDRINCL:**
```c
int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
int on = 1;
setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
// Tú creas: IP + ICMP header
// Kernel crea: Ethernet header
```

**IP_HDRINCL funciona con:**
- IPPROTO_ICMP
- IPPROTO_TCP
- IPPROTO_UDP
- raw socket (AF_INET)

---

## Tabla de compatibilidad

|    Domain     | STREAM  |  DGRAM  | RAW |
|---------------|---------|---------|-----|
| **AF_INET**   | ✅ TCP  | ✅ UDP | ✅  |
| **AF_INET6**  | ✅ TCP  | ✅ UDP | ✅  |
| **AF_PACKET** | ❌      | ✅     | ✅  |

### ¿Por qué AF_PACKET no soporta SOCK_STREAM?

**AF_PACKET opera a nivel Ethernet (Capa 2):**
- Maneja frames Ethernet individuales
- No hay concepto de "conexión" a este nivel
- Los frames pueden perderse o llegar desordenados

**SOCK_STREAM requiere:**
- Conexión establecida
- Flujo confiable de bytes
- Orden garantizado
- Control de flujo

El conflicto es que Ethernet por sí mismo no proporciona confiabilidad, eso lo hacen protocolos superiores como TCP.

### Headers que debes crear según el socket

|                      Socket                      |           Tú creas           |     Kernel crea     |
|--------------------------------------------------|------------------------------|---------------------|
| `AF_INET, SOCK_STREAM, 0`                        | Payload                      | Ethernet + IP + TCP |
| `AF_INET, SOCK_DGRAM, 0`                         | Payload                      | Ethernet + IP + UDP |
| `AF_INET, SOCK_RAW, IPPROTO_ICMP`                | ICMP                         | Ethernet + IP       |
| `AF_INET, SOCK_RAW, IPPROTO_ICMP` + `IP_HDRINCL` | IP + ICMP                    | Ethernet            |
| `AF_PACKET, SOCK_RAW, ETH_P_ALL`                 | Ethernet + IP + TCP/UDP/ICMP | -                   |

---

## Resumen

Los sockets ofrecen diferentes niveles de control según tus necesidades y la elección correcta depende del nivel de control que necesites y la complejidad que estés dispuesto a manejar.