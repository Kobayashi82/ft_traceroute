/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:12:28 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 13:54:08 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <stdio.h>

#pragma endregion

#pragma region "Methods"

	size_t	ft_strlen(const char *str);
	int		ft_strlcpy(char *dst, const char *src, int dstsize);
	int		ft_memcmp(const void *s1, const void *s2, int n);
	void	*ft_memcpy(void *dst, const void *src, int n);
	void	*ft_memset(void *b, int c, int len);

#pragma endregion
