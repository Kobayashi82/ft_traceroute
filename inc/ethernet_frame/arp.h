/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:27:23 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <arpa/inet.h>
	#include <net/if_arp.h>
	#include <net/ethernet.h>

#pragma endregion

#pragma region "Defines"

	#define IPv4						0x0800		// IPv4
	#define ARP							0x0806		// Address Resolution Protocol
	#define ARP_REQUEST					1			// ARP Request operation
	#define ARP_REPLY					2			// ARP Reply operation

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((__packed__)) {
		uint16_t	htype;							// Hardware Type			(Ethernet = 1)
		uint16_t	ptype;							// Protocol Type			(IPv4 = 0x0800)
		uint8_t		hlen;							// Hardware Length			(MAC length = 6)
		uint8_t		plen;							// Protocol Length			(IP length = 4)
		uint16_t	oper;							// Operation				(Request = 1, Reply = 2)
		uint8_t		sha[6];							// Sender Hardware Address	(MAC)
		uint32_t	spa;							// Sender protocol address	(IP)
		uint8_t		tha[6];							// Target hardware address	(MAC)
		uint32_t	tpa;							// Target protocol address	(IP)
	}	t_arp_header;

#pragma endregion

#pragma region "Methods"

	int	arp_cmp_request(t_arp_header *header, struct sockaddr_in *spa, struct sockaddr_in *tpa);
	int	arp_create_header(t_arp_header *header, uint16_t oper, const uint8_t *sha, struct sockaddr_in *spa, const uint8_t *tha, struct sockaddr_in *tpa);
	int	arp_parse_header(const uint8_t *packet, t_arp_header *header);

#pragma endregion
