/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:19:12 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 01:34:09 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_boolen	parse_args(int ac, char **av, char **envp, t_param *param)
{
	int	i;

	i = 2;
	if (ac < 5)
		return (false);
	param->sep = NULL;
	param->heredoc_fd = -1;
	if (ft_strisequal("here_doc", av[1]))
	{
		param->infile = NULL;
		param->sep = av[2];
		i += 1;
	}
	else
		param->infile = av[1];
	param->outfile = av[ac - 1];
	param->cmds = av + i;
	param->cmd_nb = ac - 1 - i;
	param->envp = envp;
	return (true);
}

void	init_data(t_data *data)
{
	data->to_read = -1;
	data->pip[0] = -1;
	data->pip[1] = -1;
	data->arg = NULL;
	data->cmd = NULL;
	data->path = NULL;
}
