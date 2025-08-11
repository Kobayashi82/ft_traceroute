/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:22:45 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 14:05:49 by vzurera-         ###   ########.fr       */
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

#pragma region "Includes"

	#include "network/packet.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "Checksum"

	static unsigned short checksum(void *data, int len) {
		unsigned long	sum = 0;
		unsigned short	*buf = data;

		while (len > 1) { sum += *buf++; len -= 2; }
		if (len == 1) sum += *(unsigned char *)buf;
		sum = (sum >> 16) + (sum & 0xFFFF);
		sum += (sum >> 16);

		return (unsigned short)(~sum);
	}

#pragma endregion

#pragma region "Headers"

	#pragma region "Add"

		#pragma region "Ethernet"

			static int ethernet_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->ethernet_header || packet->ip_header || packet->ip_option || packet->icmp_header || packet->udp_header || packet->tcp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				ft_memcpy(packet, data, sizeof(t_ethernet_header));
				packet->ethernet_header = (t_ethernet_header *)packet;
				packet->packet_len = sizeof(t_ethernet_header);

				return (0);
			}

		#pragma endregion

		#pragma region "IP"

			static int ip_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->ip_header || packet->ip_option || packet->icmp_header || packet->udp_header || packet->tcp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, sizeof(t_ip_header));
				packet->ip_header = (t_ip_header *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += sizeof(t_ip_header);

				return (0);
			}

		#pragma endregion

		#pragma region "IP Option"

			static int ip_option_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->ip_header) return (1);
				if (packet->ip_option || packet->icmp_header || packet->udp_header || packet->tcp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				uint8_t option_len = ((t_ip_option *)data)->length;
				if (!option_len) return (1);
				if (option_len % 4 || ((t_ip_option *)data)->options[option_len - 1] != EOOL) {
					option_finalize((t_ip_option *)data);
					option_len = ((t_ip_option *)data)->length;
				}

				uint8_t	total_oct = ((option_len + 3) / 4);
				ip_set_ihl(packet->ip_header, 5 + total_oct);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, total_oct * 4);
				packet->ip_option = (t_ip_option *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += total_oct * 4;

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			static int icmp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->ethernet_header && !packet->ip_header) return (1);
				if (packet->ip_option && !packet->ip_header) return (1);
				if (packet->icmp_header || packet->udp_header || packet->tcp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, sizeof(t_icmp_header));
				packet->icmp_header = (t_icmp_header *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += sizeof(t_icmp_header);

				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			static int udp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->ethernet_header && !packet->ip_header) return (1);
				if (packet->ip_option && !packet->ip_header) return (1);
				if (packet->udp_header || packet->icmp_header || packet->tcp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, sizeof(t_udp_header));
				packet->udp_header = (t_udp_header *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += sizeof(t_udp_header);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->ethernet_header && !packet->ip_header) return (1);
				if (packet->ip_option && !packet->ip_header) return (1);
				if (packet->tcp_header || packet->icmp_header || packet->udp_header || packet->tcp_option || packet->arp_header || packet->payload) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, sizeof(t_tcp_header));
				packet->tcp_header = (t_tcp_header *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += sizeof(t_tcp_header);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP Option"

			static int tcp_option_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (!packet->tcp_header) return (1);
				if (packet->tcp_option || packet->icmp_header || packet->udp_header || packet->arp_header || packet->payload) return (1);

				uint8_t option_len = ((t_tcp_option *)data)->length;
				// validar option_len y return 1 si no multiple de 4;

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, option_len);
				packet->tcp_option = (t_tcp_option *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += option_len;

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			static int arp_add(t_packet *packet, void *data) {
				if (!packet || !data) return (1);

				if (packet->arp_header || packet->ip_header || packet->ip_option || packet->icmp_header || packet->tcp_header || packet->tcp_option || packet->payload) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, sizeof(t_arp_header));
				packet->arp_header = (t_arp_header *)((uint8_t *)packet + packet->packet_len);
				packet->packet_len += sizeof(t_arp_header);

				return (0);
			}

		#pragma endregion

		#pragma region "Payload"

			static int payload_add(t_packet *packet, void *data, uint16_t data_len) {
				if (!packet || !data || !data_len) return (1);

				if (packet->packet_len + data_len >= MAX_PACKET_LEN) return (1);
				if (packet->payload || (!packet->icmp_header && !packet->udp_header && !packet->tcp_option)) return (1);

				ft_memcpy((uint8_t *)packet + packet->packet_len, data, data_len);
				packet->payload = packet + packet->packet_len;
				packet->payload_len = data_len;
				packet->packet_len += data_len;

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Validate"

		#pragma region "IP"

			static int ip_option_validate(t_packet *packet) {
				if (!packet || !packet->ip_option) return (0);

				if (!packet->ip_header) return (1);
				// invalid options

				return (0);
			}

			int ip_validate(t_packet *packet) {
				if (!packet || !packet->ip_header) return (0);

				// invalid ver and ihl
				// invalid dscp/ecn
				// total length < ip header
				// invalid protocol
				// invalid src addr
				// invalid dst addr

				ip_option_validate(packet);

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			int icmp_validate(t_packet *packet) {
				if (!packet) return (1);

				// dst port
				// 
				return (0);
			}

		#pragma endregion

		#pragma region "UDP"

			int udp_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

		#pragma endregion

		#pragma region "TCP"

			static int tcp_option_validate(t_packet *packet) {
				if (!packet) return (1);

				return (0);
			}

			int tcp_validate(t_packet *packet) {
				if (!packet) return (1);

				tcp_option_validate(packet);

				return (0);
			}

		#pragma endregion

		#pragma region "ARP"

			int arp_validate(t_packet *packet) {
				if (!packet || !packet->arp_header) return (0);

				if (!packet->ethernet_header) return (1);
				if (packet->ethernet_header->ethertype != ETH_P_ARP) return (1);
				if (packet->arp_header->sha != packet->ethernet_header->src_mac) return (1);
				if (packet->arp_header->oper == ARPOP_REPLY && packet->arp_header->tha != packet->ethernet_header->dst_mac) return (1);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Complete"

		#pragma region "IP"

			static int ip_complete(t_packet *packet) {
				if (!packet || !packet->ip_header) return (0);

				uint16_t total_len = packet->packet_len;

				if (packet->ethernet_header) total_len -= sizeof(t_ethernet_header);
				packet->ip_header->length = htons(total_len);
				packet->ip_header->checksum = 0;

				uint8_t	total_oct = 0;
				if (packet->ip_option) total_oct = ((packet->ip_option->length + 3) / 4);
				ip_set_ihl(packet->ip_header, 5 + total_oct);

				packet->ip_header->checksum = checksum(packet->ip_header, (5 + total_oct) * 4);

				return (0);
			}

		#pragma endregion

		#pragma region "ICMP"

			int icmp_complete(t_packet *packet) {
				if (!packet || !packet->icmp_header) return (1);

				ip_complete(packet);
				packet->icmp_header->checksum = 0;
				packet->icmp_header->checksum = checksum(packet->icmp_header, sizeof(t_icmp_header) + packet->payload_len);

				return (icmp_validate(packet));
			}

		#pragma endregion

		#pragma region "UDP"

			int udp_complete(t_packet *packet, uint32_t src_addr, uint32_t dst_addr) {
				if (!packet || !packet->udp_header) return (1);

				ip_complete(packet);

				packet->udp_header->length = htons(sizeof(t_udp_header) + packet->payload_len);
				packet->udp_header->checksum = 0;
				udp_set_checksum(packet->udp_header, src_addr, dst_addr, packet->payload_len, packet->payload);

				return (udp_validate(packet));
			}

		#pragma endregion

		#pragma region "TCP"

			int tcp_complete(t_packet *packet, uint32_t src_addr, uint32_t dst_addr) {
				if (!packet || !packet->tcp_header) return (1);

				ip_complete(packet);
				packet->tcp_header->length = htons(sizeof(t_tcp_header) + packet->payload_len);
				packet->tcp_header->checksum = 0;
				tcp_set_checksum(packet->tcp_header, src_addr, dst_addr, packet->payload_len, packet->payload);

				return (tcp_validate(packet));
			}

		#pragma endregion

	#pragma endregion

#pragma endregion

#pragma region "Packet"

	#pragma region "Add"

		int packet_add(t_packet *packet, void *data, uint32_t data_len, t_herdar_type header_type) {
			if (!packet || !data || !data_len) return (1);

			switch (header_type) {
				case ETHERNET:		return (ethernet_add(packet, data));			// 14 bytes
				case IP:			return (ip_add(packet, data));					// 20 bytes
				case IP_OPTION:		return (ip_option_add(packet, data));			// 0/40 bytes
				case ICMP:			return (icmp_add(packet, data));				// 8 bytes
				case UDP:			return (udp_add(packet, data));					// 8 bytes
				case TCP:			return (tcp_add(packet, data));					// 20 bytes
				case TCP_OPTION:	return (tcp_option_add(packet, data));			// 0/40 bytes
				case ARP:			return (arp_add(packet, data));					// 28 bytes
				case PAYLOAD:		return (payload_add(packet, data, data_len));
			}

			return (1);
		}

	#pragma endregion

	#pragma region "Clear"

		int packet_clear(t_packet *packet) {
			if (!packet) return (1);

			ft_memset(packet, 0, 1500);
			packet->ethernet_header = NULL;
			packet->ip_header = NULL;
			packet->ip_option = NULL;
			packet->icmp_header = NULL;
			packet->udp_header = NULL;
			packet->tcp_header = NULL;
			packet->tcp_option = NULL;
			packet->arp_header = NULL;
			packet->payload = NULL;
			packet->payload_len = 0;
			packet->packet_len = 0;

			return (0);
		}

	#pragma endregion

#pragma endregion
