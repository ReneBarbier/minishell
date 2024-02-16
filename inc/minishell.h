/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:44:42 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 16:21:33 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>
# include <fcntl.h>

//  ASCII

# define PIPE_AC 124
# define DOLLAR_AC 36
# define LESS_AC 60
# define GREAT_AC 62
# define QUOTE_ONE 39
# define QUOTE_TOW 34

// SIGNALS

# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

// ERRORS

#define ERROR_TOKEN_P "syntax error near unexpected token '|'\n"
#define ERROR_TOKEN_L "syntax error near unexpected token '<'\n"
#define ERROR_TOKEN_LL "syntax error near unexpected token '<<'\n"
#define ERROR_TOKEN_G "syntax error near unexpected token '>'\n"
#define ERROR_TOKEN_GG "syntax error near unexpected token '>>'\n"
#define ERROR_TOKEN_NL "syntax error near unexpected token\n"

// STRUCTURES

typedef enum s_sign
{
    NOTH = 0,
    PIPE,
    LESS,
    LESS_T,
    GREAT,
    GREAT_T
}   t_sign;

typedef enum s_token_type
{
    HEREDOC,
    INPUT_REDIR,
    OUTPUT_REDIR,
    APPEND_TO_END,
    INVALID,
    NOTHING
}   t_type;

typedef struct s_expansion {
    int i;
    int j;
    int single_f;
    int double_f;
} t_expansion;

typedef struct  s_lexer
{
    char            *word;
    t_sign          sign;
    struct s_lexer  *next;
}       t_lxr;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}       t_env;

typedef struct s_comand
{
    char            **args;
	t_type			type;
    struct s_comand *next;
}       t_cmd;

typedef struct s_exec
{
	char	*path;
	char	**cmd_paths;
	char	**cmd_args;
	int		**pipe;
	char	*cmd;
	int		indx;
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
}	t_exec;

/*******************************	LEXER	*******************************/

int     ft_lexer(char *str, t_lxr **lxr);
int     ft_isquote(char c);
int     ft_isspace(char c);
int     ft_issign(char c);
void    lexer_clear(t_lxr *lxr);
t_lxr   *ft_last_lxr(t_lxr *lxr);
t_lxr	*ft_lxr_addback(t_lxr *lxr, t_lxr *new);
void	print_lex(t_lxr *lxr);

/*******************************  PARSER  *******************************/

int     ft_parser(t_cmd **table, t_lxr **lxr);
int     ft_sizelst(t_lxr *list);
t_cmd   *init_parser(void);
t_cmd	*ft_cmd_addback(t_cmd *table, t_cmd *new);
char    **free_all(char **mat, int i);
void    ft_clean_lxr_prs(t_cmd *table, t_lxr *lxr);
void    parser_clear(t_cmd *table);

/*******************************  EXPANSOR  *******************************/

void	expansor(t_cmd *cmd, t_env **env);
char	*expand_var(char *str, int *i, t_env **env);
char	*get_var_name(char *str, int i);
int		double_quote_dealer(char *str, int i, int single_f, int double_f);
int		single_quote_dealer(char *str, int i, int single_f, int double_f);
char	*remove_char_at(char *str, int i);

/**********************  ENVIRONMENT / BUILTINS  **************************/

void	export_process(t_env **exp, t_env **env, char *cmd);
void	msg_n_exit(char *msg, int status);
void	error_msg(char *msg, int status);
int		forbidden_char(char *input);
void    init_envd(char **envd, t_env **env, t_env **exp);
int     ft_isbuiltin(char **cmd, t_env **env, t_env **exp);
void    ft_env_del(t_env *env);
void    ft_unset(t_env **env, t_env **exp, char **cmd);
void    ft_env(t_env **env, char **cmd);
void    ft_export(t_env **exp, t_env **env, char **cmd);
void	new_env_var(char *name, char *value, t_env **env_var);
char    *get_name(char *input);
char    *get_value(char *input);
int		update_value(char *name, char *value, t_env **exp, int append)
t_env   *find_env(t_env **env, char *name);
void	ft_pwd(char **cmd);
void    ft_cd(t_env **env, t_env **exp, char **cmd);
int     try_path(char *path);
void	ft_echo(char **args);
int		exit_value(int value);

/*******************************  EXECUTOR  *******************************/

void	input_check(char **argv, t_exec *exec, int child);
void	first_child(char **argv, t_exec exec, char **envp);
void	second_child(char **argv, t_exec exec, char **envp);
void	error_pipex(int err_type, char *name);
void	put_exitcode(int err_type);

#endif