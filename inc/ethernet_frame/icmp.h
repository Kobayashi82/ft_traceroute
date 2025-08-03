/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 17:55:12 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <netinet/ip_icmp.h>

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((__packed__)) {
		uint8_t		type;							// ICMP message type
		uint8_t		code;							// ICMP subtype/code
		uint16_t	checksum;						// Checksum of ICMP header and data
		union {
			struct {
				uint16_t id;						// Identifier (used to match request and reply)
				uint16_t sequence;					// Sequence number (for tracking order)
			} echo;
			uint32_t gateway;						// Used for Redirect messages
			struct {
				uint16_t unused;					// Unused (set to zero)
				uint16_t mtu;						// MTU of the next hop (used in Fragmentation Needed)
			} frag;
    	} un;
	}	t_icmp_header;

#pragma endregion

#pragma region "Methods"

	int	icmp_set_checksum(t_icmp_header *header, uint16_t data_len);
	int	icmp_set_id(t_icmp_header *header, uint16_t id);
	int	icmp_set_seq(t_icmp_header *header, uint16_t seq);
	int	icmp_inc_seq(t_icmp_header *header);
	int	icmp_set_gateway(t_icmp_header *header, uint32_t gateway);
	int	icmp_set_mtu(t_icmp_header *header, uint16_t mtu);

	int	icmp_create_echo(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq);
	int	icmp_create_dest_unreach(t_icmp_header *header, uint8_t code);
	int	icmp_create_frag_needed(t_icmp_header *header, uint16_t mtu);
	int	icmp_create_time_exceeded(t_icmp_header *header, uint8_t code);
	int	icmp_create_redirect(t_icmp_header *header, uint8_t code, uint32_t gateway_addr);
	int	icmp_create_param_problem(t_icmp_header *header, uint8_t code, uint8_t pointer);
	int	icmp_create_source_quench(t_icmp_header *header);
	int	icmp_create_timestamp(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq);
	int	icmp_create_info(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq);

#pragma endregion