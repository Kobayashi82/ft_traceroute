/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:26:48 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <netinet/ip_icmp.h>

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((__packed__)) {
		uint8_t		type;							// 
		uint8_t		code;							// 
		uint16_t	checksum;						// 
		union {
			struct {
				uint16_t id;						// Identificador
				uint16_t sequence;					// Número de secuencia
			} echo;									// Para Echo Request/Reply
			uint32_t gateway;						// Para mensajes como Redirect
			struct {
				uint16_t unused;					// 
				uint16_t mtu;						// 
			} frag;									// Para Fragmentation Needed
    	} un;
	}	t_icmp_header;

#pragma endregion

#pragma region "Methods"

	int	icmp_set_checksum(t_icmp_header *header, int icmp_packet_len);
	int	icmp_inc_seq(t_icmp_header *header);
	int	icmp_create_header(t_icmp_header *header, uint8_t type, uint8_t code, uint16_t id, uint16_t seq);

#pragma endregion