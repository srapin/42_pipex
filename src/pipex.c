/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:06:18 by srapin            #+#    #+#             */
/*   Updated: 2023/04/03 03:48:29by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/pipex.h"

/*
void exec_process(t_data *data)
{
	int pid;
	swap_io(data);
	execve(data->path, data->arg, data->envp);
	perror("after execve");
	exit(EXIT_FAILURE);
}


int fork_cmd(t_data *data)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		safe_close(data->prev_pip[1]); // 1 = ecriture
		safe_close(data->current_pip[0]); //0 = lecture
		exec_process(data);		
	}
	safe_close(data->prev_pip[0]); //0 = lecture
	safe_close(data->current_pip[1]); // 1 = ecriture
	safe_close(data->new_in);
	safe_close(data->new_out);
	data->prev_pip[0] = data->current_pip[0];
	data->prev_pip[1] = data->current_pip[1];
	data->first = false;
	free(data->path);
	return (pid);
}
void first_swap(t_param *param)
{
	int fd;

	if (param->heredoc_fd > -1)
	{
		dup2(param->heredoc_fd, STDIN_FILENO);
		close(param->heredoc_fd);
	}
	else
	{
		fd = open(param->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	fd = open(param->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

*/

int wait_childs(int size, int *childs_pid)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < size)
	{
		waitpid(childs_pid[i], &status, 0);
		i++;
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
	
}


void fail_process()
{
	perror("fork error");
	exit(EXIT_FAILURE);
}

void parent_process(t_data *data)
{
	safe_close(&(data->pip[1]));
	safe_close(&(data->to_read));
	data->to_read = data->pip[0];
	data->pip[0] = -1;
	data->pip[1] = -1;
}

void child_process(t_param * param, t_data * data, int i)
{
	char **paths = get_path(param->envp);
	char **arg;
	// ft_putstr_fd("child=", 2);
	// ft_putnbr_fd(i, 2);
	// ft_putstr_fd( "\n", 2);
	
	swap_io(param, data, i);
	//safe_close(data->pip[0]);
	data->arg = ft_split(param->cmds[i], ' ');
	check_acces(paths, param->cmds[i], data);
	//data->cmd = param->cmds[i];
	//safe_close(param)
	execve(data->path, data->arg, param->envp);
	perror("after execve");
	exit(EXIT_FAILURE);
}



int pipex(t_param *param, t_data *data)
{
	int i = 0;
	int childs_pid[param->cmd_nb];
	int pid;
	
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
			child_process(param, data, i);
		parent_process(data);
		i++;
	}
	safe_close(&(param->heredoc_fd));
	return wait_childs(param->cmd_nb, childs_pid);
}