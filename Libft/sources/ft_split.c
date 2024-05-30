/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:35:05 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/13 17:05:40 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cont_words(const char	*str, const char c)
{
	int	i;
	int	words;

	i = 0;
	words = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			words++;
		i++;
	}
	if (str[0] == c)
		words--;
	if (str[ft_strlen(str)-1] == c)
		words--;
	return (words);
}

char	**make_matrix(char const *str, char c)
{
	char	**matrix;

	matrix = malloc(sizeof(char *) * (cont_words(str, c) + 1));
	if (!matrix)
		return (NULL);
	return (matrix);
}

int	word_len(char const *str, char c, size_t start)
{
	int		cont;
	size_t	i;

	cont = 0;
	i = start;
	while (str[i] != c && str[i])
	{
		cont++;
		i++;
	}
	return (cont);
}

char	**ft_split(char const *str, char c)
{
	char	**matrix;
	int		i;
	int		start;
	size_t	j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	matrix = make_matrix(str, c);
	if (!matrix)
		return (NULL);
	if (str[0] != c && str[0] != 0)
		matrix[i++] = ft_substr(str, 0, word_len(str, c, 0));
	while (i < cont_words(str, c))
	{
		if ((str[j] == c && str[j + 1] != c))
		{
			start = j + 1;
			matrix[i++] = ft_substr(str, start, word_len(str, c, start));
		}
		j++;
	}
	matrix[i] = NULL;
	return (matrix);
}
