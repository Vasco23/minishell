/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:56:12 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 16:19:07 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_call(int fd, int j)
{
	int	i;

	i = 0;
	if (handler()->envp && *handler()->envp && !handler()->smp_cmd[j].cmd[1])
	{
		while (handler()->envp[i])
		{
			write(fd, handler()->envp[i], ft_strlen(handler()->envp[i]));
			i++;
			write(fd, "\n", 1);
		}
		error_handling_built_in(false);
		return ;
	}
	error_handling_built_in(true);
}
