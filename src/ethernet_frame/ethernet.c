/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:34:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:27:48 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "ethernet_frame/ethernet.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "Create Header"

	int ethernet_create_header(t_ether_header *header, const uint8_t *dest_mac, const uint8_t *src_mac, uint16_t ethertype) {
		if (!header || !dest_mac || !src_mac) return (1);

		ft_memcpy(header->dest_mac, dest_mac, 6);
		ft_memcpy(header->src_mac, src_mac, 6);
		header->ethertype = htons(ethertype);

		return (0);
	}

#pragma endregion

#pragma region "Parse Header"

	int ethernet_parse_header(const uint8_t *packet, t_ether_header *header) {
		if (!packet || !header) return (1);

		ft_memcpy(header->dest_mac, packet, 6);
		ft_memcpy(header->src_mac, packet + 6, 6);
		header->ethertype = ntohs(*(uint16_t *)(packet + 12));

		return (0);
	}

#pragma endregion
