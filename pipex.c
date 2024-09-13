/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:33:35 by dravaono          #+#    #+#             */
/*   Updated: 2024/04/11 15:53:59 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_strdup(env[i] + 5));
		else
			i++;
	}
	return (0);
}

char	*good_path(t_command cmd, char *str, char **av)
{
	char	*charfinal;
	int		i;

	if (access(av[0], R_OK) == 0)
		return (av[0]);
	else
	{
		i = 0;
		cmd.tabchar = ft_split(str, ':');
		while (cmd.tabchar[i])
		{
			cmd.tab = ft_strjoin(cmd.tabchar[i], "/");
			charfinal = ft_strjoinps(cmd.tab, av[0]);
			if (access(charfinal, R_OK) == 0)
			{
				free_tab(cmd.tabchar);
				return (charfinal);
			}
			else
				i++;
			free(charfinal);
		}
		free_tab(cmd.tabchar);
	}
	return (0);
}

void	pipex(t_command cmd, char **av, char **envp)
{
	int	fdpipe[2];

	if (!cmd.lechemin || !cmd.ledeuxiemechemin)
		ft_error(&cmd, "Error\npath");
	if (pipe(fdpipe) == -1)
		ft_error(&cmd, "Error\npipe");
	cmd.parent = fork();
	if (cmd.parent < 0)
		ft_error(&cmd, "Error\nfork");
	if (cmd.parent == 0)
		child_process(cmd, av, envp, fdpipe);
	else
	{
		cmd.parents = fork();
		if (cmd.parents < 0)
			ft_error(&cmd, "Error\nfork");
		if (cmd.parents == 0)
			parent_process(cmd, av, envp, fdpipe);
		else
			waitpid(-1, NULL, 0);
	}
}

void	child_process(t_command cmd, char **av, char **envp, int *fdpipe)
{
	close(fdpipe[0]);
	cmd.infile = open(av[1], O_RDONLY);
	dup2(cmd.infile, STDIN_FILENO);
	dup2(fdpipe[1], STDOUT_FILENO);
	execve(cmd.lechemin, cmd.cmd, envp);
	if (execve(cmd.lechemin, cmd.cmd, envp) == -1)
		ft_error(&cmd, "Error\nexecve");
	close(fdpipe[1]);
}

void	parent_process(t_command cmd, char **av, char **envp, int *fdpipe)
{
	int	fd;

	close(fdpipe[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fdpipe[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(cmd.ledeuxiemechemin, cmd.cmdd, envp);
	if (execve(cmd.ledeuxiemechemin, cmd.cmdd, envp) == -1)
		ft_error(&cmd, "Error\nexceve2");
	close(fdpipe[0]);
}
