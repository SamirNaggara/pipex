/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:34:15 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/05 11:07:47 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft-plus/libft/libft.h"
# include "../libft-plus/printf/ft_printf.h"
# include "../libft-plus/get-next-line/get_next_line.h"
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# ifndef TMP_FILE_NAME_H
#  define TMP_FILE_NAME_H
#  define TMP_FILE_NAME "tmp_file_stdin"
# endif

# ifndef ERROR_H
#  define ERROR_H
#  define E_PERMISSION "permission non accordée "
#  define E_OUT_FILE "perreur lors de la création du fichier de sortie"
#  define E_DUP2 "la fonction dup2 n'a pas fonctionné correctement : "
#  define E_FILE_NOT_FOUND "Erreur inconnu à l'ouverture du fichier std_in: "
#  define E_FILE_NOT_FOUND2 "aucun fichier ou dossier de ce type: "
#  define E_CMD_NOT_FOUND "command not found: "
#  define E_NB_ARG "il n'y a pas assez d'argument"
# endif

typedef struct s_data
{
	char	*file_content;
	char	*file_in;
	char	*file_out;
	char	**path;
	char	*cmd1;
	char	*cmd2;
	int		ac;
	char	**av;
	char	**envp;
	char	*stop_str;
	int		here_doc;
	char	*stdin_line;
	int		fd_in;

}	t_data;

t_data	*ft_init(int ac, char **av, char **envp);
char	**ft_get_path(char **envp);
char	*ft_add_slash(char *path);
int		ft_nb_slash_to_add(char *path);
int		ft_exec_cmd(t_data *d, char *cmd);
int		ft_inverse_stdin(t_data *d);
int		ft_free_double_tab(char **path);
int		ft_inverse_stdout(t_data *d);
int		ft_free_path_and_d(t_data *d);
int		ft_fork(t_data *d);
void	ft_process_cmd2(t_data *d, int *fd);
void	ft_process_cmd1(t_data *d, int *fd);
int		ft_parse_here_doc(t_data *d, char **av);
int		ft_parse_classic(t_data *d, char **av);
int		ft_stdin_file(t_data *d);
int		ft_close_all_fds(void);
int		ft_cmd_valid(t_data *d, char *cmd);
int		ft_test_cmds(t_data *d);
int		ft_parse_doc(t_data *d, char **av);
t_data *ft_free_d_path_close_fds(t_data *data);
t_data *ft_free_d_close_fds(t_data *d);
int	ft_create_stdout(t_data *d);


#endif