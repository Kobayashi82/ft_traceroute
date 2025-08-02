/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethernet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:34:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 12:41:59 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "ethernet_frame/ethernet.h"
	#include "utils/utils.h"

	#include <arpa/inet.h>

#pragma endregion

#pragma region "VLAN"

	#pragma region "Create VLAN Header"

		int create_ethernet_vheader(t_ether_vheader *header, const uint8_t *dest_mac, const uint8_t *src_mac, uint16_t vid, uint8_t dei, uint8_t pcp, uint16_t ethertype) {
			if (!header || !dest_mac || !src_mac)  return (1);
			if (vid >= 4095 || dei > 1 || pcp > 7) return (1);

			ft_memcpy(header->dest_mac, dest_mac, 6);
			ft_memcpy(header->src_mac, src_mac, 6);
			header->tpid = htons(VLAN);
			header->tci = htons((((pcp & 0x7) << 13) | ((dei & 0x1) << 12) | (vid & 0x0FFF)));
			header->ethertype = htons(ethertype);

			return (0);
		}

	#pragma endregion

	#pragma region "Parse VLAN Header"

		int parse_ethernet_vheader(const uint8_t *packet, t_ether_vheader *header) {
			if (!packet || !header) return (1);

			ft_memcpy(header->dest_mac, packet, 6);
			ft_memcpy(header->src_mac, packet + 6, 6);
			header->tpid = ntohs(*(uint16_t *)(packet + 12));
			header->tci = ntohs(*(uint16_t *)(packet + 14));
			header->ethertype = ntohs(*(uint16_t *)(packet + 16));

			return (0);
		}

	#pragma endregion

	#pragma region "Extract VLAN fields"

		void extract_vlan_fields(uint16_t tci, uint16_t *vid, uint8_t *dei, uint8_t *pcp) {
			if (vid) *vid = tci & 0x0FFF;
			if (dei) *dei = (tci >> 12) & 0x01;
			if (pcp) *pcp = (tci >> 13) & 0x07;
		}

	#pragma endregion

	#pragma region "Has VLAN Tag"

		int has_vlan_tag(const uint8_t *packet) {
			if (!packet) return (-1);

			uint16_t tpid = ntohs(*(uint16_t *)(packet + 12));
			return (tpid == VLAN);
		}

	#pragma endregion

#pragma endregion

#pragma region "Normal"

	#pragma region "Create Header"

		int create_ethernet_header(t_ether_header *header, const uint8_t *dest_mac, const uint8_t *src_mac, uint16_t ethertype) {
			if (!header || !dest_mac || !src_mac) return (1);

			ft_memcpy(header->dest_mac, dest_mac, 6);
			ft_memcpy(header->src_mac, src_mac, 6);
			header->ethertype = htons(ethertype);

			return (0);
		}

	#pragma endregion

	#pragma region "Parse Header"

		int parse_ethernet_header(const uint8_t *packet, t_ether_header *header) {
			if (!packet || !header) return (1);
			
			ft_memcpy(header->dest_mac, packet, 6);
			ft_memcpy(header->src_mac, packet + 6, 6);
			header->ethertype = ntohs(*(uint16_t *)(packet + 12));
			
			return (0);
		}

	#pragma endregion

#pragma endregion

//     t_ether_vheader header;
//     uint8_t dest_mac[6] = { 0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E };
//     uint8_t src_mac[6] = { 0x00, 0x5F, 0x6A, 0x7B, 0x8C, 0x9D };

//     // Crear encabezado con VLAN 2, prioridad 4, Ethertype ARP (0x0806)
//     create_ethernet_vheader(&header, dest_mac, src_mac, 0x8100, 0x0810, 0x1, 0x0806);
