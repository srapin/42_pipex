/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:18:54 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 22:01:43 by srapin           ###   ########.fr       */
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

void	swap_io(t_param *param, t_data *data, int i)
{
	int	fd;

	if (i == 0 && param->heredoc_fd > -1)
		fd = param->heredoc_fd;
	else if (i == 0)
		fd = open(param->infile, O_RDONLY);
	else
		fd = data->to_read;
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	safe_close(&fd);
	if (i == param->cmd_nb - 1 && param->infile)
		fd = open(param->outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (i == param->cmd_nb - 1)
		fd = open(param->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
	{
		safe_close(&(data->pip[0]));
		fd = data->pip[1];
	}
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	safe_close(&fd);
}
