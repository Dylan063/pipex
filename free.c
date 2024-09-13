/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:53:39 by dravaono          #+#    #+#             */
/*   Updated: 2024/04/11 16:05:23 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_command(t_command *cmd)
{
	free(cmd->lechemin);
	free(cmd->ledeuxiemechemin);
	free_tab(cmd->cmd);
	free_tab(cmd->cmdd);
}

void	ft_error(t_command *cmd, char *str)
{
	free_command(cmd);
	perror(str);
	exit(1);
}

void	free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_justerror(char *str)
{
	perror(str);
	exit(1);
}
