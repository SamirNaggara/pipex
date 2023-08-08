/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:47 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/08 17:09:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(t_data *d)
{
	int		i;
	char	**path;
	char	*str_path;

	i = 0;
	while (d->path_exist && d->envp[i] && !ft_strnstr(d->envp[i], "PATH=", 5))
		i++;
	str_path = ft_add_slash(d->envp[i] + 5);
	if (!str_path)
		return (NULL);
	path = ft_split(str_path, ':');
	free(str_path);
	if (!path)
		return (NULL);
	return (path);
}

char	*ft_add_slash(char *path)
{
	char	*to_return;
	int		i;
	int		j;

	to_return = (char *)malloc(sizeof(char)
			* (ft_strlen(path) + ft_nb_slash_to_add(path) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
	{
		if (path[j] == ':')
			to_return[i++] = '/';
		to_return[i++] = path[j++];
	}
	to_return[i] = '/';
	to_return[i + 1] = '\0';
	return (to_return);
}

int	ft_nb_slash_to_add(char *path)
{
	int	i;
	int	nb;

	if (!path || !*path)
		return (-1);
	nb = 1;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			nb++;
		i++;
	}
	return (nb);
}
