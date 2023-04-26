/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:18:54 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 23:09:50 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	check_io(t_param *param)
{
	if (param->infile && access(param->infile, F_OK | R_OK) == -1)
		perror("acces infile");
	if (access(param->outfile, F_OK) != -1
		&& access(param->outfile, W_OK) == -1)
		perror("acces outfile");
	if (access(param->outfile, F_OK) == -1)
		safe_close(&(int){open(param->outfile, O_WRONLY | O_CREAT,
				0666)});
}

void	exit_free(int *to_free, int to_close)
{
	safe_close(&to_close);
	free(to_free);
	exit(EXIT_FAILURE);
}

void	swap_io(t_param *param, t_data *data, int i, int *to_free)
{
	int	fd;

	safe_close(&(data->pip[0]));
	if (i == 0 && param->heredoc_fd > -1)
		fd = param->heredoc_fd;
	else if (i == 0)
		fd = open(param->infile, O_RDONLY);
	else
		fd = data->to_read;
	dup2(fd, STDIN_FILENO);
	if (fd == -1)
		exit_free(to_free, data->pip[1]);
	safe_close(&fd);
	if (i == param->cmd_nb - 1 && param->infile)
		fd = open(param->outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (i == param->cmd_nb - 1)
		fd = open(param->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = data->pip[1];
	dup2(fd, STDOUT_FILENO);
	if (fd == -1)
		exit_free(to_free, data->pip[1]);
	safe_close(&fd);
}
