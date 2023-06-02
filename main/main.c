/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:28:18 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:13 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// Samir il te reste a voir les fds open, c'est chelou, tu les vois avec  lsof | grep sam-acer | grep /home/sam-acer/Documents/42/pipex
// en ligne de commande.
// Apparemment, il faut fermer tout les fds à la fin d'un programme, ne pas en laisser un seul d'ouvert
// Meme pas stdin (chelou mais bon)
int	main(int ac, char **av, char **envp)
{
	t_data	*d;

	d = ft_init(ac, av, envp);
	if (!d)
		return (0);
	ft_fork(d);
	ft_free_double_tab(d->path);
	if (d->here_doc)
		unlink(TMP_FILE_NAME);
	free(d);
	return (0);
}
