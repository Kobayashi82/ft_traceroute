
|  Header  |      Length      |             Checksum             |
|----------|------------------|----------------------------------|
| Ethernet | No               | FCS (managed by NIC)             |
| IP       | Header + Payload | Header                           |
| ICMP     | No               | Header + Payload                 |
| UDP      | Header + Payload | Pseudo-Header + Header + Payload |
| TCP      | Header + Payload | Pseudo-Header + Header + Payload |
| ARP      | No               | No                               |
| PAYLOAD  | No               | No                               |
