/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:40:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/11 09:43:01 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	ft_init(int ac, char **av, char **envp)
{
	t_data	d;

	if (ac < 5)
	{
		fd_printf(STDERR_FILENO, "%s\n", E_NB_ARG);
		ft_close_all_fds();
		exit(0);
	}
	d.envp = envp;
	d.ac = ac;
	d.av = av;
	d.path = ft_get_path(envp);
	if (!d.path)
	{
		ft_close_all_fds();
		exit(0);
	}
	if (!ft_parse_doc(&d, av))
	{
		ft_free_double_tab(d.path);
		ft_close_all_fds();
		exit(0);
	}
	return (d);
}

int	ft_parse_doc(t_data *d, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 6) == 0)
	{
		if (!ft_parse_here_doc(d, av))
			return (0);
	}
	else
	{
		if (!ft_parse_classic(d, av))
			return (0);
	}
	return (1);
}

int	ft_parse_here_doc(t_data *d, char **av)
{
	d->file_in = TMP_FILE_NAME;
	d->stop_str = av[2];
	d->cmd1 = av[3];
	d->cmd2 = av[4];
	d->file_out = av[5];
	d->here_doc = 1;
	if (d->here_doc)
	{
		if (!ft_stdin_file(d))
		{
			return (0);
		}
	}
	return (1);
}
/*
	Create stdout file
*/

int	ft_create_stdout(t_data *d)
{
	int		fd_out;

	fd_out = open(d->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		if (errno == EACCES)
			fd_printf(STDERR_FILENO, "%s %s\n", E_PERMISSION, d->file_out);
		else
			fd_printf(STDERR_FILENO, "%s\n", E_OUT_FILE);
		close(fd_out);
		return (0);
	}
	close(fd_out);
	return (1);
}

int	ft_parse_classic(t_data *d, char **av)
{
	d->file_in = av[1];
	d->cmd1 = av[2];
	d->cmd2 = av[3];
	d->file_out = av[4];
	d->here_doc = 0;
	return (1);
}
