/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:57:52 by nradal            #+#    #+#             */
/*   Updated: 2022/09/30 18:01:44 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	infile_process(char **av, int *pipe_fd, char **envp, char *path)
{
	int		infile_fd;
	pid_t	pid;
	char	**cmds;

	cmds = ft_split(av[2], ' ');
	if (!cmds)
		exit_error("Split in infile", 2);
	pid = fork();
	if (pid == -1)
		exit_perror("fork in infile", 2);
	else if (pid == 0)
	{
		infile_fd = open_file(av[1], INFILE);
		if (infile_fd != -1)
			if (close(pipe_fd[0]) != -1)
				if (dup2(infile_fd, STDIN_FILENO) != -1)
					if (dup2(pipe_fd[1], STDOUT_FILENO) != -1)
						if (close(infile_fd) != -1)
							if (close(pipe_fd[1]) != -1)
								(execve(path, cmds, envp));
		leave_clean(cmds, path);
		exit_perror("Infile_process ", 2);
	}
	leave_clean(cmds, path);
	return (waiting_pid(pid, pipe_fd, NO));
}

int	outfile_process(char **av, int *pipe_fd, char **envp, char *path)
{
	int		outfile_fd;
	pid_t	pid;
	char	**cmds;

	cmds = ft_split(av[3], ' ');
	if (!cmds)
		exit_error("Split in outfile", 2);
	pid = fork();
	if (pid == -1)
		exit_perror("fork in outfile", 2);
	else if (pid == 0)
	{
		outfile_fd = open_file(av[4], OUTFILE);
		if (outfile_fd != -1)
			if (close(pipe_fd[1]) != -1)
				if (dup2(outfile_fd, STDOUT_FILENO) != -1)
					if (dup2(pipe_fd[0], STDIN_FILENO) != -1)
						if (close(outfile_fd) != -1)
							if (close(pipe_fd[0]) != -1)
								(execve(path, cmds, envp));
		leave_clean(cmds, path);
		exit_perror("Outfile process ", 2);
	}
	leave_clean(cmds, path);
	return (waiting_pid(pid, pipe_fd, YES));
}
