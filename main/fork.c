/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:38:29 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/02 14:21:52 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork(t_data *d)
{
	int		fd[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (!ft_inverse_stdin(d) || pipe(fd) == -1)
		return (0);
	child1 = fork();
	if (child1 == -1)
		return (0);
	if (child1 == 0)
		ft_process_cmd1(d, fd);
	waitpid(child1, &status, 0);
	if (status != 0)
		return (0);
	child2 = fork();
	if (child2 == -1)
		return (0);
	if (child2 == 0)
		ft_process_cmd2(d, fd);
	
	close(fd[0]);
	close(fd[1]);
	ft_close_all_fds();
	
	return (1);
}
