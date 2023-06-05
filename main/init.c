/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:40:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/05 11:08:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*ft_init(int ac, char **av, char **envp)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return ((t_data *)0);
	if (ac < 5)
	{
		ft_printf(STDERR_FILENO, "%s\n", E_NB_ARG);
		ft_close_all_fds();
		free(d);
		return ((t_data *)0);
	}
	d->envp = envp;
	d->ac = ac;
	d->av = av;
	d->path = ft_get_path(envp);
	if (!d->path)
		return (ft_free_d_close_fds(d));
	if (!ft_parse_doc(d, av))
	{
		ft_free_double_tab(d->path);
		free(d);
		ft_close_all_fds();
		return ((t_data *)0);
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
			free(d);
			return (0);
		}
	}
	return (1);
}

/*
	Si on est dans le cas here doc
	il prends les infos du stdin et les mets dans un fichier temporaire
*/
int	ft_stdin_file(t_data *d)
{
	int		fd_tmp;
	char	*stdin_line;

	fd_tmp = open(TMP_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0655);
	stdin_line = get_next_line(STDIN_FILENO);
	while (!stdin_line || !ft_strnstr(stdin_line, d->stop_str,
			ft_strlen(d->stop_str)))
	{
		write(fd_tmp, stdin_line, ft_strlen(stdin_line));
		free(stdin_line);
		stdin_line = get_next_line(STDIN_FILENO);
	}
	free(stdin_line);
	close(fd_tmp);
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
			ft_printf(STDERR_FILENO, "%s %s\n", E_PERMISSION, d->file_out);
		else
			ft_printf(STDERR_FILENO, "%s\n", E_OUT_FILE);
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
