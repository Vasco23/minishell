/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:57:05 by miguelro          #+#    #+#             */
/*   Updated: 2023/04/19 18:32:47 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**mke_matrix(char const *str)
{
	char	**matrix;

	matrix = malloc(sizeof(char *) * (ft_count_words(str) + 1));
	if (!matrix)
		return (NULL);
	return (matrix);
}

int	word_size(char const *str, size_t start)
{
	int		cont;
	size_t	i;

	cont = 0;
	i = start;
	while (str[i] && !ft_isspace(str[i]))
	{
		cont++;
		i++;
	}
	return (cont);
}

char	**ft_split_space(char const *str)
{
	char	**matrix;
	int		i;
	int		start;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	matrix = mke_matrix(str);
	if (!matrix)
		return (NULL);
	while (i < ft_count_words(str))
	{
		while (ft_isspace(str[j]))
			j++;
		start = j;
		matrix[i++] = ft_substr(str, start, word_size(str, start));
		j += word_size(str, start);
	}
	matrix[i] = NULL;
	return (matrix);
}
