/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:00:16 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 15:28:00 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirections(char **cmd)
{
	int		i;
	int		redirections;
	bool	tog_sep;

	i = -1;
	redirections = 0;
	tog_sep = false;
	while (cmd[++i])
	{
		if (ft_istoken(cmd[i]) && ft_strcmp(cmd[i], "|"))
		{
			if (!tog_sep)
				redirections++;
			tog_sep = true;
		}
		else
			tog_sep = false;
	}
	return (redirections);
}

void	alloc_flags_redir(char **mat32, int cmd_it)
{
	handler()->smp_cmd[cmd_it].nmr_redir = count_redirections(mat32);
	if (handler()->smp_cmd[cmd_it].nmr_redir > 0)
	{
		(handler()->smp_cmd[cmd_it].redirections) = \
			ft_calloc(handler()->smp_cmd[cmd_it].nmr_redir, sizeof(t_lexer));
	}
	(handler()->smp_cmd[cmd_it].cmd) = \
		ft_calloc(count_arrays(mat32) + 1, sizeof(char *));
}

void	parser_reduce_lines(char **mat32, int *redi_it, int *mat_it, int cmd_it)
{
	int	flag_it;

	flag_it = -1;
	alloc_flags_redir(mat32, cmd_it);
	while (mat32[++(*mat_it)])
	{
		if (ft_istoken(mat32[(*mat_it)]) && ft_strcmp(mat32[(*mat_it)], "|"))
		{
			(*redi_it)++;
			handler()->smp_cmd[cmd_it].redirections[(*redi_it)].token = \
				ft_tokenize(mat32[(*mat_it)]);
			if (mat32[(*mat_it) + 1])
				handler()->smp_cmd[cmd_it].redirections[(*redi_it)].str = \
					ft_strdup(mat32[++(*mat_it)]);
		}
		else
			handler()->smp_cmd[cmd_it].cmd[++flag_it] = \
				ft_strdup(mat32[(*mat_it)]);
	}
}

void	create_smp_cmd(char **smp_cmd)
{
	int		mat_it;
	int		redi_it;
	char	**mat32;
	int		cmd_it;

	cmd_it = -1;
	while (smp_cmd[++cmd_it])
		handler()->smp_cmd_size++;
	(handler()->smp_cmd) = \
		ft_calloc(handler()->smp_cmd_size + 1, sizeof(t_smp_cmd));
	cmd_it = -1;
	while (smp_cmd[++cmd_it])
	{
		mat_it = -1;
		redi_it = -1;
		mat32 = ft_split(smp_cmd[cmd_it], '\2');
		parser_reduce_lines(mat32, &redi_it, &mat_it, cmd_it);
		ft_free_arr(mat32);
	}
}

void	parser(void)
{
	char	**smp_cmd;

	smp_cmd = super_split(handler()->line);
	if (!smp_cmd || smp_cmd[0][0] == '\5')
	{
		(handler()->smp_cmd) = ft_calloc(1, sizeof(t_smp_cmd));
		handler()->new_prompt = true;
		return ;
	}
	create_smp_cmd(smp_cmd);
	ft_free_arr(smp_cmd);
	verify_smp_cmd();
}
