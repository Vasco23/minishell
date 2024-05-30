/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:05:37 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/14 18:11:58 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*newstr;
	size_t	i;

	if (!string)
		return (NULL);
	i = 0;
	newstr = (char *)malloc(ft_strlen(string) + 1);
	if (!newstr)
		return (NULL);
	while (string[i])
	{
		newstr[i] = string[i];
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
