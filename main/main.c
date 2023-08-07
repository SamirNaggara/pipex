/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:28:18 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 00:07:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	d = ft_init(ac, av, envp);
	ft_test_cmds(&d);
	if (d.status == 0)
		return (0);
	ft_fork(&d);
	ft_free_double_tab(d.path);
	if (d.here_doc)
		unlink(TMP_FILE_NAME);
	return (0);
}

int	ft_test_cmds(t_data *d)
{
	d->status = 1;
	if (!ft_inverse_stdin(d))
		d->status = 2;
	if (!ft_cmd_valid(d, d->cmd1))
		d->status = 2;
	if (!ft_cmd_valid(d, d->cmd2))
		d->status = 0;
	if (!ft_test_stdout(d))
		d->status = 0;
	if (!d->status)
	{
		ft_close_all_fds();
		ft_free_double_tab(d->path);
	}
	return (d->status);
}
