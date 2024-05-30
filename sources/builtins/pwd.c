/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:26:43 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 16:19:30 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int fd)
{
	char	buff[FILENAME_MAX];
	char	*path;

	path = getcwd(buff, FILENAME_MAX);
	if (!path)
	{
		error_handling_built_in(true);
		return ;
	}
	if (path)
		write(fd, path, strlen(path));
	write(fd, "\n", 1);
	error_handling_built_in(false);
}
