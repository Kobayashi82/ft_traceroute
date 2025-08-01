/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:38 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/01 19:17:16 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "main/options.h"
	#include "network/network.h"

#pragma endregion

#pragma region "Structures"

	typedef struct s_traceroute {
		bool			running;
		char			*name;
		t_options		options;
	}	t_traceroute;

#pragma endregion

#pragma region "Variables"

	extern t_traceroute g_traceroute;

#pragma endregion

#pragma region "Methods"



#pragma endregion
