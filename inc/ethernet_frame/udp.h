/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 14:01:41 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <netinet/in.h>

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((__packed__)) {
		uint16_t	src_port;						// 
		uint16_t	dst_port;						// 
		uint16_t	length;							// 
		uint16_t	checksum;						// 
	}	t_udp_header;

#pragma endregion

#pragma region "Methods"

	int	udp_set_data_length(t_udp_header *header, uint16_t data_len);
	int	udp_set_length(t_udp_header *header, uint16_t length);
	int	udp_set_checksum(t_udp_header *header, uint32_t src_addr, uint32_t dst_addr, uint16_t data_len, const void *data);
	int	udp_create_header_checksum(t_udp_header *header, uint16_t src_port, uint16_t dst_port, uint32_t src_addr, uint32_t dst_addr, uint16_t data_len, const void *data);
	int	udp_create_header(t_udp_header *header, uint16_t src_port, uint16_t dst_port, uint16_t length);

#pragma endregion
