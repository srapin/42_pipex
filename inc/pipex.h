/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:50:53 by srapin            #+#    #+#             */
/*   Updated: 2023/04/24 23:02:00 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/ft_printf.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/mylibft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <wait.h>

typedef enum s_boolen
{
	false,
	true
}			t_boolen;

typedef struct s_param
{
	char	*infile;
	char	*outfile;
	int		cmd_nb;
	int		heredoc_fd;
	char	*sep;
	char	**cmds;
	char	**envp;
}			t_param;

typedef struct s_data
{
	int		to_read;
	int		pip[2];
	char	*path;
	char	**arg;
	char	*cmd;
}			t_data;

//heredoc
int			heredoc(t_param *param, t_data *data);

//init
t_boolen	parse_args(int ac, char **av, char **envp, t_param *param);
void		init_data(t_data *data);

//io
void		swap_io(t_param *param, t_data *data, int i, int *to_free);
void		check_io(t_param *param);

//main
int			main(int ac, char **av, char **envp);

//pipex
void		fail_process(void);
int			pipex(t_param *param, t_data *data);

//safe
t_boolen	check_acces(char **paths, t_data *data);
void		safe_close(int *fd);
void		safe_pipe(int pipe_tab[2]);

//tools
void		free_tab(char **tab);
void		add_slash(char **paths);
t_boolen	ft_strisequal(char *s1, char *s2);
char		**get_path(char **envp);

#endif