
#include "../inc/pipex.h"


/*
void init_data(t_data *data, t_param *param)
{
	data->first =  true;
	data->last = false;
	data->prev_pip[0] = -1; 
	data->prev_pip[1] = -1; 
	data->envp = param->envp;
	data->new_in = param->infile;
	data->new_out = param->outfile;
}


void print_data(t_data *data)
{
	ft_printf("f = %d\n", data->first);
	ft_printf("l = %d\n", data->last);
	ft_printf("new_in = %d\n", data->new_in);
	ft_printf("new_out = %d\n", data->new_out);
	ft_printf("p_0 = %d\n", data->prev_pip[0]);
	ft_printf("p_1 = %d\n", data->prev_pip[1]);
	ft_printf("c_0 = %d\n", data->current_pip[0]);
	ft_printf("c_1 = %d\n", data->current_pip[1]);
	//ft_printf(data->path);
}

int pipex(t_param *param)
{
	int status;
	t_data data;
	//int pipe_tab[2];
	int i =  0;
	char** paths;
	
	init_data(&data, param);
	
	paths = get_path(param->envp);
	swap_io(&data);
	//print_data(&data);
	while (i < param->cmd_nb)
	{
		ft_printf("%s\n", param->cmds[i]);
		/*
		if (i == param->cmd_nb - 1)
			last_param(&data);
		create_and_check_pipe(pipe_tab, &data);
		set_infile_outfile(&data, param);
		data.arg = ft_split(param->cmds[i], ' ');
		if (!check_acces(paths, param->cmds[i], &data))
			return 0;
		fork_cmd(&data);
		i++;
	}
	free(paths);
	
	return status;
}



void print_data(t_data *data)
{
	ft_printf("f = %d\n", data->first);
	ft_printf("l = %d\n", data->last);
	ft_printf("new_in = %d\n", data->new_in);
	ft_printf("new_out = %d\n", data->new_out);
	ft_printf("p_0 = %d\n", data->prev_pip[0]);
	ft_printf("p_1 = %d\n", data->prev_pip[1]);
	ft_printf("c_0 = %d\n", data->current_pip[0]);
	ft_printf("c_1 = %d\n", data->current_pip[1]);
	//ft_printf(data->path);
}


*/