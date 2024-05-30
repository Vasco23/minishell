/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:16:39 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/06 15:34:56 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		v;
	char	*newstr;

	i = 0;
	v = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1 && s1[v])
		newstr[i++] = s1[v++];
	v = 0;
	while (s2 && s2[v])
	{
		newstr[i] = s2[v++];
		if (newstr[i++] == '\n')
			break ;
	}
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nwl;

	i = 0;
	j = 0;
	is_nwl = 0;
	while (str[i])
	{
		if (is_nwl)
			str[j++] = str[i];
		if (str[i] == '\n')
			is_nwl = 1;
		str[i] = '\0';
		i++;
	}
	return (is_nwl);
}
