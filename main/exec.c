/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:36:12 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 14:12:04 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exec_cmd(t_data *d, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	**arguments;
	int		status;

	arguments = ft_split(cmd, ' ');
	i = 0;
	status = -1;
	while (d->path && d->path[i])
	{
		full_cmd = ft_strjoin(d->path[i++], arguments[0]);
		if (!full_cmd)
			return (ft_free_double_tab(arguments));
		if (access(full_cmd, X_OK) != -1)
			status = execve(full_cmd, arguments, d->envp);
		free(full_cmd);
	}
	if (access(arguments[0], X_OK) != -1)
		status = execve(arguments[0], arguments, d->envp);
	fd_printf(STDERR_FILENO, "%s%s\n", E_CMD_NOT_FOUND, cmd);
	ft_free_double_tab(arguments);
	if (status == -1)
		return (0);
	return (1);
}

int	ft_cmd_valid(t_data *d, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	**arguments;
	int		status;

	if (!*cmd)
		return (ft_empty_cmd());
	arguments = ft_split(cmd, ' ');
	i = 0;
	status = 0;
	while (d->path && d->path[i])
	{
		full_cmd = ft_strjoin(d->path[i++], arguments[0]);
		if (!full_cmd)
			return (ft_free_double_tab(arguments));
		if (access(full_cmd, X_OK) != -1)
			status = 1;
		free(full_cmd);
	}
	if (access(arguments[0], X_OK) != -1)
		status = 1;
	if (!status)
		fd_printf(STDERR_FILENO, "%s%s\n", E_CMD_NOT_FOUND, cmd);
	ft_free_double_tab(arguments);
	return (status);
}

int	ft_empty_cmd(void)
{
	fd_printf(STDERR_FILENO, E_NOCMD);
	return (0);
}
