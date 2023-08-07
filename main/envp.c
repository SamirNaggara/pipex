/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:55:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/07 18:19:50 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fill_envp(t_data *d)
{
	if (d->envp && *(d->envp))
	{
		if (!ft_path_exist(d))
		{
			d->path = NULL;
			return ;
		}
		d->path_exist = 1;
		d->path = ft_get_path(d);
		if (!d->path)
		{
			ft_close_all_fds();
			exit(0);
		}
	}
	else
		d->path = NULL;
}

int	ft_path_exist(t_data *d)
{
	int	i;

	i = 0;
	while (d->envp[i])
	{
		if (ft_strnstr(d->envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}
