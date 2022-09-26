/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noahrd0 <noahrd0@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:25:04 by noahrd0           #+#    #+#             */
/*   Updated: 2022/09/26 21:04:01 by noahrd0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int open_file(char *file, int type)
{
	int	outfile_fd;
	
	if (type == INFILE)
	{
		if (access(file, R_OK))
		{
			ft_putendl_fd("[>]	Invalid infile", 2);
			exit(EXIT_FAILURE);
		}	
		return (open(file, O_RDONLY));
	}
	else
	{
		outfile_fd = open(file, O_WRONLY | O_CREAT, 0777);
		if (access(file, W_OK))
		{
			ft_putendl_fd("[>]	Invalid outfile", 2);
			exit(EXIT_FAILURE);
		}
		return (outfile_fd);
	}
}

int	main(int ac, char **av)
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid;
	// !TEMPORAIRE
		char *argv[] = {"cat", NULL};
		char *env[] = {NULL};
		char *argv2[] = {"wc", "-l", NULL};
		char *env2[] = {NULL};
	// !
	
	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_fd("[>]	An error ocurred while opening the pipe.", 2);
		return (EXIT_FAILURE);
	}
	if (ac == 5)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putendl_fd("[>]	An error ocurred while duplicating the process.", 2);
			return (EXIT_FAILURE);
		}
		else if (pid == 0) // CHILD PROCESS, WRITE
		{
			infile_fd = open_file(av[1], INFILE);
			close(pipe_fd[0]);
			dup2(infile_fd, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(infile_fd);
			close(pipe_fd[1]);
			execve("/bin/cat", argv, env);
		} // MAIN PROCESS, READ
		waitpid(pid, NULL, 0);
		outfile_fd = open_file(av[4], OUTFILE);
		close(pipe_fd[1]);
		dup2(outfile_fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(outfile_fd);
		close(pipe_fd[0]);
		execve("/usr/bin/wc", argv2, env2);
	}
	else
		ft_putendl_fd("[>]	Invalid number of arguments.", 2);
	return (EXIT_FAILURE);
}
