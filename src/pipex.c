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

int pipex(t_param *param, t_data *data)
{
	int status = 0;
	int pipe_tab[2];
	int i =  0;
	int childs_pid[param->cmd_nb];

	init_data(data, param);
	if (param->sep)
		heredoc(param, data);
	close(STDERR_FILENO);
	swap_io(data);
	while (i < param->cmd_nb)
	{
		if (i == param->cmd_nb - 1)
			last_param(data);
		create_and_check_pipe(pipe_tab, data);
		set_infile_outfile(data, param);
		data->arg = ft_split(param->cmds[i], ' ');
		if (!data->arg)
			return (EXIT_FAILURE);
		if (!check_acces(param->paths, param->cmds[i], data))
			return 0; //todo gerer erreur
		data->cmd = param->cmds[i];
		childs_pid[i] = fork_cmd(data);
		free_tab(data->arg);
		i++;
	}
	free_tab(param->paths);
	return status;
}