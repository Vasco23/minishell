/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:55:53 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/17 15:20:28 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_lines_export_2(int j, int i)
{
	if (check_var(handler()->smp_cmd[i].cmd[j], 0, handler()->export) >= 0)
	{
		if (check_var(handler()->smp_cmd[i].cmd[j], 0,
				handler()->envp) >= 0)
			return ;
		add_string_env(handler()->smp_cmd[i].cmd[j]);
		return ;
	}
	add_string_env(handler()->smp_cmd[i].cmd[j]);
	add_string_export(handler()->smp_cmd[i].cmd[j], 0);
}

void	export_call_aux(int i, int k, int j, int equal)
{
	int	var;

	while (handler()->smp_cmd[i].cmd[j][++k] && equal == 0)
	{
		if (handler()->smp_cmd[i].cmd[j][k] == '=')
			equal = 1;
		if (k == 0 && (handler()->smp_cmd[i].cmd[j][k] == '='))
		{
			error_handling_built_in(true);
			return (((void)write(2, "minishell: bad assignment\n", 26)));
		}
		else if (equal == 0 && !(handler()->smp_cmd[i].cmd[j][k + 1]))
		{
			var = check_var(handler()->smp_cmd[i].cmd[j], 1, handler()->export);
			if (var < 0)
				add_string_export(handler()->smp_cmd[i].cmd[j], 1);
		}
		else if (handler()->smp_cmd[i].cmd[j][k] == '='
				&& !(handler()->smp_cmd[i].cmd[j][k + 1]))
			save_lines_export_2(j, i);
		else if (handler()->smp_cmd[i].cmd[j][k] == '=')
			save_lines_export_2(j, i);
	}
}

void	export_call(int i, int j, int equal, int fd)
{
	int		k;
	bool	return_type;

	return_type = false;
	if ((i - 1) >= 0 && handler()->smp_cmd[i - 1].nmr_redir == 0 \
		&& handler()->smp_cmd[i].cmd[1])
		return ;
	else if (i + 1 < handler()->smp_cmd_size && \
		handler()->smp_cmd[i + 1].nmr_redir == 0 \
			&& handler()->smp_cmd[i].cmd[1])
		return ;
	while (handler()->smp_cmd[i].cmd[++j])
	{
		k = -1;
		if (alpha_find(handler()->smp_cmd[i].cmd[j]))
		{
			return_type = true;
			continue ;
		}
		export_call_aux(i, k, j, equal);
		equal = 0;
	}
	if (!handler()->smp_cmd[i].cmd[1])
		print_export(fd);
	error_handling_built_in(return_type);
}
