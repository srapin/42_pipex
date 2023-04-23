/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:22:15 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 00:00:31 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	safe_pipe(int pipe_tab[2])
{
	if (pipe(pipe_tab) == -1)
	{
		perror("pipe creation failed");
		exit(EXIT_FAILURE);
	}
}

void	check_acces(char **paths, char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], data->arg[0]);
		if (path && access(path, X_OK) == 0)
		{
			data->path = path;
			return ;
		}
		free(path);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	safe_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}
