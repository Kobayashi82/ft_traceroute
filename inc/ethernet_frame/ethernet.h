/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:02:13 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/01 19:02:33 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <arpa/inet.h>

#pragma endregion

#pragma region "Defines"

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

	#define VLAN_PCP_ROUTINE			0			// Routine traffic (lowest priority)
	#define VLAN_PCP_VIDEO1				1			// Video/Voice traffic
	#define VLAN_PCP_VIDEO2				2			// Video/Voice traffic
	#define VLAN_PCP_VIDEO3				3			// Video/Voice traffic
	#define VLAN_PCP_BEST_EFFORT		4			// Best-effort (web browsing)
	#define VLAN_PCP_BULK_DATA			5			// Bulk data (non-urgent)
	#define VLAN_PCP_BACKGROUND			6			// Background traffic
	#define VLAN_PCP_CRITICAL			7			// Critical traffic (emergency)

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

	// Estructura con VLAN:			[ dst_mac ][ src_mac ][ TPID=0x8100 ][ TCI ][ ethertype ][ payload ]
	//									 6          6            2          2         2        ...

	// Estructura sin VLAN:			[ dst_mac ][ src_mac ][ ethertype ][ payload ]
	//									 6          6           2        ...

	// Valores de PCP y su significado:
	// 
	// |-----|--------------------|---------------------------------------------|
	// | PCP |     Prioridad      |                 Descripción                 |
	// |-----|--------------------|---------------------------------------------|
	// |  0  | Routine traffic	  | Tráfico estándar (menos prioritario)        |
	// |  1  | Video/Voice        | Tráfico de voz o video                      |
	// |  2  | Video/Voice        | Tráfico de voz o video                      |
	// |  3  | Video/Voice        | Tráfico de voz o video                      |
	// |  4  | Best effort        | Tráfico común (navegación web)              |
	// |  5  | Bulk data          | Tráfico de datos no urgente                 |
	// |  6  | Background traffic | Tráfico de fondo (menos importante)         |
	// |  7  | Critical traffic	  | Tráfico de alta prioridad (ej. emergencias) |
	// |-----|--------------------|---------------------------------------------|

#pragma endregion
