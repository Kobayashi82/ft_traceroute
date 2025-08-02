/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:11:17 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 11:53:38 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"



#pragma endregion

#pragma region "Defines"

	#define IPv4						0x0800		// IPv4


#pragma endregion

#pragma region "Structures"

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
