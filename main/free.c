/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:36:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/03 12:32:01 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free_path_and_d(t_data *d)
{
	ft_free_double_tab(d->path);
	free(d);
	return (0);
}

int	ft_free_double_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (0);
}

int	ft_close_all_fds(void)
{
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (0);
}

t_data *ft_free_d_path_close_fds(t_data *d)
{
	ft_free_double_tab(d->path);
	return (ft_free_d_close_fds(d));
}

t_data *ft_free_d_close_fds(t_data *d)
{
	free(d);
	ft_close_all_fds();
	return ((t_data *)0);
}