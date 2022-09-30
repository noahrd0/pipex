/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:25:04 by nradal            #+#    #+#             */
/*   Updated: 2022/09/30 18:01:23 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	char	*path;

	if (pipe(pipe_fd) == -1)
		exit_perror("Main :", 2);
	if (ac == 5)
	{
		path = get_path(av[2], envp);
		if (!path)
			exit_error("Get_path : Command not found", 2);
		if (infile_process(av, pipe_fd, envp, path) == -1)
			exit_perror("Execve (infile_process)", 2);
		path = get_path(av[3], envp);
		if (!path)
			exit_error("Get_path : Command not found", 2);
		if (outfile_process(av, pipe_fd, envp, path) == -1)
			exit_perror("Execve (outfile_process)", 2);
	}
	else
		exit_error("Invalid number of arguments.", 2);
	return (0);
}
