/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:26:58 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "ethernet_frame/icmp.h"

#pragma endregion

#pragma region "Checksum"

	static unsigned short checksum(void *data, int len) {
		unsigned long	sum = 0;
		unsigned short	*buf = data;

		while (len > 1) { sum += *buf++; len -= 2; }
		if (len == 1) sum += *(unsigned char *)buf;
		sum = (sum >> 16) + (sum & 0xFFFF);
		sum += (sum >> 16);

		return (unsigned short)(~sum);
	}

#pragma endregion

	int icmp_set_checksum(t_icmp_header *header, int icmp_packet_len) {
		if (!header || icmp_packet_len < (int) sizeof(t_icmp_header)) return (1);

		header->checksum = 0;
		header->checksum = checksum(header, icmp_packet_len);

		return (0);
	}

	int icmp_inc_seq(t_icmp_header *header) {
		if (!header) return (1);

		header->un.echo.sequence = htons(ntohs(header->un.echo.sequence) + 1);

		return (0);
	}

#pragma region "Create"

	int icmp_create_header(t_icmp_header *header, uint8_t type, uint8_t code, uint16_t id, uint16_t seq) {
		if (!header) return (1);

		header->type = type;
		header->code = code;
		header->checksum = 0;
		header->un.echo.id = htons(id);
		header->un.echo.sequence = htons(seq);

		return (0);
	}

#pragma endregion
