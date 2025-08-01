/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:11:44 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/01 19:18:00 by vzurera-         ###   ########.fr       */
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

#pragma region "MEMCMP"

	int ft_memcmp(const void *s1, const void *s2, int n) {
		unsigned char	*str1 = (unsigned char *)s1;
		unsigned char	*str2 = (unsigned char *)s2;
		int				i = 0;

		while ((*str1 == *str2) && i < n - 1 && n > 0) {
			str1++; str2++; i++;
		}

		if ((!*str1 && !*str2) || i == n) return (0);

		return (*str1 - *str2);
	}

#pragma endregion

#pragma region "MEMCPY"

	void *ft_memcpy(void *dst, const void *src, int n) {
		unsigned char		*d = (unsigned char *)dst;
		const unsigned char	*s = (const unsigned char *)src;

		if (!n || (!d && !s && n)) return (dst);
		while (n-- > 0) *d++ = *s++;

		return (dst);
	}

#pragma endregion

#pragma region "MEMSET"

	void *ft_memset(void *b, int c, int len) {
		unsigned char	*p = b;

		while (len--) *p++ = (unsigned char)c;

		return (b);
	}

#pragma endregion
