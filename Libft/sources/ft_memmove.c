/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:04:57 by marvin            #+#    #+#             */
/*   Updated: 2022/08/06 19:04:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*pd;
	char	*ps;
	size_t	i;

	pd = (char *)dest;
	ps = (char *)src;
	if (pd < ps)
	{
		i = 0;
		while (i < n)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	if (pd > ps)
	{
		i = n;
		while (i > 0)
		{
			pd[i - 1] = ps[i - 1];
			i--;
		}
	}
	return (dest);
}
