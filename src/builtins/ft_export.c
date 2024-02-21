/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:29 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/19 15:21:46 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_print(t_env **exp)
{
	t_env	*tmp;

	tmp = *exp;
	while (tmp)
	{
		ft_fprintf(1, "declare -x %s", tmp->name);
		if (tmp->value)
			ft_fprintf(1 ,"=\"%s\"\n", tmp->value);
		else
			ft_fprintf(1 ,"\n");
		tmp = tmp->next;
	}
}

void	 sort_export(t_env **exp)
{
	t_env	*node;
	t_env	*start;
	int		sorted_f;

	node = *exp;
	start = *exp;
	sorted_f = 1;
	if (!node)
		return ;
	while (sorted_f)
	{
		sorted_f = 0;
		while (node->next)
		{
			if (ft_strncmp(node->name, node->next->name, ft_strlen(node->name) + 1) > 0)
			{
				swap_data(node, node->next);
				sorted_f = 1;
			}
			node = node->next;
		}
		node = start;
	}
	export_print(exp);
}

int	update_value(char *name, char *value, t_env **exp, int append)
{
	t_env	*tmp;
	int		exists_f;

	tmp = *exp;
	exists_f = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (value && append)
				tmp->value = ft_join_n_destroy(tmp->value, value, 3);
			else
				tmp->value = value;
			exists_f = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (exists_f);
}

void	export_process(t_env **exp, t_env **env, char *cmd)
{
	char	*name;
	char	*value;
	int 	append;

	value = NULL;
	append = 0;
	if (forbidden_char(cmd))
		msg_exit("export", cmd, "Not a valid identifier", 1);
	name = get_name(cmd);
	value = get_value(cmd);
	if (ft_strncmp(cmd + ft_strlen(name), "+=", 2) == 0)
		append = 1;
	if (!update_value(name, value, exp, append))
		new_env_var(name, value, exp);
	if (!update_value(name, value, env, append) && value)
		new_env_var(name, value, env);
	free(name);
	free(value);
}

void	ft_export(t_env **exp, t_env **env, char **cmd)
{
	int		i;

	i = 0;
	if (!cmd[1])
		sort_export(exp);
	else
		while (cmd[++i])
			export_process(exp, env, cmd[i]);
	exit(0);
}