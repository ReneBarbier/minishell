/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:54:33 by martorre          #+#    #+#             */
/*   Updated: 2024/02/01 13:02:43 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"

#define PIPE 124
#define DOLLAR 36
#define LESS 60
#define GREAT 62
#define QUOTE_ONE 39
#define QUOTE_TOW 34

typedef struct  s_lexer
{
    char            *word;
    struct t_lxr   *next;
}   t_lxr;

#endif