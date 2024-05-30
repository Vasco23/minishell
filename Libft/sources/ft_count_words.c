/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:29:08 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/19 14:08:55 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			words++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (words);
}
