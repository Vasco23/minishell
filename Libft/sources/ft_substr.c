/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:22:28 by miguelro          #+#    #+#             */
/*   Updated: 2022/11/03 15:34:43 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	sub_len;
	char	*substr;

	i = start;
	j = 0;
	sub_len = 0;
	if (!str)
		return (0);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	while (sub_len < len && str[i++])
		sub_len++;
	i = start;
	substr = (char *)malloc(sub_len + 1);
	if (!substr)
		return (NULL);
	while (i < ft_strlen(str) && j < sub_len)
		substr[j++] = str[i++];
	substr[j] = 0;
	return (substr);
}
