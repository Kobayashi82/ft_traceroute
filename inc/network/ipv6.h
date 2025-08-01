/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipv6.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/01 19:26:53 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <stdint.h>

#pragma endregion

#pragma region "Defines"



#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint8_t		dest_mac[6];					// Destination MAC address
		uint8_t		src_mac[6];						// Source MAC address
		uint16_t	tpid;							// Tag Protocol Identifier (indicates presence of a VLAN tag)
		uint16_t	tci;							// Tag Control Information (contains priority (PCP), drop eligibility (DEI), and VLAN ID (VID))
		uint16_t	ethertype;						// Type of next protocol (IPv4, IPv6, ARP, WOL)
	}	t_ether_vheader;

	typedef struct __attribute__((packed)) {
		uint8_t		dest_mac[6];					// Destination MAC address
		uint8_t		src_mac[6];						// Source MAC address
		uint16_t	ethertype;						// Type of next protocol (IPv4, IPv6, ARP, WOL)
	}	t_ether_header;

#pragma endregion

#pragma region "Information"



#pragma endregion
