/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:03:23 by marvin            #+#    #+#             */
/*   Updated: 2023/08/15 19:16:07 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pd;
	const unsigned char	*ps;

	i = 0;
	pd = (unsigned char *)dest;
	ps = (unsigned char *)src;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dest);
}
