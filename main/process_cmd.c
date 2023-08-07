/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:37:37 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 00:13:14 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_process_cmd1(t_data *d, int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		ft_close_all_fds();
		close(fd[1]);
		close(fd[0]);
		close(d->fd_in);
		ft_free_path_and_d(d);
		exit(1);
	}
	close(fd[1]);
	if (d->status == 1)
	{
		if (!ft_exec_cmd(d, d->cmd1))
		{
			close(fd[1]);
			close(fd[0]);
			ft_free_path_and_d(d);
			ft_close_all_fds();
			close(d->fd_in);
			exit(1);
		}
	}
	close(fd[1]);
	close(fd[0]);
	ft_close_all_fds();
	ft_free_path_and_d(d);
	exit(0);
}

void	ft_process_cmd2(t_data *d, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_close_all_fds();
		close(fd[0]);
		ft_free_path_and_d(d);
		exit(1);
	}
	if (!ft_inverse_stdout(d))
	{
		ft_close_all_fds();
		close(fd[0]);
		ft_free_path_and_d(d);
		exit(1);
	}
	close(STDERR_FILENO);
	close(fd[0]);
	if (d->status)
		ft_exec_cmd(d, d->cmd2);
	ft_close_all_fds();
	ft_free_path_and_d(d);
	exit(0);
}
