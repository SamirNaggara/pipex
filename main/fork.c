/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:38:29 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 16:32:57 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork(t_data *d)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (0);
	d->child1 = fork();
	if (d->child1 == 0)
		ft_process_cmd1(d, fd);
	d->child2 = fork();
	if (d->child2 == 0)
		ft_process_cmd2(d, fd);
	close(fd[1]);
	close(fd[0]);
	waitpid(d->child1, NULL, 0);
	waitpid(d->child2, NULL, 0);
	ft_close_all_fds();
	return (1);
}
