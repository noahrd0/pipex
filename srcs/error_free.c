/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:59:20 by nradal            #+#    #+#             */
/*   Updated: 2022/09/30 18:01:40 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_perror(char *str, int fd)
{
	ft_putstr_fd("[>]	", fd);
	perror(str);
	exit(-1);
}

void	exit_error(char *str, int fd)
{
	ft_putstr_fd("[>]	", fd);
	ft_putendl_fd(str, fd);
	exit(-1);
}

char	*return_free(char *ret, char *fr)
{
	free(fr);
	return (ret);
}

void	leave_clean(char **cmds, char *path)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free (cmds);
	free (path);
}
