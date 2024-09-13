/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:33:32 by dravaono          #+#    #+#             */
/*   Updated: 2024/04/11 16:04:45 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/inc/libft.h"
# include "./libft/inc/get_next_line_bonus.h"
# include "./libft/inc/ft_printf.h"

typedef struct s_command
{
	int		infile;
	int		outfile;
	char	*lechemin;
	char	*ledeuxiemechemin;
	char	*tab;
	char	**cmd;
	char	**cmdd;
	char	**tabchar;
	pid_t	parent;
	pid_t	parents;
}			t_command;

char		**argss(char *av);
char		*find_path(char **env);
char		*good_path(t_command cmd, char *str, char **av);
void		ft_fork(t_command cmd, char **av);
void		pipex(t_command cmd, char **av, char **envp);
void		parent_process(t_command cmd, char **av, char **envp, int *fdpipe);
void		child_process(t_command cmd, char **av, char **envp, int *fdpipe);
void		filegood(t_command cmd, char **av);
void		ft_error(t_command *cmd, char *str);
void		free_tab(char **str);
char		*ft_strjoinps(char *s1, char *s2);
void		free_command(t_command *cmd);
void		ft_justerror(char *str);

#endif