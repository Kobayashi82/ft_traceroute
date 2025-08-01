# Guía DSCP y ECN para Raw Sockets

## Estructura del campo ToS (8 bits)

```
Bit:    7   6   5   4   3   2   1   0
       |----DSCP (6 bits)-----|ECN(2)|
```

- **DSCP**: 6 bits más significativos (0-63)
- **ECN**: 2 bits menos significativos (0-3)

## Valores ECN por Protocolo

```c
// TCP
uint8_t ecn = 1;  // ECT(1) - Estándar moderno

// UDP
uint8_t ecn = 0;  // Not ECT - Sin control de congestión

// ICMP
uint8_t ecn = 0;  // Not ECT - Mensajes de control
```

## Conversión Rápida

```c
// ToS → DSCP
uint8_t DSCP_Byte = (tos & 0xFC) | ecn;

// DSCP → ToS
uint8_t DSCP = (tos & 0xFC);
uint8_t ECN = tos & 0x03;
```

## Valores ECN

| Valor | Binario | Nombre | Uso |
|-------|---------|--------|-----|
| 0 | 00 | Not ECT | No compatible con ECN |
| 1 | 01 | ECT(1) | Compatible ECN - estándar |
| 2 | 10 | ECT(0) | Compatible ECN - alternativo |
| 3 | 11 | CE | Congestión detectada (solo routers) |

## Valores DSCP Comunes

### Clase de Servicio (Class Selector)
| DSCP | Binario | Nombre | Uso | Decimal ToS |
|------|---------|--------|-----|-------------|
| 0 | 000000 | CS0/BE | Best Effort | 0 |
| 8 | 001000 | CS1 | Bulk/Respaldo | 32 |
| 16 | 010000 | CS2 | Standard | 64 |
| 24 | 011000 | CS3 | Crítico | 96 |
| 32 | 100000 | CS4 | Video | 128 |
| 40 | 101000 | CS5 | VoIP | 160 |
| 48 | 110000 | CS6 | Control de red | 192 |
| 56 | 111000 | CS7 | Reservado | 224 |

### Assured Forwarding (AF)
| DSCP | Binario | Nombre | Uso | Decimal ToS |
|------|---------|--------|-----|-------------|
| 10 | 001010 | AF11 | Baja prioridad, baja pérdida | 40 |
| 12 | 001100 | AF12 | Baja prioridad, media pérdida | 48 |
| 14 | 001110 | AF13 | Baja prioridad, alta pérdida | 56 |
| 18 | 010010 | AF21 | Media prioridad, baja pérdida | 72 |
| 20 | 010100 | AF22 | Media prioridad, media pérdida | 80 |
| 22 | 010110 | AF23 | Media prioridad, alta pérdida | 88 |
| 26 | 011010 | AF31 | Alta prioridad, baja pérdida | 104 |
| 28 | 011100 | AF32 | Alta prioridad, media pérdida | 112 |
| 30 | 011110 | AF33 | Alta prioridad, alta pérdida | 120 |
| 34 | 100010 | AF41 | Video streaming | 136 |
| 36 | 100100 | AF42 | Video streaming, media pérdida | 144 |
| 38 | 100110 | AF43 | Video streaming, alta pérdida | 152 |

### Expedited Forwarding
| DSCP | Binario | Nombre | Uso | Decimal ToS |
|------|---------|--------|-----|-------------|
| 46 | 101110 | EF | VoIP, tiempo real crítico | 184 |

### Tabla Rápida

| ToS | DSCP | Nombre | Uso |
|-----|------|--------|-----|
| 0 | 0 | BE | Best Effort |
| 32 | 8 | CS1 | Bulk |
| 64 | 16 | CS2 | Standard |
| 96 | 24 | CS3 | Crítico |
| 104 | 26 | AF31 | Alta prioridad |
| 136 | 34 | AF41 | Video |
| 184 | 46 | EF | VoIP/Tiempo real |
