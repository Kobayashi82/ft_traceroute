/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 22:44:10 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                    ARP Header (28 bytes)                                  
    ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐
    │          0          │          1          │          2          │          3          │
    ├─────────────────────┴─────────────────────┼─────────────────────┴─────────────────────┤
    │             Hardware Type (1)             │          Protocol Type (0x0800)           │
    ├─────────────────────┬─────────────────────┼───────────────────────────────────────────┤
    │     Hwd Len (6)     │    Proto Len (4)    │                 Operation                 │
    ├─────────────────────┴─────────────────────┴───────────────────────────────────────────┤
    │                                Sender Hardware Address                                │
    │                                           ┌───────────────────────────────────────────┤
    │                                           │          Sender Protocol Address          │
    ├───────────────────────────────────────────┼───────────────────────────────────────────┤
    │      Sender Protocol Address (cont.)      │          Target Hardware Address          │
    ├───────────────────────────────────────────┘                                           │
    │                                                                                       │
    ├───────────────────────────────────────────────────────────────────────────────────────┤
    │                                Target Protocol Address                                │
    └───────────────────────────────────────────────────────────────────────────────────────┘
*/

#pragma region "Includes"

	#include "network/frame/arp.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "ARP Request Compare" // ft_malcolm

	int arp_cmp_request(t_arp_header *header, uint32_t spa, uint32_t tpa) {
		if (!header) return (0);

		if (ntohs(header->ptype) != ETH_P_IP)							return (0);
		if (ntohs(header->oper) != ARPOP_REQUEST)						return (0);

		if (header->spa != spa)											return (0);
		if (header->tpa != tpa)											return (0);

		uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		if (ft_memcmp(header->tha, broadcast, 6))						return (0);

		return (1);
	}

#pragma endregion

#pragma region "Set"

	#pragma region "Hardware Type"

		int arp_set_htype(t_arp_header *header, uint16_t htype) {
			if (!header) return (1);

			header->htype = htons(htype);

			return (0);
		}

	#pragma endregion

	#pragma region "Protocol Type"

		int arp_set_ptype(t_arp_header *header, uint16_t ptype) {
			if (!header) return (1);

			header->ptype = htons(ptype);

			return (0);
		}

	#pragma endregion

	#pragma region "Hardware Length"

		int arp_set_hlen(t_arp_header *header, uint8_t hlen) {
			if (!header) return (1);

			header->hlen = hlen;

			return (0);
		}

	#pragma endregion

	#pragma region "Protocol Length"

		int arp_set_plen(t_arp_header *header, uint8_t plen) {
			if (!header) return (1);

			header->plen = plen;

			return (0);
		}

	#pragma endregion

	#pragma region "Operation"

		int arp_set_oper(t_arp_header *header, uint16_t oper) {
			if (!header) return (1);

			header->oper = htons(oper);

			return (0);
		}

	#pragma endregion

	#pragma region "Source Hardware Address (MAC)"

		int arp_set_sha(t_arp_header *header, const uint8_t *sha) {
			if (!header || !sha) return (1);

			ft_memcpy(header->sha, sha, 6);

			return (0);
		}

	#pragma endregion

	#pragma region "Sender Protocol Address (IP)"

		int arp_set_spa(t_arp_header *header, uint32_t spa) {
			if (!header) return (1);

			header->spa = htons(spa);

			return (0);
		}

	#pragma endregion

	#pragma region "Target Hardware Address (MAC)"

		int arp_set_tha(t_arp_header *header, const uint8_t *tha) {
			if (!header || !tha) return (1);

			ft_memcpy(header->tha, tha, 6);

			return (0);
		}

	#pragma endregion

	#pragma region "Target Protocol Address (IP)"

		int arp_set_tpa(t_arp_header *header, uint32_t tpa) {
			if (!header) return (1);

			header->tpa = htons(tpa);

			return (0);
		}

	#pragma endregion

#pragma endregion

#pragma region "Create"

	int arp_create_header(t_arp_header *header, uint16_t oper, const uint8_t *sha, uint32_t spa, const uint8_t *tha, uint32_t tpa) {
		if (!header || (oper != ARPOP_REQUEST && oper != ARPOP_REPLY)) return (1);

		header->htype = htons(1);						// Ethernet = 1
		header->ptype = htons(ETH_P_IP);				// IPv4
		header->hlen = 6;								// MAC length = 6
		header->plen = 4;								// IP length = 4
		header->oper = htons(oper);						// Operation (Request = 1, Reply = 2)

		ft_memcpy(header->sha, sha, 6);					// Sender MAC (spoofed)
		header->spa = spa;								// Sender IP  (spoofed)

		ft_memcpy(header->tha, tha, 6);					// Target MAC
		header->tpa = tpa;								// Target IP

		return (0);
	}

#pragma endregion
