/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:25:52 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/04 11:25:53 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "network/frame/ethernet.h"
	#include "network/frame/ipv4.h"
	#include "network/frame/icmp.h"
	#include "network/frame/udp.h"
	#include "network/frame/tcp.h"
	#include "network/frame/arp.h"

#pragma endregion

#pragma region "Defines"

	#define MAX_PACKET_LEN	65535

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint8_t				packet[MAX_PACKET_LEN];
		uint32_t			packet_len;
		t_ethernet_header	*ethernet_header;
		t_ip_header			*ip_header;
		t_icmp_header		*icmp_header;
		t_udp_header		*udp_header;
		t_tcp_header		*tcp_header;
		t_arp_header		*arp_header;
		void				*payload;
	}	t_packet;

#pragma endregion

#pragma region "Methods"



#pragma endregion
