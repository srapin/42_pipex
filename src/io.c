/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:18:54 by srapin            #+#    #+#             */
/*   Updated: 2023/04/03 02:56:58 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/pipex.h"


void set_infile_outfile(t_data *data, t_param *param)
{
	data->new_in = data->prev_pip[0]; //ancien en lecture
	data->new_out = data->current_pip[1]; // current en ecriture
}

void swap_io(t_data *data)
{
	//todo proteger?
	if (data->new_in > -1)
	{
		dup2(data->new_in, STDIN_FILENO);
		close(data->new_in);
	}
	if (data->new_out > -1 && !data->last)
	{
		dup2(data->new_out, STDOUT_FILENO);
		close(data->new_out);
	}
}
