/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:12:28 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/04 12:56:43 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <stdio.h>
	#include <stdint.h>

#pragma endregion

#pragma region "Methods"

	// STR
	size_t	ft_strlen(const char *str);
	int		ft_strlcpy(char *dst, const char *src, int dstsize);
	// MEM
	int		ft_memcmp(const void *s1, const void *s2, int n);
	void	*ft_memcpy(void *dst, const void *src, int n);
	void	*ft_memmove(void *dst, const void *src, int len);
	void	*ft_memset(void *b, int c, int len);
	// MAC
	int		is_broadcast_mac(const uint8_t *mac);
	int		is_multicast_mac(const uint8_t *mac);

#pragma endregion
