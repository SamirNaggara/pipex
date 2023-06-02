/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:04:30 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/02 14:25:07 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_inverse_stdout(t_data *d)
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
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror(E_DUP2);
		exit(1);
		close(fd_out);
		return (0);
	}
	close(fd_out);
	return (1);
}

int	ft_inverse_stdin(t_data *d)
{
	int	fd_in;

	fd_in = open(d->file_in, O_RDONLY);
	if (fd_in == -1)
	{
		if (errno == EACCES)
			ft_printf(STDERR_FILENO, "%s%s\n", E_PERMISSION, d->file_in);
		else if (errno == ENOENT)
			ft_printf(STDERR_FILENO, "%s%s\n", E_FILE_NOT_FOUND, d->file_in);
		else
			ft_printf(STDERR_FILENO, "%s%s\n", E_FILE_NOT_FOUND2, d->file_in);
		close(fd_in);
		return (0);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		return (0);
	}
	close(fd_in);
	return (1);
}
