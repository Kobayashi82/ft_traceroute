/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:22:45 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/04 13:35:51 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   |  Header  |      Length      |             Checksum             |
   |----------|------------------|----------------------------------|
   | Ethernet | No               | FCS (managed by NIC)             |
   | IP       | Header + Payload | Header                           |
   | ICMP     | No               | Header + Payload                 |
   | UDP      | Header + Payload | Pseudo-Header + Header + Payload |
   | TCP      | Header + Payload | Pseudo-Header + Header + Payload |
   | ARP      | No               | No                               |
   | PAYLOAD  | No               | No                               |
*/

// Si cambio ETHERNET o TCP debo desplazar los datos y actualizar los punteros

#pragma region "Includes"

	#include "network/packet.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "Headers"

	#pragma region "Add"

		#pragma region "Ethernet"

			static int ethernet_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "IP"

			static int ip_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "IP Option"

			static int ip_option_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			static int icmp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			static int udp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "TCP Option"

			static int tcp_option_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			static int arp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

		#pragma region "Payload"

			static int payload_add(t_packet *packet, void *data, uint16_t data_len) {
				if (!packet || !data) return (1);
				(void) data_len;

				if (!packet->ethernet_header) {
					if (packet->packet_len > 0) {
						if (packet->packet_len + sizeof(t_ethernet_header) > MAX_PACKET_LEN) return (1);
						ft_memmove((uint8_t *)packet + sizeof(t_ethernet_header), packet, packet->packet_len);
						if (packet->ip_header)		packet->ip_header	+= sizeof(t_ethernet_header);
						if (packet->ip_option)		packet->ip_option	+= sizeof(t_ethernet_header);
						if (packet->icmp_header)	packet->icmp_header	+= sizeof(t_ethernet_header);
						if (packet->udp_header)		packet->udp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_header)		packet->tcp_header	+= sizeof(t_ethernet_header);
						if (packet->tcp_option)		packet->tcp_option	+= sizeof(t_ethernet_header);
						if (packet->arp_header)		packet->arp_header	+= sizeof(t_ethernet_header);
						if (packet->payload)		packet->payload		+= sizeof(t_ethernet_header);
					}
				}

				ft_memcpy(packet->ethernet_header, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Remove"

		#pragma region "Ethernet"

			static int ethernet_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "IP"

			static int ip_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "Ip Option"

			static int ip_option_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			static int icmp_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			static int udp_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP Option"

			static int tcp_option_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			static int arp_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "Payload"

			static int payload_remove(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Validate"

		#pragma region "Ethernet"

			static int ethernet_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "IP"

			static int ip_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "IP Option"

			static int ip_option_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			static int icmp_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			static int udp_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP Option"

			static int tcp_option_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			static int arp_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Complete"

		#pragma region "Ethernet"

			static int ethernet_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "IP"

			static int ip_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "IP Option"

			static int ip_option_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			static int icmp_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			static int udp_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP Option"

			static int tcp_option_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			static int arp_complete(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

	#pragma endregion

#pragma endregion

#pragma region "Packet"

	#pragma region "Add"

		int packet_add(t_packet *packet, void *data, uint32_t data_len, t_herdar_type header_type) {
			if (!packet || !data || !data_len) return (1);

			switch (header_type) {
				case ETHERNET:		return (ethernet_add(packet, data));	// 14 bytes
				case IP:			return (ip_add(packet, data));			// 20 bytes
				case IP_OPTION:		return (ip_option_add(packet, data));	// 0/40 bytes
				case ICMP:			return (icmp_add(packet, data));		// 8 bytes
				case UDP:			return (udp_add(packet, data));			// 8 bytes
				case TCP:			return (tcp_add(packet, data));			// 20 bytes
				case TCP_OPTION:	return (tcp_option_add(packet, data));	// 0/40 bytes
				case ARP:			return (arp_add(packet, data));			// 28 bytes
				case PAYLOAD:		return (payload_add(packet, data, data_len));
			}

			return (1);
		}

	#pragma endregion

	#pragma region "Remove"

		int packet_remove(t_packet *packet, t_herdar_type header_type) {
			if (!packet) return (1);

			switch (header_type) {
				case ETHERNET:		return (ethernet_remove(packet));		// 14 bytes
				case IP:			return (ip_remove(packet));				// 20 bytes
				case IP_OPTION:		return (ip_option_remove(packet));		// 0/40 bytes
				case ICMP:			return (icmp_remove(packet));			// 8 bytes
				case UDP:			return (udp_remove(packet));			// 8 bytes
				case TCP:			return (tcp_remove(packet));			// 20 bytes
				case TCP_OPTION:	return (tcp_option_remove(packet));		// 0/40 bytes
				case ARP:			return (arp_remove(packet));			// 28 bytes
				case PAYLOAD:		return (payload_remove(packet));
			}

			return (1);
		}

	#pragma endregion

	#pragma region "Validate"

		// Check lengths, checksum and correct values
		int packet_validate(t_packet *packet) {
			if (!packet) return (1);
			
			ethernet_validate(packet);
			ip_validate(packet);
			ip_option_validate(packet);
			icmp_validate(packet);
			udp_validate(packet);
			tcp_validate(packet);
			tcp_option_validate(packet);
			arp_validate(packet);

			return (0);
		}

	#pragma endregion

	#pragma region "Complete"

		// Set lengths, calculate checksum and validate
		int packet_complete(t_packet *packet) {
			if (!packet) return (1);

			ethernet_complete(packet);
			ip_complete(packet);
			ip_option_complete(packet);
			icmp_complete(packet);
			udp_complete(packet);
			tcp_complete(packet);
			tcp_option_complete(packet);
			arp_complete(packet);

			return (0);
		}

	#pragma endregion

#pragma endregion
