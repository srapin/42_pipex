/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:15:56 by srapin            #+#    #+#             */
/*   Updated: 2023/04/17 23:58:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int heredoc(t_param *param, t_data *data)
{
	char *line;
	int pid;
	int status;
	
	
	safe_pipe(data->pip);
	pid = fork();
	if (pid < 0)
		fail_process();
	if (!pid)
	{
		safe_close(data->pip[0]);
		line = get_next_line(STDIN_FILENO);
		while(ft_strstr(param->sep, line, ft_strlen(param->sep)))
		{
			ft_putstr_fd(line, data->pip[1]);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		exit(0);
	}
	wait(&status);
	safe_close(data->pip[1]);
	param->heredoc_fd = data->pip[0];
	return status;
}
