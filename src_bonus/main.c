/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:02:58 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 01:49:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	heredoc_process(t_param *param, t_data *data)
{
	char	*line;

	safe_close(&(data->pip[0]));
	line = get_next_line(STDIN_FILENO);
	dup2(data->pip[1], STDOUT_FILENO);
	safe_close(&(data->pip[1]));
	while (ft_strstr(param->sep, line, ft_strlen(param->sep)))
	{
		ft_printf(line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	exit(0);
}

int	heredoc(t_param *param, t_data *data)
{
	int	pid;
	int	status;

	safe_pipe(data->pip);
	pid = fork();
	if (pid < 0)
		fail_process();
	if (!pid)
	{
		heredoc_process(param, data);
	}
	wait(&status);
	safe_close(&(data->pip[1]));
	param->heredoc_fd = data->pip[0];
	data->pip[0] = -1;
	data->pip[1] = -1;
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	t_param	param;
	t_data	data;

	if ((!parse_args(ac, av, envp, &param)))
	{
		ft_printf("parse error");
		return (1);
	}
	init_data(&data);
	if (!param.infile)
		heredoc(&param, &data);
	check_io(&param);
	return (pipex(&param, &data));
}
