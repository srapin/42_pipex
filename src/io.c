/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:18:54 by srapin            #+#    #+#             */
/*   Updated: 2023/04/17 23:48:15 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/pipex.h"

/*
void set_infile_outfile(t_data *data, t_param *param)
{
	data->new_in = data->prev_pip[0]; //ancien en lecture
	data->new_out = data->current_pip[1]; // current en ecriture
}
*/




void swap_io(t_param * param, t_data * data, int i)
{
	//todo proteger?
	int fd;
	
	if (i == 0 && param->heredoc_fd > -1)
		fd = param->heredoc_fd;
	else if (i == 0)
		fd = open(param->infile, O_RDONLY);
	else
		fd = data->to_read;

	// ft_putstr_fd("stdin=", 2);
	// ft_putnbr_fd(fd, 2);
	// ft_putstr_fd("\n", 2);
	dup2(fd, STDIN_FILENO);
	safe_close(&fd);
	if (i == param->cmd_nb - 1)
		fd = open(param->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
	{
		safe_close(&(data->pip[0]));
		fd = data->pip[1];
	}
	// ft_putstr_fd("stdout=", 2);
	// ft_putnbr_fd(fd, 2);
	// ft_putstr_fd("\n", 2);
	dup2(fd, STDOUT_FILENO);
	safe_close(&fd);
}
