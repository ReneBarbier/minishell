/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:39:40 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/12 13:47:00 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	input_file(t_pipe *data, char *file, int heredoc)
{
	if (data->infile_fd)
		close(data->infile_fd);
	check_file(file, heredoc);
	data->infile_fd = open(file, O_RDONLY);
	if (data->infile_fd < 0)
		msg_exit(file, 0, ERR_NO_FILE, 1);
}

void	outfile_file(t_pipe *data, char *file, int type)
{
	if (data->outfile_fd)
		close(data->outfile_fd);
	check_file(file, 0);
	if (type == APPEND_TO_END)
		data->outfile_fd = open(file, O_APPEND | O_CREAT | O_RDWR, 0000644);
	else
		data->outfile_fd = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data->outfile_fd < 0)
		msg_exit(file, 0, ERR_NO_FILE, 1);
}

void	get_files_redir(t_rd *redir, t_pipe *data)
{
	while (redir)
	{
		if (redir->type == INPUT_REDIR)
			input_file(data, redir->file, 1);
		else if (redir->type == HEREDOC)
		{
			printf("HEREDOC\n");
			input_file(data, redir->file, 0);
		}
		else if (redir->type == OUTPUT_REDIR || redir->type == APPEND_TO_END)
			outfile_file(data, redir->file, redir->type);
		redir = redir->next;
	}
}

void	make_redirections(t_pipe *data, t_cmd *cmd)
{
	close(data->pipe_ends[0]);
	if (data->outfile_fd) // if theres an output file
	{
		dup2(data->outfile_fd, STDOUT_FILENO);
		close(data->outfile_fd);
	}
	else if (cmd->next != NULL)                 
		dup2(data->pipe_ends[1], STDOUT_FILENO);
	close(data->pipe_ends[1]);
	if (data->infile_fd)
	{
		dup2(data->infile_fd, STDIN_FILENO);
		close(data->infile_fd);
	}
}
