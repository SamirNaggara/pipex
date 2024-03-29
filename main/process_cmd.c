/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:37:37 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 16:38:37 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_process_cmd1(t_data *d, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) != -1 && d->status != 2)
	{
		close(fd[1]);
		ft_exec_cmd(d, d->cmd1);
	}
	close(fd[1]);
	ft_close_all_fds();
	ft_free_path_and_d(d);
	exit(0);
}

void	ft_process_cmd2(t_data *d, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) != -1 && ft_inverse_stdout(d))
	{
		close(fd[0]);
		if (d->status)
			ft_exec_cmd(d, d->cmd2);
	}
	close(fd[0]);
	close(STDERR_FILENO);
	ft_close_all_fds();
	ft_free_path_and_d(d);
	exit(0);
}
