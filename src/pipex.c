/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:50:53 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 00:10:37 by srapin           ###   ########.fr       */
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
	exit(EXIT_FAILURE);
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
	char	**arg;

	paths = get_path(param->envp);
	swap_io(param, data, i);
	data->arg = ft_split(param->cmds[i], ' ');
	if (check_acces(paths, param->cmds[i], data))
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
	int	*childs_pid;
	int	pid;

	i = 0;
	childs_pid = malloc(param->cmd_nb * sizeof(int));
	if (!childs_pid)
		exit(EXIT_FAILURE);
	while (i < param->cmd_nb)
	{
		if (i < param->cmd_nb - 1)
			safe_pipe(data->pip);
		if (i == 1)
			safe_close(&(param->heredoc_fd));
		childs_pid[i] = fork();
		if (childs_pid[i] < 0)
			fail_process();
		if (childs_pid[i] == 0)
			child_process(param, data, i, childs_pid);
		parent_process(data);
		i++;
	}
	safe_close(&(param->heredoc_fd));
	return (wait_childs(param->cmd_nb, childs_pid));
}
