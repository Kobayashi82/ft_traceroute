/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 21:09:55 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                    ICMP Header (8 bytes)                                  
    ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐
    │          0          │          1          │          2          │          3          │
    ├─────────────────────┼─────────────────────┼─────────────────────┴─────────────────────┤
    │        Type         │        Code         │                 Checksum                  │
    └─────────────────────┴─────────────────────┴───────────────────────────────────────────┘
    ┌───────────────────────────────────────────┬───────────────────────────────────────────┐
    │                    ID                     │                 Sequence                  │
    └───────────────────────────────────────────┴───────────────────────────────────────────┘
    ┌───────────────────────────────────────────────────────────────────────────────────────┐
    │                                        Gateway                                        │
    └───────────────────────────────────────────────────────────────────────────────────────┘
    ┌───────────────────────────────────────────┬───────────────────────────────────────────┐
    │                  Unused                   │                    MTU                    │
    └───────────────────────────────────────────┴───────────────────────────────────────────┘
*/

#pragma region "Includes"

	#include "network/frame/icmp.h"

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

		int icmp_set_checksum(t_icmp_header *header, uint16_t data_len) {
			if (!header || data_len < sizeof(t_icmp_header)) return (1);

			header->checksum = 0;
			header->checksum = checksum(header, sizeof(t_icmp_header) + data_len);

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

				header->un.gateway = htons(gateway);

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

	#pragma region "Echo"

		// Echo Request (8) / Echo Reply (0)
		int icmp_create_echo(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq) {
			if (!header || (type != ICMP_ECHO && type != ICMP_ECHOREPLY)) return (1);

			header->type = type;
			header->code = 0;
			header->checksum = 0;
			header->un.echo.id = htons(id);
			header->un.echo.sequence = htons(seq);

			return (0);
		}

	#pragma endregion

	#pragma region "Destination Unreachable"

		// Destination Unreachable (3)
		int icmp_create_dest_unreach(t_icmp_header *header, uint8_t code) {
			if (!header || code > 15) return (1);

			header->type = ICMP_DEST_UNREACH;
			header->code = code;
			header->checksum = 0;
			header->un.gateway = 0;						// Unused, must be zero

			return (0);
		}

	#pragma endregion

	#pragma region "Fragmentation Needed"

		// Fragmentation Needed (subtype of Destination Unreachable)
		int icmp_create_frag_needed(t_icmp_header *header, uint16_t mtu) {
			if (!header) return (1);

			header->type = ICMP_DEST_UNREACH;
			header->code = ICMP_FRAG_NEEDED;
			header->checksum = 0;
			header->un.frag.unused = 0;
			header->un.frag.mtu = htons(mtu);

			return (0);
		}

	#pragma endregion

	#pragma region "Time Exceeded"

		// Time Exceeded (11)
		int icmp_create_time_exceeded(t_icmp_header *header, uint8_t code) {
			if (!header || code > 1) return (1);

			header->type = ICMP_TIME_EXCEEDED;
			header->code = code;						// 0: TTL exceeded, 1: Fragment reassembly time exceeded
			header->checksum = 0;
			header->un.gateway = 0;						// Unused, must be zero

			return (0);
		}

	#pragma endregion

	#pragma region "Redirect"

		// Redirect (5)
		int icmp_create_redirect(t_icmp_header *header, uint8_t code, uint32_t gateway_addr) {
			if (!header || code > 3) return (1);

			header->type = ICMP_REDIRECT;
			header->code = code;						// 0: Network, 1: Host, 2: ToS+Network, 3: ToS+Host
			header->checksum = 0;
			header->un.gateway = gateway_addr;			// Gateway IP address (already in network byte order)

			return (0);
		}

	#pragma endregion

	#pragma region "Parameter Problem"

		// Parameter Problem (12)
		int icmp_create_param_problem(t_icmp_header *header, uint8_t code, uint8_t pointer) {
			if (!header || code > 2) return (1);

			header->type = ICMP_PARAMETERPROB;
			header->code = code;						// 0: Pointer indicates error, 1: Missing required option, 2: Bad length
			header->checksum = 0;
			header->un.gateway = htonl(pointer << 24);	// Pointer in the first byte, rest zeros

			return (0);
		}

	#pragma endregion

	#pragma region "Source Quench"

		// Source Quench (4) - Deprecated but still used
		int icmp_create_source_quench(t_icmp_header *header) {
			if (!header) return (1);

			header->type = ICMP_SOURCE_QUENCH;
			header->code = 0;
			header->checksum = 0;
			header->un.gateway = 0;						// Unused, must be zero

			header->checksum = checksum(header, sizeof(t_icmp_header));

			return (0);
		}

	#pragma endregion

	#pragma region "Timestamp"

		// Timestamp Request (13) / Timestamp Reply (14) - Timestamp data (originate, receive, transmit times) goes in payload
		int icmp_create_timestamp(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq) {
			if (!header || (type != ICMP_TIMESTAMP && type != ICMP_TIMESTAMPREPLY)) return (1);

			header->type = type;
			header->code = 0;
			header->checksum = 0;
			header->un.echo.id = htons(id);
			header->un.echo.sequence = htons(seq);

			return (0);
		}

	#pragma endregion

	#pragma region "Information"

		// Information Request (15) / Information Reply (16) - Obsolete
		int icmp_create_info(t_icmp_header *header, uint8_t type, uint16_t id, uint16_t seq) {
			if (!header || (type != ICMP_INFO_REQUEST && type != ICMP_INFO_REPLY)) return (1);

			header->type = type;
			header->code = 0;
			header->checksum = 0;
			header->un.echo.id = htons(id);
			header->un.echo.sequence = htons(seq);

			header->checksum = checksum(header, sizeof(t_icmp_header));

			return (0);
		}

	#pragma endregion

#pragma endregion