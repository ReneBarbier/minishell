/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:45:55 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/04 12:28:49 by rbarbier         ###   ########.fr       */
/*                                                                 +           */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_table(t_cmd *table)
{
	t_cmd	*tmp;
	int		i;
	int		j; 
	
	
	j = 0;
	i = 0;
	tmp = table;
	while (tmp)
	{
		j = 0;
		while (tmp->args[j])
		{
			printf("table[%d].args[%d] = %s\n", i, j, tmp->args[j]);
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

int main(int argc, char **argv, char **envd)
{
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmd;
	char	*prompt;
	t_lxr	*lxr = NULL;
	t_cmd	*table = NULL;

	//(void)envd;
	cmd = malloc(sizeof(t_cmd));
	(void)argv;
	if (argc > 1)
	{
		printf("Error: minishell does not take any arguments\n");
		return (1);
	}
	env = NULL;
	exp = NULL;
	init_envd(envd, &env, &exp);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		ft_lexer(prompt, &lxr);
		ft_parser(&table, &lxr);
		expansor(table, &env);
		print_table(table);
		ft_clean_lxr_prs(table, lxr);
		lxr = NULL;
		table = NULL;
		//printf("%s\n", prompt);
	}
    return 0;
}
