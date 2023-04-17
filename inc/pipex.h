/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:50:53 by srapin            #+#    #+#             */
/*   Updated: 2023/04/14 01:03:52 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libft/ft_printf.h"
#include "../libft/mylibft/libft.h"
#include "../libft/gnl/get_next_line_bonus.h"


typedef enum s_boolen
{
	false,
	true
} t_boolen;


typedef struct s_param
{
	int infile;
	int outfile;
	int cmd_nb;
	char *sep;
	char **cmds; //ajust
	char **envp;
	char** paths;
} t_param;

typedef struct s_data
{
	t_boolen first;
	t_boolen last;
	int new_in;
	int new_out;
	int prev_pip[2];
	int current_pip[2];
	char *path; //free
	char **arg; //todo free
	char **envp;
	char *cmd;
}	t_data;


//heredoc
int heredoc(t_param *param, t_data *data);

//init
t_boolen parse_args(int ac, char **av, char ** envp, t_param *param);
void init_data(t_data *data, t_param *param);
void last_param(t_data *data);

//io
void set_infile_outfile(t_data *data, t_param *param);
void swap_io(t_data *data);

//main
int main(int ac, char** av, char **envp);

//pipex
void exec_process(t_data *data);
int fork_cmd(t_data *data);
int pipex(t_param *param, t_data * data);

//safe
void create_and_check_pipe(int pipe_tab[2], t_data *data);
t_boolen check_acces(char **paths, char *cmd, t_data *data);
void safe_close(int  fd);

//tools
void free_tab(char **tab);
void add_slash(char **paths);
t_boolen	ft_strisequal(char *s1, char *s2);
char **get_path(char **envp);

#endif