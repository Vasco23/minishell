/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:56:03 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/15 20:18:27 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_letter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	remove_line(char **mat, int sep, bool is_env)
{
	int		i;
	int		j;
	char	**new_mat;

	new_mat = ft_calloc(count_arrays(mat), sizeof(char *));
	i = -1;
	j = -1;
	while (mat && mat[++i])
	{
		if (i == sep)
			continue ;
		new_mat[++j] = ft_strdup(mat[i]);
	}
	new_mat[++j] = NULL;
	if (mat)
		ft_free_arr(mat);
	if (is_env)
		handler()->envp = new_mat;
	else
		handler()->export = new_mat;
}

void	remove_word(char *str)
{
	int	i;

	if (!str)
		return ;
	i = check_var(str, 1, handler()->export);
	if (i != -1)
		remove_line(handler()->export, i, false);
	else
		return ;
	i = check_var(str, 1, handler()->envp);
	if (i != -1)
		remove_line(handler()->envp, i, true);
	return ;
}

void	unset_call(void)
{
	int	i;

	i = 1;
	while (handler()->smp_cmd[0].cmd[i])
	{
		if (check_letter(handler()->smp_cmd[0].cmd[i], '=') == 1)
			return ;
		remove_word(handler()->smp_cmd[0].cmd[i]);
		i++;
	}
	error_handling_built_in(false);
}
