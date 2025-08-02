/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:27:34 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "ethernet_frame/arp.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "ARP Request Compare"

	int arp_cmp_request(t_arp_header *header, struct sockaddr_in *spa, struct sockaddr_in *tpa) {
		if (!header) return (0);

		if (ntohs(header->htype) != ETH_P_ARP)							return (0);
		if (ntohs(header->oper) != ARP_REQUEST)							return (0);

		if (header->spa != spa->sin_addr.s_addr)						return (0);
		if (header->tpa != tpa->sin_addr.s_addr)						return (0);

		uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		if (ft_memcmp(header->tha, broadcast, 6))						return (0);

		return (1);
	}

#pragma endregion

#pragma region "Create Header"

	int arp_create_header(t_arp_header *header, uint16_t oper, const uint8_t *sha, struct sockaddr_in *spa, const uint8_t *tha, struct sockaddr_in *tpa) {
		if (!header || !sha || !spa || !tha || !tpa || (oper != ARPOP_REQUEST && oper != ARPOP_REPLY)) return (1);

		header->htype = htons(1);						// Ethernet = 1
		header->ptype = htons(ETH_P_IP);				// IPv4 = 0x0800
		header->hlen = 6;								// MAC length = 6
		header->plen = 4;								// IP length = 4
		header->oper = htons(oper);						// Operation (Request = 1, Reply = 2)

		ft_memcpy(header->sha, sha, 6);					// Sender MAC (spoofed)
		header->spa = spa->sin_addr.s_addr;				// Sender IP  (spoofed)

		ft_memcpy(header->tha, tha, 6);					// Target MAC
		header->tpa = tpa->sin_addr.s_addr;				// Target IP

		return (0);
	}

#pragma endregion

#pragma region "Parse Header"

	int arp_parse_header(const uint8_t *packet, t_arp_header *header) {
		if (!packet || !header) return (1);

		header->htype = *(uint16_t *)packet;			// Ethernet
		header->ptype = *(uint16_t *)(packet + 2);		// IPv4
		header->hlen = *(uint8_t *)(packet + 4);		// MAC length
		header->plen = *(uint8_t *)(packet + 5);		// IP length
		header->oper = *(uint16_t *)(packet + 6);		// Operation

		ft_memcpy(header->sha, packet + 8, 6);			// Sender MAC
		header->spa = *(uint32_t *)(packet + 14);		// Sender IP

		ft_memcpy(header->tha, packet + 18, 6);			// Target MAC
		header->tpa = *(uint32_t *)(packet + 24);		// Target IP

		return (0);
	}

#pragma endregion

#pragma region "Information"

	//                          ARP Header (28 bytes)                      
	//    ┌───────────────┬───────────────┬───────────────┬───────────────┐
	//    │       0       │       1       │       2       │       3       │
	//    ├───────────────┴───────────────┼───────────────┴───────────────┤
	//    │       Hardware Type (1)       │    Protocol Type (0x0800)     │
	//    ├───────────────┬───────────────┼───────────────────────────────┤
	//    │  Hwd Len (6)  │ Proto Len (4) │           Operation           │
	//    ├───────────────┴───────────────┴───────────────────────────────┤
	//    │                    Sender Hardware Address                    │
	//    │                               ┌───────────────────────────────┤
	//    │                               │    Sender Protocol Address    │
	//    ├───────────────────────────────┼───────────────────────────────┤
	//    │Sender Protocol Address (cont.)│    Target Hardware Address    │
	//    ├───────────────────────────────┘                               │
	//    │                                                               │
	//    ├───────────────────────────────────────────────────────────────┤
	//    │                    Target Protocol Address                    │
	//    └───────────────────────────────────────────────────────────────┘

#pragma endregion
