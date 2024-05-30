/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:15:22 by miguelro          #+#    #+#             */
/*   Updated: 2022/11/03 14:55:04 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	i;

	if (!str)
		return (0);
	while (*str && ft_strchr(set, *str))
		str++;
	i = ft_strlen(str);
	while (i && ft_strrchr(set, str[i]))
		i--;
	return (ft_substr(str, 0, i + 1));
}
