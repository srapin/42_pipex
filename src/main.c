/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:02:58 by srapin            #+#    #+#             */
/*   Updated: 2023/04/17 23:10:24 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int ac, char** av, char **envp)
{
	t_param param;
	t_data data;

	if ((!parse_args(ac, av, envp, &param)))
	{
		ft_printf("parse error");
		return 1;
	}
	init_data(&data);
	// dup2(open("in", O_RDONLY), STDIN_FILENO);
	// dup2(open("out", O_WRONLY), STDIN_FILENO);
	// dup2(open("err", O_WRONLY), STDIN_FILENO);
	if (!param.infile)
		heredoc(&param, &data);
	//first_swap(&param);
	return pipex(&param, &data);
}