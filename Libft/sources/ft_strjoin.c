/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:38:32 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/19 14:10:09 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*finstr;

	if (!s1 || !s2)
		return (NULL);
	finstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!finstr)
		return (NULL);
	ft_strlcpy(finstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(finstr, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (finstr);
}
