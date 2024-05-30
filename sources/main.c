/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:29 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:04:41 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitpid_op(void)
{
	int	status;

	status = 0;
	waitpid(handler()->id, &status, 0);
	handler()->child--;
	if (WIFSTOPPED(status))
		handler()->exit_status = WIFSTOPPED(status);
	else if (WIFEXITED(status))
		handler()->exit_status = WEXITSTATUS(status);
	while (handler()->child-- > 0)
		wait(&status);
}

bool	minishell_loop_initializer(void)
{
	handler()->new_prompt = false;
	handler()->child = 0;
	if (handler()->line)
		free(handler()->line);
	handler()->line = NULL;
	handler()->line = rl_get();
	if (!handler()->line[0])
		return (false);
	if (!validate_pipe(handler()->line))
	{
		ft_putstr_fd("minishell: syntax error " \
			"near unexpected token\n", 2);
		return (false);
	}
	return (true);
}

void	minishell_loop(void)
{
	while (1)
	{
		if (!minishell_loop_initializer())
			continue ;
		free_smp_cmd();
		parser();
		if (handler()->new_prompt)
			continue ;
		remove_aspas_smp();
		remove_empty_cmd();
		make_fds();
		executer();
		if (handler()->child)
			waitpid_op();
	}
}

void	initializer(char **envp)
{
	int	i;

	i = -1;
	(handler()->envp) = ft_calloc(count_arrays(envp) + 2, sizeof(char *));
	while (envp && envp[++i])
		handler()->envp[i] = ft_strdup(envp[i]);
	if (envp && *envp)
		make_export(true);
	handler()->child = 0;
	(handler()->pwd) = getcwd(NULL, 0);
	(handler()->old_pwd) = getcwd(NULL, 0);
	handler()->exit_status = 0;
	handler()->smp_cmd_size = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	initializer(envp);
	minishell_loop();
}
