/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/04/26 12:23:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <fcntl.h>

//	DEFINE MACRO
# define PROMPT "\x1B[1;35mMiniShell >: \x1B[0m"
# define RL_PROMPT "MiniShell >: "

# define TERM_CHARS "<>|\"\'$"
# define TERM_N_SPACE " <>|\"\'$"

# define DEFAULT 1
# define MUTE 2
# define RESET 3
# define HEREDOC 4

// 	GLOBAL
extern int	g_status;

/* Data structures */
typedef enum e_token_type
{
	NONE,
	WORD,
	VAR,
	DQUOTE,
	SQUOTE,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
}	t_token_type;
/*
Note that only WORD and VAR token have malloc'd data attributes.
*/

typedef struct s_token
{
	size_t			index;
	char			*data;
	t_token_type	type;
	char			**cmd;
	bool			to_delete;
	int				pipefd[2];
	int				in;
	int				out;
	bool			heredoc_expand;
	pid_t			pid;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	const char	*str;
	size_t		index;
}	t_input;

typedef struct s_data
{
	char	*line;
	char	**path;
	char	**export;
	bool	newpath;
	t_list	*env;
	t_token	*token_list;
}			t_data;

//	UTILS
int		count_str(char **str);

char	*my_strcat(char *dest, char *str);
char	*path_join(char *path, char *cmd);
char	*var_join(char *var, char *value);

bool	valid_var(char *varname);
bool	ft_is_in_charset(char c, char *charset);

size_t	find_char_set(const char *str, char *charset);
t_list	*grep(char *varname, t_data *data);

//	FREE MEMORIES
char	*cleaner(char *str_in);
void	free_tab(char **tab);
void	free_exit(t_data *data, int opt);

//	DATA FUNCTIONS
char	**cpy_env(t_list *env);
void	data_init(t_data *data, char **envp);
void	sort_export(char **sort);
void	update_env(t_data *data);

//	PARSING
t_token	*lexer(char *input);
t_token	*scanner(const char *str);
t_token	*envar_split(t_token **elem);

int		free_toklist(t_token **list);
int		categ_1(t_input *input, t_token **token_list);
int		categ_2(t_input *input, t_token **token_list);
int		categ_3(t_input *input, t_token **token_list);
int		categ_4(t_input *input, t_token **token_list);
int		categ_5(t_input *input, t_token **token_list);

char	*find_envar(char *envar, t_data *env_data);

size_t	ft_envarlen(const char *str);
size_t	is_closed(t_token *elem, t_token_type elem_type);

bool	categorizer(t_input *input, t_token **token_list);
bool	create_token(t_token_type type, char *data, t_token **list);
bool	checker_quotes(t_token *token_list, t_data *env_data);
bool	checker_redir(t_token *token_list, t_data *data);
bool	checker_words(t_token *token_list);
bool	reduce_words(t_token *elem, size_t end, t_token **token_list);
bool	is_legit(t_token *elem);
bool	heredoc_expand_exception(t_token *elem);
bool	synerror(char *str, t_data *data);

void	analyzer(t_data *data);
void	display_toklist(t_token *token_list);
void	relink_toklist(t_token *elem, t_token *tmp,
			char *new_data, t_token **token_list);
void	expand(t_token *elem, t_data *env_data);
void	lst_pop(t_token *elem, t_token **token_list);
void	reduce_all(t_token **elem, t_token *end, t_token **token_list);
void	reduce(t_token **elem, t_token *end, t_data *env_data,
			t_token **token_list);
void	expand_remaining_envar(t_data *env_data);
void	suppress_spaces(t_token **token_list);
void	glue_together(t_token **tmp, t_token **token_list);
void	glue_to_prev(t_token **tmp, t_token **token_list);
void	glue_to_next(t_token **tmp, t_token **token_list);
void	reparse_envar(t_token **elem, t_data *data);

//	EXEC
bool	in_pipeline(t_token *elem);
bool	exec_builtins(t_token *elem, t_data *data);
bool	is_redir_token(t_token *elem);
bool	exec_builtins(t_token *elem, t_data *data);
bool	is_builtin(char *cmd);

char	*pop_first_cmd(t_token **elem, t_data *data);
char	*get_binpath(char *filename, t_data *data);
char	*get_filepath(char **filename);

pid_t	fork_exec(t_token *elem, char **envp, t_data *data);

void	dgreat_handler(char *filepath, t_token **tmp, t_data *data);
void	great_handler(char *filepath, t_token **tmp, t_data *data);
void	less_handler(char *filepath, t_token **tmp, t_data *data);
void	merge_cmd(t_token *elem, t_data *data);
void	file_handler(t_data *data);
void	executor(char **envp, t_data *data);
void	heredoc(char *delim, t_token **tmp, t_data *data);
void	matriochka(char **str, t_data *data);
void	child_prompt(char *delim, t_token **tmp, t_data *data);
void	standalone_builtin(t_token *elem, t_data *data);
void	close_unused_fd(t_token *elem, t_data *data);
void	exec_cmd(char **arg, char **envp, t_data *data);
void	check_exit_status(void);
void	less_fail(int fd, t_token **elem);
void	end_handlers(char *filepath, t_token **tmp, t_data *data);

int		count_cmd(t_data *data);

//	BUILTINS
void	cd(char **argpath, t_data *data);
void	echo(char **arg);
void	exit_ms(char **arg, t_data *data);
void	export(char **arg, t_data *data);
void	env(char **cmd, t_list *env);
void	pwd(char **cmd);
void	unset(char **arg, t_data *data);

//	SIGNAL
void	set_signal(int mode);

#endif
