/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:11:44 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/04 12:56:12 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "utils/utils.h"

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

#pragma region "MEMMOVE"

	void *ft_memmove(void *dst, const void *src, int len) {
		unsigned char		*d = (unsigned char *)dst;
		const unsigned char	*s = (const unsigned char *)src;

		if (!d && !s && len) return (dst);
		if (d < s)
			while (len-- > 0) *d++ = *s++;
		else {
			d += len - 1;
			s += len - 1;
			while (len-- > 0) *d-- = *s--;
		}

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
