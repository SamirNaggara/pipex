/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:34:15 by snaggara          #+#    #+#             */
/*   Updated: 2023/05/31 13:03:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft-plus/libft/libft.h"
# include "libft-plus/printf/ft_printf.h"
# include "libft-plus/get-next-line/get_next_line.h"
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>



typedef struct s_data
{
	char 	*file_content;
	char 	*file_in;
	char 	*file_out;
	char 	**path;
	char	*cmd1;
	char	*cmd2;
	int		ac;
	char	**av;
	char	**envp;
	char	*stop_str;
	int		infile;
}	t_data;

char	*ft_get_all_content(int fd);
t_data	*ft_init();
char	**ft_get_path(char **envp);
char	*ft_add_slash(char *path);
int		ft_nb_slash_to_add(char *path);
void	ft_exec_cmd(t_data *d, char *cmd);
int		ft_inverse_stdin(t_data *d);
int		ft_free_double_tab(char **path);
int		ft_inverse_stdout(t_data *d);
int		ft_free_path_and_d(t_data *d);
int		ft_exec_both(t_data *d);
int		ft_process_cmd2(t_data *d, int *fd);
int		ft_process_cmd1(t_data *d, int *fd);
void	ft_parse_infile(t_data *d, char **av);
void	ft_parse_classic(t_data *d, char **av);




#endif
