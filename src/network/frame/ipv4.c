/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipv4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:22:05 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/03 21:10:01 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                   IP Header (20/60 bytes)                                 
    ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐
    │          0          │          1          │          2          │          3          │
    ├──────────┬──────────┼───────────────┬─────┼─────────────────────┴─────────────────────┤
    │ Version  │   IHL    │   DSCP        │ ECN │               Total Length                │
    ├──────────┴──────────┴───────────────┴─────┼───────┬───────────────────────────────────┤
    │              Identification               │ Flags │          Fragment Offset          │
    ├─────────────────────┬─────────────────────┼───────┴───────────────────────────────────┤
    │    Time to Live     │      Protocol       │              Header Checksum              │
    ├─────────────────────┴─────────────────────┴───────────────────────────────────────────┤
    │                                    Source Address                                     │
    ├───────────────────────────────────────────────────────────────────────────────────────┤
    │                                  Destination Address                                  │
    ├───────────────────────────────────────────────────────────────────────────────────────┤
    │                                                                                       │
    │                        Options (if IHL > 5) - Not implemented                         │
    │                                                                                       │
    └───────────────────────────────────────────────────────────────────────────────────────┘
*/

#pragma region "Includes"

	#include "network/frame/ipv4.h"

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

	#pragma region "DSCP/ECN"

		#pragma region "Set ToS"

			int ip_set_tos(t_ip_header *header, uint8_t tos) {
				if (!header || tos > 252) return (1);

				uint8_t dscp = (tos >> 2) & DSCP_MASK;
				header->dscp_ecn = (header->dscp_ecn & ECN_FIELD_MASK) | ((dscp & DSCP_MASK) << 2);

				return (0);
			}

		#pragma endregion

		#pragma region "Set DSCP"

			int ip_set_dscp(t_ip_header *header, uint8_t dscp) {
				if (!header || dscp > 63) return (1);

				header->dscp_ecn = (header->dscp_ecn & ECN_FIELD_MASK) | ((dscp & DSCP_MASK) << 2);

				return (0);
			}

		#pragma endregion

		#pragma region "Set ECN"

			int ip_set_ecn(t_ip_header *header, uint8_t ecn) {
				if (!header || ecn > 3) return (1);

				header->dscp_ecn = (header->dscp_ecn & DSCP_FIELD_MASK) | (ecn & ECN_MASK);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "Length"

		int ip_set_length(t_ip_header *header, uint16_t data_len) {
			if (!header) return (1);

			header->length = htons(sizeof(t_ip_header) + data_len);

			return (0);
		}

	#pragma endregion

	#pragma region "ID"

		int ip_set_id(t_ip_header *header, uint16_t id) {
			if (!header) return (1);

			header->id = htons(id);

			return (0);
		}

	#pragma endregion

	#pragma region "Fragment"

		#pragma region "Set Don't Fragment"

			int ip_set_df(t_ip_header *header, uint8_t frag_df) {
				if (!header) return (1);

				uint16_t frag = ntohs(header->frag);
				if (frag_df) frag |= DF_FLAG; else frag &= ~DF_FLAG;

				header->frag = htons(frag);

				return (0);
			}

		#pragma endregion

		#pragma region "Set More Fragments"

			int ip_set_mf(t_ip_header *header, uint8_t frag_mf) {
				if (!header) return (1);

				uint16_t frag = ntohs(header->frag);
				if (frag_mf) frag |= MF_FLAG; else frag &= ~MF_FLAG;

				header->frag = htons(frag);

				return (0);
			}

		#pragma endregion

		#pragma region "Set Fragment Offset"

			int ip_set_frag_offset(t_ip_header *header, uint16_t frag_offset) {
				if (!header || frag_offset > 8191) return (1);

				uint16_t frag = ntohs(header->frag);
				frag = (frag & ~FRAG_OFFSET_MASK) | (frag_offset & FRAG_OFFSET_MASK);
				header->frag = htons(frag);

				return (0);
			}

		#pragma endregion

	#pragma endregion

	#pragma region "TTL"

		int ip_set_ttl(t_ip_header *header, uint8_t ttl) {
			if (!header) return (1);

			header->ttl = ttl;

			return (0);
		}

	#pragma endregion

	#pragma region "Protocol"

		int ip_set_protocol(t_ip_header *header, uint8_t protocol) {
			if (!header) return (1);

			header->protocol = protocol;

			return (0);
		}

	#pragma endregion

	#pragma region "Checksum"

		int ip_set_checksum(t_ip_header *header) {
			if (!header) return (1);

			header->checksum = 0;
			header->checksum = checksum(header, sizeof(t_ip_header));

			return (0);
		}

	#pragma endregion

	#pragma region "SRC Address"

		int ip_set_src_addr(t_ip_header *header, uint32_t src_addr) {
			if (!header) return (1);

			header->src_addr = src_addr;

			return (0);
		}

	#pragma endregion

	#pragma region "DST Address"

		int ip_set_dst_addr(t_ip_header *header, uint32_t dst_addr) {
			if (!header) return (1);

			header->dst_addr = dst_addr;

			return (0);
		}

	#pragma endregion

#pragma endregion

#pragma region "Create"

	int create_ip_header(t_ip_header *header, uint8_t dscp, uint8_t ecn, uint16_t data_len, uint16_t id, uint8_t frag_df, uint8_t frag_mf, uint8_t frag_offset, uint8_t ttl, uint8_t protocol, uint32_t src_addr, uint32_t dst_addr) {
		if (!header || dscp > 63 || ecn > 3) return (1);

		header->ver_ihl = VER_IHL;
		header->dscp_ecn = ((dscp & DSCP_MASK) << 2) | (ecn & ECN_MASK);
		header->length = htons(sizeof(t_ip_header) + data_len);
		header->id = htons(id);
		header->frag = htons(((frag_df & 1) << 14) | ((frag_mf & 1) << 13) | (frag_offset & FRAG_OFFSET_MASK));
		header->ttl = ttl;
		header->protocol = protocol;
		header->checksum = 0;
		header->src_addr = src_addr;
		header->dst_addr = dst_addr;

		header->checksum = checksum(header, sizeof(t_ip_header));

		return (0);
	}

#pragma endregion
