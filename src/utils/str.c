/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:11:44 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 14:21:22 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "utils/utils.h"

#pragma endregion

#pragma region "STRLEN"

	size_t ft_strlen(const char *str) {
		size_t i = 0;

		while (str && str[i]) ++i;

		return (i);
	}

#pragma endregion

#pragma region "STRLCPY"

	int ft_strlcpy(char *dst, const char *src, int dstsize) {
		int		i = 0, srclen = 0;

		if (!src) return (0);
		while (src[srclen]) ++srclen;
		if (dstsize > 0) {
			while (dstsize > 0 && src[i] && i < dstsize - 1) { dst[i] = src[i]; ++i; }
			dst[i] = '\0';
		}

		return (srclen);
	}

#pragma endregion

