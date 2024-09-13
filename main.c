/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:44 by dravaono          #+#    #+#             */
/*   Updated: 2024/04/11 16:05:13 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_command	cmd;
	char		*str;

	if (ac != 5)
		ft_justerror("Error\nargs");
	if (!env[0])
		ft_justerror("Error\nenv");
	if (av[2][0] == 0 || av[2][0] == ' ' || av[3][0] == 0 || av[3][0] == ' ')
		ft_justerror("Error\nargs");
	cmd.cmd = ft_split(av[2], ' ');
	str = find_path(env);
	cmd.cmdd = ft_split(av[3], ' ');
	cmd.lechemin = good_path(cmd, str, cmd.cmd);
	cmd.ledeuxiemechemin = good_path(cmd, str, cmd.cmdd);
	free(str);
	filegood(cmd, av);
	pipex(cmd, av, env);
	free_command(&cmd);
	return (0);
}

void	filegood(t_command cmd, char **av)
{
	if (access(av[1], F_OK | X_OK) == -1)
	{
		ft_error(&cmd, "Error\nfile");
	}
	if (access(av[4], F_OK) == -1)
	{
		open(av[4], O_CREAT | O_WRONLY | O_TRUNC);
	}
	if (open(av[1], __O_DIRECTORY) != -1)
	{
		ft_error(&cmd, "Error\nfiledoss");
	}
	if (open(av[4], __O_DIRECTORY) != -1)
	{
		ft_error(&cmd, "Error\nfiledoss");
	}
}

char	*ft_strjoinps(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*sfinal;

	sfinal = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	j = 0;
	if (!sfinal)
		return (0);
	while (s1[i])
	{
		sfinal[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sfinal[i] = s2[j];
		i++;
		j++;
	}
	sfinal[i] = '\0';
	free(s1);
	return (sfinal);
}
