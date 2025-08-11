/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 12:58:00 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                  TCP Header (20/60 bytes)                                 
    ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐
    │          0          │          1          │          2          │          3          │
    ├─────────────────────┴─────────────────────┼─────────────────────┴─────────────────────┤
    │                Source Port                │             Destination Port              │
    ├───────────────────────────────────────────┴───────────────────────────────────────────┤
    │                                    Sequence Number                                    │
    ├───────────────────────────────────────────────────────────────────────────────────────┤
    │                 Acknowledgement Number (meaningful when ACK bit set)                  │
    ├──────────┬──────────┬──┬─┬─┬─┬─┬─┬─┬─┬─┬──┬───────────────────────────────────────────┤
    │   Data   │          │  │C│E│U│A│R│P│S│F│  │                                           │
    │  Offset  │ Reserved │  │W│C│R│C│S│S│Y│I│  │                  Windows                  │
    │          │          │  │R│E│G│K│T│H│N│N│  │                                           │
    ├──────────┴──────────┴──┴─┴─┴─┴─┴─┴─┴─┴─┴──┼───────────────────────────────────────────┤
    │                 Checksum                  │  Urgent Pointer (only when URG bit set)   │
    ├───────────────────────────────────────────┴───────────────────────────────────────────┤
    │               (Options) If present, Data Offset will be greater than 5                │
    │                  Padded with zeroes to a multiple of 32 bits, since                   │
    │                Data Offset counts words of 4 octets (not implemented)                 │
    ├───────────────────────────────────────────────────────────────────────────────────────┤
    │                                                                                       │
    │                                         Data                                          │
    │                                                                                       │
    └───────────────────────────────────────────────────────────────────────────────────────┘
*/

#pragma region "Includes"

	#include "network/frame/tcp.h"

#pragma endregion

#pragma region "Checksum"

	static unsigned long checksum_partial(const void *data, int len) {
		unsigned long			sum = 0;
		const unsigned short	*buf = data;

		while (len > 1) { sum += *buf++; len -= 2; }
		if (len == 1) sum += *(unsigned char *)buf;

		return (sum);
	}

	static unsigned short checksum(unsigned long total_sum) {
		total_sum = (total_sum >> 16) + (total_sum & 0xFFFF);
		total_sum += (total_sum >> 16);

		return (unsigned short)(~total_sum);
	}

#pragma endregion

#pragma region "Set Data Length"

	int tcp_set_data_length(t_tcp_header *header, uint16_t data_len) {
		if (!header) return (1);

		header->length = sizeof(t_tcp_header) + data_len;

		return (0);
	}

#pragma endregion

#pragma region "Set Length"

	int tcp_set_length(t_tcp_header *header, uint16_t length) {
		if (!header) return (1);
		if (length < sizeof(t_tcp_header)) length = sizeof(t_tcp_header);

		header->length = htons(length);

		return (0);
	}

#pragma endregion

#pragma region "Set Checksum"

	int tcp_set_checksum(t_tcp_header *header, uint32_t src_addr, uint32_t dst_addr, uint16_t data_len, const void *data) {
		if (!header) return (1);
		if (!data) data_len = 0;

		unsigned long total_sum = 0;

		struct __attribute__((__packed__)) {
			uint32_t	src_addr;						// 
			uint32_t	dst_addr;						// 
			uint8_t		zeroes;							// 
			uint8_t		protocol;						// 
			uint16_t	length;							// 
		}	pseudo_header;

		pseudo_header.src_addr = src_addr;
		pseudo_header.dst_addr = dst_addr;
		pseudo_header.zeroes = 0;
		pseudo_header.protocol = IPPROTO_TCP;
		pseudo_header.length = htons(sizeof(t_tcp_header) + data_len);
		// pseudo_header.length = htons(sizeof(t_tcp_header) + tcp_options_len + data_len);
		total_sum += checksum_partial(&pseudo_header, sizeof(pseudo_header));

		header->length = htons(sizeof(t_tcp_header) + data_len);
		header->checksum = 0;
		total_sum += checksum_partial(header, sizeof(t_tcp_header));

		if (data && data_len > 0) total_sum += checksum_partial(data, data_len);

		header->checksum = checksum(total_sum);

		return (0);
	}

#pragma endregion

#pragma region "Create"

	// int tcp_create_header(t_tcp_header *header, uint16_t src_port, uint16_t dst_port, uint32_t seq, uint32_t ack_num) {
	// 	if (!header || !dst_port ) return (1);

	// 	header->src_port = htons(src_port);
	// 	header->dst_port = htons(dst_port);
	// 	header->length = htons(sizeof(t_tcp_header) + data_len);
	// 	header->checksum = 0;

	// 	return (0);
	// }

#pragma endregion
