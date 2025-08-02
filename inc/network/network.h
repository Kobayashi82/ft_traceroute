/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:40:48 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 14:24:07 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "network/socket.h"
	#include "ethernet_frame/ethernet.h"

#pragma endregion

#pragma region "Structures"

	typedef struct __attribute__((packed)) {
		uint32_t		packet_len;
	}	t_packet;

#pragma endregion

#pragma region "Methods"



#pragma endregion
