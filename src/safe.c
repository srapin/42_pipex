/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:22:15 by srapin            #+#    #+#             */
/*   Updated: 2023/04/03 03:02:02 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/pipex.h"

void create_and_check_pipe(int pipe_tab[2], t_data *data)
{
	if (data->last)
		return;
	if(pipe(pipe_tab) == -1)
	{
		perror("pipe creation failed");
		exit(EXIT_FAILURE);
	}
	data->current_pip[0] = pipe_tab[0];
	data->current_pip[1] = pipe_tab[1];
}

t_boolen check_acces(char **paths, char *cmd, t_data *data)
{
	int i;
	i = 0;
	char *path;
	
	while(paths && paths[i])
	{
		path = ft_strjoin(paths[i], data->arg[0]);
		if (path && access(path, X_OK) == 0)
		{
			data->path = path;
			return true;
		}
		free(path);
		i++;
	}
	return false;
}

void safe_close(int  fd)
{
	if (fd != -1)
		close(fd); //0 = lecture 
	
}

