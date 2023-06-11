/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:04:30 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/11 09:42:44 by snaggara         ###   ########.fr       */
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
			fd_printf(STDERR_FILENO, "%s %s\n", E_PERMISSION, d->file_out);
		else
			fd_printf(STDERR_FILENO, "%s\n", E_OUT_FILE);
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror(E_DUP2);
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
			fd_printf(STDERR_FILENO, "%s%s\n", E_PERMISSION, d->file_in);
		else if (errno == ENOENT)
			fd_printf(STDERR_FILENO, "%s%s\n", E_FILE_NOT_FOUND, d->file_in);
		else
			fd_printf(STDERR_FILENO, "%s%s\n", E_FILE_NOT_FOUND2, d->file_in);
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

int	ft_test_stdout(t_data *d)
{
	int		fd_out;

	fd_out = open(d->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		if (errno == EACCES)
			fd_printf(STDERR_FILENO, "%s %s\n", E_PERMISSION, d->file_out);
		else
			fd_printf(STDERR_FILENO, "%s\n", E_OUT_FILE);
		return (0);
	}
	close(fd_out);
	return (1);
}

/*
	Si on est dans le cas here doc
	il prends les infos du stdin et les mets dans un fichier temporaire
*/
int	ft_stdin_file(t_data *d)
{
	int		fd_tmp;
	char	*stdin_line;

	fd_tmp = open(TMP_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0655);
	stdin_line = get_next_line(STDIN_FILENO);
	while (!stdin_line || !ft_strnstr(stdin_line, d->stop_str,
			ft_strlen(d->stop_str)))
	{
		write(fd_tmp, stdin_line, ft_strlen(stdin_line));
		free(stdin_line);
		stdin_line = get_next_line(STDIN_FILENO);
	}
	free(stdin_line);
	close(fd_tmp);
	return (1);
}
