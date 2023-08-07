/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:38:29 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/07 22:49:02 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork(t_data *d)
{
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (0);
	d->child1 = fork();
	if (d->child1 == -1)
		return (0);
	if (d->child1 == 0)
		ft_process_cmd1(d, fd);
	d->child2 = fork();
	if (d->child2 == -1)
		return (0);
	if (d->child2 == 0)
		ft_process_cmd2(d, fd);
	close(fd[1]);
	close(fd[0]);
	waitpid(d->child1, &status, 0);
	if (status != 0)
	{
		close(fd[1]);
		close(fd[0]);
		return (0);
	}
	waitpid(d->child2, &status, 0);
	close(fd[1]);
	close(fd[0]);
	ft_close_all_fds();
	return (1);
}
