/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:02:20 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/15 15:14:23 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	cursor[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || FOPEN_MAX < fd)
		return (NULL);
	line = NULL;
	while (cursor[fd][0] || read(fd, cursor[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin2(line, cursor[fd]);
		if (ft_strlen(cursor[fd]) == 0)
			return (line);
		if (ft_clean(cursor[fd]) == 1)
			break ;
		if (read(fd, cursor[fd], 0) < 0)
		{
			free (line);
			return (NULL);
		}
	}
	return (line);
}
