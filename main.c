/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:28:18 by snaggara          #+#    #+#             */
/*   Updated: 2023/05/31 13:19:30 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*d;

	d = ft_init(ac, av, envp);
	if (!d)
		return (0);

	if (!ft_exec_both(d))
		return (ft_free_path_and_d(d));
	ft_free_double_tab(d->path);
	free(d);
	return (0);
}

int	ft_exec_both(t_data *d)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;


	if (!ft_inverse_stdin(d))
			return (0);
	if (pipe(fd) == -1)
		perror("error sur le pipe");
	child1 = fork();
	if (child1 == 0)
		ft_process_cmd1(d, fd);
	child2 = fork();
	if (child2 == 0)
		ft_process_cmd2(d, fd);
	close(fd[0]);
	close(fd[1]);
	wait(&child1);
	wait(&child2);
	return (1);
}

int	ft_process_cmd1(t_data *d, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_exec_cmd(d, d->cmd1);
	close(fd[1]);
	return (1);
}

int	ft_process_cmd2(t_data *d, int *fd)
{
	int		fd_out;

	wait(NULL);
	close(fd[1]);
	//printf("voila le sdtin du parent : %s\n", ft_get_all_content(fd[0]));
	dup2(fd[0], STDIN_FILENO);
	fd_out = open(d->file_out, O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (fd_out == -1) {
		ft_printf(STDERR_FILENO, "Erreur lors de la création du fichier de sortie :)");
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Erreur lors de l'exécution de dup2 pour la sortie !!");
		return (0);
	}
	
	ft_exec_cmd(d, d->cmd2);
	close(fd_out);
	close(fd[0]);
	return (1);
}

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

int	ft_inverse_stdout(t_data *d)
{
	int	fd_out;

	fd_out = open(d->file_out, O_RDONLY);

	if (fd_out != -1 && access(d->file_out, W_OK) == -1)
	{
		ft_printf(STDERR_FILENO, "Nous n'avons pas les permissions d'écriture sur le fichier de sortie\n");
		close(fd_out);

		return (0);
	}
	fd_out = open(d->file_out, O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (fd_out == -1) {
        ft_printf(STDERR_FILENO, "Erreur lors de la création du fichier de sortie");
        return (0);
    }

	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Erreur lors de l'exécution de dup2 pour la sortie");
        return (0);
	}
	close(fd_out);
	return (1);
}

int	ft_inverse_stdin(t_data *d)
{
	int	fd_in;

	if (access(d->file_in, R_OK) == -1)
	{
		ft_printf(STDERR_FILENO, "Nous n'avons pas les permissions de lecture sur le fichier d'entrée\n");
		return (0);
	}
	fd_in = open(d->file_in, O_RDONLY);
	if (fd_in == -1) {
        ft_printf(STDERR_FILENO, "Erreur lors de l'ouverture du fichier d'entrée: No such file or directory");
        return (0);
    }

	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Erreur lors de l'exécution de dup2");
        return (0);
	}
	close(fd_in);
	return (1);
}

void	ft_exec_cmd(t_data *d, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	**arguments;
	int		status;
	
	(void)cmd;
	arguments = ft_split(cmd, ' ');
	i = 0;
	//ft_printf(STDERR_FILENO, "j'execute la commande : %s\n", cmd);
	while (d->path[i])
	{
		full_cmd = ft_strjoin(d->path[i], arguments[0]);
		if (!full_cmd)
			return ;
		status = execve(full_cmd, arguments, d->envp);
		free(full_cmd);
		i++;
	}
	ft_free_double_tab(arguments);
	if (status == -1)
		perror("Une erreur est survenue : ");

	//ft_printf(STDERR_FILENO, "Command not found: %s", cmd);
}
char	**ft_get_path(char **envp)
{
	int		i;
	char	**path;
	char	*str_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	str_path = ft_add_slash(envp[i] + 5);
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

	to_return = (char *)malloc(sizeof(char) *
			(ft_strlen(path) + ft_nb_slash_to_add(path) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	j = 0;
	while(path[j])
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

char	*ft_get_all_content(int fd)
{
	char	*file_content;
	char	*line;
	char	*tmp;

	file_content = get_next_line(fd);
	while (file_content)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin(file_content, line);
		free(file_content);
		free(line);
		file_content = tmp;
	}
	return (file_content);

}

t_data	*ft_init(int ac, char **av, char **envp)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (0);
	if (ac < 5)
	{
		ft_printf(STDERR_FILENO, "il n'y a pas assez d'argument\n");
		return (0);
	}
	d->envp = envp;
	d->ac = ac;
	d->av = av;
	d->path = ft_get_path(envp);
	if (!d->path)
	{
		free(d);
		return (0);
	}
	if (ft_strncmp(av[1], "here_doc", 6) == 0)
	{
		ft_parse_infile(d, av);
	}
	ft_parse_classic(d, av);
	
	return (d);
}

void	ft_parse_infile(t_data *d, char **av)
{
	d->file_in = av[1];
	d->stop_str = av[2];
	d->cmd1 = av[3];
	d->cmd2 = av[4];
	d->file_out = av[5];
	d->infile = 1;
}


void	ft_parse_classic(t_data *d, char **av)
{
	d->file_in = av[1];
	d->cmd1 = av[2];
	d->cmd2 = av[3];
	d->file_out = av[4];
	d->infile = 0;
}