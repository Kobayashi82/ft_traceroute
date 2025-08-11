/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 12:58:20 by vzurera-         ###   ########.fr       */
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
		uint16_t	length;							// (header + payload)
		uint16_t	checksum;						// (pseudo header + header + payload)
	}	t_tcp_header;

	typedef struct __attribute__((__packed__)) {
		uint8_t		options[40];					// 
		uint8_t		length;							// 
	}	t_tcp_option;

#pragma endregion

#pragma region "Methods"

	int	tcp_set_data_length(t_tcp_header *header, uint16_t data_len);
	int	tcp_set_length(t_tcp_header *header, uint16_t length);
	int	tcp_set_checksum(t_tcp_header *header, uint32_t src_addr, uint32_t dst_addr, uint16_t data_len, const void *data);

	// int	tcp_create_header(t_tcp_header *header, uint16_t src_port, uint16_t dst_port, uint16_t length);

#pragma endregion
