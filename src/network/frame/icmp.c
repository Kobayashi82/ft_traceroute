/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 12:49:02 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                    ICMP Header (8 bytes)                                  
    ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐
    │          0          │          1          │          2          │          3          │
    ├─────────────────────┼─────────────────────┼─────────────────────┴─────────────────────┤
    │        Type         │        Code         │                 Checksum                  │
    ├─────────────────────┴─────────────────────┴───────────────────────────────────────────┤
    │   ┌───────────────────────────────────────┬───────────────────────────────────────┐   │
    ├─> │                  ID                   │               Sequence                │ <─┤
    │   └───────────────────────────────────────┴───────────────────────────────────────┘   │
    │   ┌───────────────────────────────────────────────────────────────────────────────┐   │
    ├─> │                                    Gateway                                    │ <─┤
    │   └───────────────────────────────────────────────────────────────────────────────┘   │
    │   ┌───────────────────────────────────────┬───────────────────────────────────────┐   │
    ├─> │                Unused                 │                  MTU                  │ <─┤
    │   └───────────────────────────────────────┴───────────────────────────────────────┘   │
	└───────────────────────────────────────────────────────────────────────────────────────┘
*/

#pragma region "Includes"

	#include "network/frame/icmp.h"

#pragma endregion

#pragma region "Checksum"

	static unsigned long checksum_partial(const void *data, int len) {
		unsigned long			sum = 0;
		const unsigned short	*buf = data;

		while (len > 1) { sum += *buf++; len -= 2; }
		if (len == 1) sum += *(unsigned char *)buf;

		return (sum);
	}

	static unsigned short checksum_final(unsigned long total_sum) {
		total_sum = (total_sum >> 16) + (total_sum & 0xFFFF);
		total_sum += (total_sum >> 16);

		return (unsigned short)(~total_sum);
	}

#pragma endregion

#pragma region "Set"

	#pragma region "Type"

		int icmp_set_type(t_icmp_header *header, uint8_t type) {
			if (!header) return (1);

			header->type = type;

			return (0);
		}

	#pragma endregion

	#pragma region "Code"

		int icmp_set_code(t_icmp_header *header, uint8_t code) {
			if (!header) return (1);

			header->code = code;

			return (0);
		}

	#pragma endregion

	#pragma region "Checksum"

		int icmp_set_checksum(t_icmp_header *header, uint16_t data_len, const void *data) {
			if (!header) return (1);

			unsigned long total_sum = 0;

			header->checksum = 0;
			total_sum += checksum_partial(header, sizeof(t_icmp_header));

			if (data && data_len > 0) total_sum += checksum_partial(data, data_len);

			header->checksum = htons(checksum_final(total_sum));

			return (0);
		}

	#pragma endregion

	#pragma region "ECHO"

		#pragma region "ID"

			int icmp_set_id(t_icmp_header *header, uint16_t id) {
				if (!header) return (1);

				header->un.echo.id = htons(id);

				return (0);
			}

		#pragma endregion

		#pragma region "Sequence"
		
			int icmp_set_seq(t_icmp_header *header, uint16_t seq) {
				if (!header) return (1);

				header->un.echo.sequence = htons(seq);

				return (0);
			}

			int icmp_inc_seq(t_icmp_header *header) {
				if (!header) return (1);

				uint16_t seq = ntohs(header->un.echo.sequence);
				header->un.echo.sequence = htons(seq + 1);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "GATEWAY"

		#pragma region "Gateway"

			int icmp_set_gateway(t_icmp_header *header, uint32_t gateway) {
				if (!header) return (1);

				header->un.gateway = gateway;

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "FRAG"

		#pragma region "MTU"

			int icmp_set_mtu(t_icmp_header *header, uint16_t mtu) {
				if (!header) return (1);

				header->un.frag.mtu = htons(mtu);

				return (0);
			}

		#pragma endregion

	#pragma endregion

#pragma endregion

#pragma region "Create"

	#pragma region "(8) Echo Request"

		// Send ping request to test host reachability and measure round-trip time (RTT)
		// Payload (optional): Originate timestamp + pattern
		int icmp_create_echo(t_icmp_header *header, uint16_t id, uint16_t seq) {
			if (!header) return (1);

			header->type = ICMP_ECHO;
			header->code = 0;
			header->checksum = 0;
			header->un.echo.id = htons(id);
			header->un.echo.sequence = htons(seq);

			return (0);
		}

	#pragma endregion

	#pragma region "(13) Timestamp"

		// Measure network round-trip time and clock differences
		// Payload: Originate timestamp + space for receive and transmit timestamp (16 bytes)
		int icmp_create_timestamp(t_icmp_header *header, uint16_t id, uint16_t seq) {
			if (!header) return (1);

			header->type = ICMP_TIMESTAMP;
			header->code = 0;
			header->checksum = 0;
			header->un.echo.id = htons(id);
			header->un.echo.sequence = htons(seq);

			return (0);
		}

	#pragma endregion

#pragma endregion
