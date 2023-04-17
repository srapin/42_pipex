/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:15:56 by srapin            #+#    #+#             */
/*   Updated: 2023/04/14 01:42:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int heredoc(t_param *param, t_data *data)
{
	char *line;
	int fd[2];
	int pid;
	int status;
	
	
	create_and_check_pipe(fd, data);
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		safe_close(data->current_pip[0]);
		data->new_out = data->current_pip[1];
		swap_io(data);
		line = get_next_line(STDIN_FILENO);
		while(ft_strstr(param->sep, line, ft_strlen(param->sep)))
		{
			ft_printf(line);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		exit(0);
	}
	wait(&status);
	safe_close(data->current_pip[1]);
	data->new_in = data->current_pip[0];
	return status;
}
