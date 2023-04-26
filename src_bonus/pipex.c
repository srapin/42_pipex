/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:50:53 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 23:02:35 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	wait_childs(int size, int *childs_pid)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < size)
	{
		waitpid(childs_pid[i], &status, 0);
		i++;
	}
	free(childs_pid);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

void	fail_process(void)
{
	perror("fork error");
}

void	parent_process(t_data *data)
{
	safe_close(&(data->pip[1]));
	safe_close(&(data->to_read));
	data->to_read = data->pip[0];
	data->pip[0] = -1;
	data->pip[1] = -1;
}

void	child_process(t_param *param, t_data *data, int i, int *to_free)
{
	char	**paths;

	swap_io(param, data, i, to_free);
	paths = get_path(param->envp);
	data->arg = ft_split(param->cmds[i], ' ');
	if (check_acces(paths, data))
		execve(data->path, data->arg, param->envp);
	perror("cmd not found");
	free_tab(paths);
	free_tab(data->arg);
	free(data->path);
	free(to_free);
	exit(EXIT_FAILURE);
}

int	pipex(t_param *param, t_data *data)
{
	int	i;
	int	*pid;

	i = 0;
	pid = malloc(param->cmd_nb * sizeof(int));
	if (!pid)
		exit(EXIT_FAILURE);
	while (i < param->cmd_nb)
	{
		if (i < param->cmd_nb - 1)
			safe_pipe(data->pip);
		if (i == 1)
			safe_close(&(param->heredoc_fd));
		pid[i] = fork();
		if (pid[i] < 0)
			fail_process();
		if (pid[i] == 0)
			child_process(param, data, i, pid);
		if (pid[i] > 0)
			parent_process(data);
		i++;
	}
	safe_close(&(param->heredoc_fd));
	return (wait_childs(param->cmd_nb, pid));
}
