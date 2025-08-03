/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:30 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 19:46:50 by vzurera-         ###   ########.fr       */
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
		uint32_t	spa;							// Sender Protocol Address	(IP)
		uint8_t		tha[6];							// Target hardware address	(MAC)
		uint32_t	tpa;							// Target Protocol Address	(IP)
	}	t_arp_header;

#pragma endregion

#pragma region "Methods"

	int arp_cmp_request(t_arp_header *header, uint32_t spa, uint32_t tpa);

	int	ethernet_set_htype(t_arp_header *header, uint16_t htype);
	int	ethernet_set_ptype(t_arp_header *header, uint16_t ptype);
	int	ethernet_set_hlen(t_arp_header *header, uint8_t hlen);
	int	ethernet_set_plen(t_arp_header *header, uint8_t plen);
	int	ethernet_set_oper(t_arp_header *header, uint16_t oper);
	int	ethernet_set_sha(t_arp_header *header, const uint8_t *sha);
	int	ethernet_set_spa(t_arp_header *header, uint32_t spa);
	int	ethernet_set_tha(t_arp_header *header, const uint8_t *tha);
	int	ethernet_set_tpa(t_arp_header *header, uint32_t tpa);

	int arp_create_header(t_arp_header *header, uint16_t oper, const uint8_t *sha, uint32_t spa, const uint8_t *tha, uint32_t tpa);

#pragma endregion
