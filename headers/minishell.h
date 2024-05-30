/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:31:21 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:41:29 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

//enum de redireções
typedef enum s_tokens
{
	GREAT = 2,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}				t_tokens;

//array de words com o bool token que indica
//se a palavra atual é um token
typedef struct s_lexer
{
	char		*str;
	t_tokens	token;

}				t_lexer;

//representa um commando simples e as suas redirections
//ex: ls-la > output.txt < intput.txt
typedef struct s_smp_cmd
{
	char		**cmd;
	int			fds[2];
	int			nmr_redir;
	t_lexer		*redirections;

}				t_smp_cmd;

//estrutura estática com todas as variaveis neçessárias
typedef struct s_handler
{
	char		*line;
	char		**envp;
	char		**export;
	char		*pwd;
	char		*old_pwd;
	char		*command_path;
	int			lexer_size;
	int			smp_cmd_size;
	bool		red;
	int			built_in;
	int			file_fd;
	int			child;
	int			fds_tmp[2];
	int			id;
	int			exit_status;
	int			last_cmd;
	bool		change_env;
	bool		new_prompt;
	bool		here_doc;
	t_smp_cmd	*smp_cmd;

}				t_handler;

t_handler		*handler(void);

//bultins
void			pwd(int fd);
void			echo(char **str, int fd, bool new_line);
void			cd(void);
void			exit_call(void);
void			env_call(int fd, int j);
void			export_call(int i, int j, int equal, int fd);
void			unset_call(void);
void			error_handling_built_in(bool error);

// executer
void			executer(void);
void			child(int fd_in, int fd_out, int n);
int				here_doc(int fd, int y, int j);
char			*env_finder(char *str);
void			do_comand(char *path, int n);
size_t			ft_strlen_n(const char *str);
int				great(int i, int j);
int				great_great(int i, int j);
int				less(int i, int j);
int				less_less(int i, int j);
int				pipes(int i, bool red_less_fail);

//parser
void			parser(void);
void			print_parser(void);
void			verify_smp_cmd(void);
bool			ft_istoken(char *str);
char			**super_split(char *str);
t_tokens		ft_tokenize(char *str);
char			*replace_dollar_cmd_heredoc(char *str);
void			remove_empty_cmd(void);

//utils
void			make_fds(void);
int				count_arrays(char **tmp);
int				check_var(char *str, int n, char **array);
void			error(char *str);
bool			ft_isseperator(char c);
void			free_parser(void);
void			terminate(int i, bool print);
void			free_smp_cmd(void);
void			write_fd(int fd_in, int fd_out);
void			close_fd(int fd_in, int fd_out);
int				find_builtins(int i);
void			do_builtin(int i, int fd, int j);
bool			validate_pipe(char *str);
void			sig_int(int sig);
char			*rl_get(void);
char			**copy_double_array(char **array);
int				alpha_find(char *str);
char			*add_aspas(char *str);
size_t			strlen_equal(char *str);
void			add_string_export(char *str, int n);
void			add_string_env(char *str);
size_t			strlen_equal(char *str);
void			print_export(int fd);
int				add_declare(char **array, char *str, int i);
void			make_export(bool tog);
char			*replace_dollar(char *str);
void			add_path_to_export(void);
long long		exit_atoll_aux(char *new_str, bool is_neg, int i);
int				check_greats(int i);
int				check_less(int i);
void			child_save_lines(int fd_in, int fd_out);
void			save_lines_less_less(int i, int j);
int				save_lines_less_less_2(void);
int				save_lines_less(int i, int j);
void			error_handling_red(void);
void			close_fd_0(int j);
char			*env_var_value_aux2(char *key_dup, int j);
char			*remove_aspas(char *str, int i, int j);
int				cd_aux(int error);
void			remove_aspas_smp(void);
void			sig_int_heredoc(int sig);
void			sig_quit_cmd(int sig);
void			sig_quit_cmd(int sig);
void			close_all_fds(void);
void			executer_aux_aux(int i, bool red_less_fail);
void			pipe_save_lines(int i, bool red_less_fail);
void			great_child_close(int i, int fd_in, int fd_out, int fd_in2);
int				count_dollar(char *line);
char			*expand_line(char *line, char **expand_line, int i, int n);
char			*env_var_value_new(char *key);
bool			create_seperators_aux(char *cpy_line, char *str, int j, int i);
void			executer_redir(int i);
void			great_utils(int i);
void			great_great_utils(int i);
void			less_utils(int i);

#endif