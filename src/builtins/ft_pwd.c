/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:02:05 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/20 18:14:25 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(char **cmd)
{
	char	*tmp;

	if (cmd && cmd[1])
		return (msg_return("pwd", 0, "too many arguments", 1));
	tmp = getcwd(NULL, 0);
	ft_fprintf(1, "%s\n", tmp);
	free(tmp);
	exit_status(0);
}