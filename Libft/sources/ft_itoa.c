/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:55:48 by miguelro          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:26 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*makestr(size_t size, long nbr)
{
	char	*str;

	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	str[size--] = 0;
	while (nbr > 0)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] != '\0')
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = (long)n;
	size = 0;
	if (n < 0)
	{
		nbr = -nbr;
		size++;
	}
	if (n == 0)
	{
		str = (char *)malloc(2);
		*str = '0';
		str[1] = 0;
		return (str);
	}
	while (n)
	{
		n /= 10;
		size++;
	}
	return (makestr(size, nbr));
}
