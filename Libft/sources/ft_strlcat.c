/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:19 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/19 14:10:31 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	src_index;

	if (!dst || !src)
		return (-1);
	srclen = ft_strlen(src);
	dstlen = 0;
	src_index = 0;
	while (dst[dstlen] && dstlen < size)
		dstlen++;
	while (src[src_index] && (dstlen + src_index + 1) < size)
	{
		dst[dstlen + src_index] = src[src_index];
		src_index++;
	}
	if (dstlen < size)
		dst[dstlen + src_index] = 0;
	return (dstlen + srclen);
}
