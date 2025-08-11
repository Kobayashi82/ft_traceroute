/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:25:52 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 13:56:33 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "network/frame/ethernet.h"
	#include "network/frame/ip.h"
	#include "network/frame/icmp.h"
	#include "network/frame/udp.h"
	#include "network/frame/tcp.h"
	#include "network/frame/arp.h"

#pragma endregion

#pragma region "Defines"

	#define MAX_PACKET_LEN	65535

#pragma endregion

#pragma region "Enumerators"

	typedef enum e_header_type { ETHERNET, IP, ICMP, UDP, TCP, ARP, PAYLOAD, IP_OPTION, TCP_OPTION } t_herdar_type;

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint8_t				packet[MAX_PACKET_LEN];
		uint32_t			packet_len;
		t_ethernet_header	*ethernet_header;
		t_ip_header			*ip_header;
		t_ip_option			*ip_option;
		t_icmp_header		*icmp_header;
		t_udp_header		*udp_header;
		t_tcp_header		*tcp_header;
		t_tcp_option		*tcp_option;
		t_arp_header		*arp_header;
		void				*payload;
		uint16_t			payload_len;

	}	t_packet;

#pragma endregion

#pragma region "Methods"

	int	icmp_complete(t_packet *packet);
	int	udp_complete(t_packet *packet, uint32_t src_addr, uint32_t dst_addr);
	int	tcp_complete(t_packet *packet, uint32_t src_addr, uint32_t dst_addr);

	int	packet_add(t_packet *packet, void *data, uint32_t data_len, t_herdar_type header_type);
	int	packet_clear(t_packet *packet);

#pragma endregion
