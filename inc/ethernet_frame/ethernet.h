/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:02:13 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:27:52 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <arpa/inet.h>

#pragma endregion

#pragma region "Defines"

	// EtherTypes
	#define IPv4						0x0800		// IPv4
	#define ARP							0x0806		// Address Resolution Protocol
	#define WOL							0x0842		// Wake-On-LAN
	#define VLAN						0x8100		// VLAN Tagging
	#define MPLS						0x8847		// Multiprotocol Label Switching
	#define MPLS_MULTI					0x8848		// Multiprotocol Label Switching Multicast
	#define LLDP						0x88CC		// Link Layer Discovery Protocol
	#define PPPoE_Discovery				0x880B		// PPPoE Discovery
	#define PPPoE_Session				0x880C		// PPPoE Session
	#define IPv6						0x86DD		// IPv6

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint8_t		dest_mac[6];					// Destination MAC address
		uint8_t		src_mac[6];						// Source MAC address
		uint16_t	ethertype;						// Type of next protocol (IPv4, IPv6, ARP, WOL)
	}	t_ether_header;

#pragma endregion

#pragma region "Methods"

	int		ethernet_create_header(t_ether_header *header, const uint8_t *dest_mac, const uint8_t *src_mac, uint16_t ethertype);
	int		ethernet_parse_header(const uint8_t *packet, t_ether_header *header);

#pragma endregion
