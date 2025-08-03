/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:02:13 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 19:19:41 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <arpa/inet.h>
	#include <linux/if_ether.h>

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint8_t		dst_mac[6];						// Destination MAC address
		uint8_t		src_mac[6];						// Source MAC address
		uint16_t	ethertype;						// Type of protocol (ETH_P_IP, ETH_P_ARP)
	}	t_ether_header;

#pragma endregion

#pragma region "Methods"

	int		ethernet_create_header(t_ether_header *header, const uint8_t *dst_mac, const uint8_t *src_mac, uint16_t ethertype);

#pragma endregion
