/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:34:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/04 11:20:56 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                               Ethernet Header (14 bytes)                              
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │  0  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │ 10  │ 11  │ 12  │ 13  │
    ├─────┴─────┴─────┴─────┴─────┴─────┼─────┴─────┴─────┴─────┴─────┴─────┼─────┴─────┤
    │          MAC Destination          │            MAC Source             │ Ethertype │
    └───────────────────────────────────┴───────────────────────────────────┴───────────┘
*/

#pragma region "Includes"

	#include "network/frame/ethernet.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "Set"

	#pragma region "Destination MAC"

		int ethernet_set_dst_mac(t_ethernet_header *header, const uint8_t *dst_mac) {
			if (!header || !dst_mac) return (1);

			ft_memcpy(header->dst_mac, dst_mac, 6);

			return (0);
		}

	#pragma endregion

	#pragma region "Source MAC"

		int ethernet_set_src_mac(t_ethernet_header *header, const uint8_t *src_mac) {
			if (!header || !src_mac) return (1);

			ft_memcpy(header->src_mac, src_mac, 6);

			return (0);
		}

	#pragma endregion

	#pragma region "EtherType"

		int ethernet_set_ethertype(t_ethernet_header *header, uint16_t ethertype) {
			if (!header) return (1);

			header->ethertype = htons(ethertype);

			return (0);
		}

	#pragma endregion

#pragma endregion

#pragma region "Create"

	int ethernet_create_header(t_ethernet_header *header, const uint8_t *dst_mac, const uint8_t *src_mac, uint16_t ethertype) {
		if (!header || !dst_mac || !src_mac) return (1);

		ft_memcpy(header->dst_mac, dst_mac, 6);
		ft_memcpy(header->src_mac, src_mac, 6);
		header->ethertype = htons(ethertype);

		return (0);
	}

#pragma endregion
