/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:19:12 by srapin            #+#    #+#             */
/*   Updated: 2023/04/14 03:09:13 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/pipex.h"


t_boolen parse_args(int ac, char **av, char ** envp, t_param *param)
{
	int i;
	
	i = 2;
	if (ac < 5)
		return false;
	param->sep = NULL;
	if (ft_strisequal("here_doc", av[1]))
	{
		//heredoc(param);
		param->infile = -1;
		param->sep = av[2];
		i += 1;
	}
	else
		param->infile = open(av[1], O_RDONLY);
	param->outfile = open(av[ac - 1], O_WRONLY);
	param->cmds = av + i;
	param->cmd_nb = ac - 1 - i;
	param->envp = envp;
	param->paths = get_path(param->envp);
	return true;
}

void init_data(t_data *data, t_param *param)
{
	data->first =  true;
	data->last = false;
	data->new_in = param->infile;
	data->new_out = param->outfile;
	data->prev_pip[0] = -1; 
	data->prev_pip[1] = -1; 
	data->current_pip[0] = -1; 
	data->current_pip[1] = -1; 
	data->envp = param->envp;
	data->arg = NULL;
	data->cmd = NULL;
	data->path = NULL;
}

void last_param(t_data *data)
{
	data->last = true;
	data->current_pip[0] = -1; 
	data->current_pip[1] = -1; 
}
