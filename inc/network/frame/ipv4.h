/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipv4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 22:35:56 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <netinet/in.h>

#pragma endregion

#pragma region "Defines"

	#define VER_IHL					0x45				// Version = 4, IHL = 4

	#define DSCP_MASK				0x3F				// 6 bits (0-63)
	#define ECN_MASK				0x03				// 2 bits (0-3)
	#define DSCP_FIELD_MASK			0xFC				// Bits 7-2 (preserve DSCP  clean ECN)
	#define ECN_FIELD_MASK			0x03				// Bits 1-0 (preserve ECN   clean DSCP)

	#define DF_FLAG					0x4000				// Don't Fragment  (bit 14)
	#define MF_FLAG					0x2000				// More Fragments  (bit 13)
	#define FRAG_OFFSET_MASK		0x1FFF				// Fragment offset (bits 12-0)

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((__packed__)) {
		uint8_t		ver_ihl;						// IHL (min = 5, max = 15)
		uint8_t		dscp_ecn;						// 
		uint16_t	length;							// Length (min = 20, max = 65535)
		uint16_t	id;								// 
		uint16_t	frag;							// 
		uint8_t		ttl;							// 
		uint8_t		protocol;						// 
		uint16_t	checksum;						// 
		uint32_t	src_addr;						// 
		uint32_t	dst_addr;						// 
	}	t_ip_header;

#pragma endregion

#pragma region "Methods"

	int	ip_set_tos(t_ip_header *header, uint8_t tos);
	int	ip_set_dscp(t_ip_header *header, uint8_t dscp);
	int	ip_set_ecn(t_ip_header *header, uint8_t ecn);
	int	ip_set_length(t_ip_header *header, uint16_t data_len);
	int	ip_set_id(t_ip_header *header, uint16_t id);
	int	ip_set_df(t_ip_header *header, uint8_t frag_df);
	int	ip_set_mf(t_ip_header *header, uint8_t frag_mf);
	int	ip_set_frag_offset(t_ip_header *header, uint16_t frag_offset);
	int	ip_set_ttl(t_ip_header *header, uint8_t ttl);
	int	ip_inc_ttl(t_ip_header *header);
	int	ip_set_protocol(t_ip_header *header, uint8_t protocol);
	int	ip_set_checksum(t_ip_header *header);
	int	ip_set_src_addr(t_ip_header *header, uint32_t src_addr);
	int	ip_set_dst_addr(t_ip_header *header, uint32_t dst_addr);

	int create_ip_header(t_ip_header *header, uint8_t dscp, uint8_t ecn, uint16_t data_len, uint16_t id, uint8_t df, uint8_t mf, uint8_t frag_offset, uint8_t ttl, uint8_t protocol, uint32_t src_addr, uint32_t dst_addr);

#pragma endregion
