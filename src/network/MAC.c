/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MAC.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:03:08 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/01 19:17:53 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "network/network.h"
	#include "utils/utils.h"

#pragma endregion

#pragma region "MAC"

	#pragma region "Is Broadcast"

		int is_broadcast_mac(const uint8_t *mac) {
			return (mac && mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF && mac[3] == 0xFF && mac[4] == 0xFF && mac[5] == 0xFF);
		}

	#pragma endregion

	#pragma region "Is Multicast"

		int is_multicast_mac(const uint8_t *mac) {
			return (mac && mac[0] & 0x01);
		}

	#pragma endregion

#pragma endregion
