/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:25:04 by noahrd0           #+#    #+#             */
/*   Updated: 2022/09/29 16:20:05 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_error(char *str, int fd)
{
	ft_putstr_fd("[>]	An error occured : ", 2);
	ft_putendl_fd(str, fd);
	exit(EXIT_FAILURE);
}

char	*return_free(char *ret, char *fr)
{
	free(fr);
	return (ret);
}

int	open_file(char *file, int type)
{
	int	outfile_fd;

	if (type == INFILE)
	{
		if (access(file, R_OK))
			exit_error("infile in open_file", 2);
		return (open(file, O_RDONLY));
	}
	else
	{
		outfile_fd = open(file, O_WRONLY | O_CREAT, 0777);
		if (access(file, W_OK))
			exit_error("outfile in open_file", 2);
		return (outfile_fd);
	}
}

char	*clean_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*clean_cmd;

	i = 0;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	clean_cmd = malloc(sizeof(char) * i + 1);
	if (!clean_cmd)
	{
		free(clean_cmd);
		exit_error("malloc in clean_cmd", 2);
	}
	j = 0;
	while (j < i)
	{
		clean_cmd[j] = cmd[j];
		j++;
	}
	clean_cmd[j] = '\0';
	return (clean_cmd);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	cmd = clean_cmd(cmd);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (return_free(NULL, cmd));
	path = env[i] + 5;
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strichr(path, ':'));
		bin = ft_strcjoin(dir, cmd, '/');
		free(dir);
		if (access(bin, F_OK) == 0) // F_OK check si le fichier existe
			return (return_free(bin, cmd));
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (return_free(NULL, cmd));
}

void leave_clean(char **cmds, char *path)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("%d : %s\n", i, cmds[i]);
		free(cmds[i]);
		i++;
	}
	free (cmds);
	free (path);
}

int	infile_process(char **av, int *pipe_fd, char **envp, char *path, char **cmds)
{
	int		infile_fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork in infile", 2);
	else if (pid == 0)
	{
		infile_fd = open_file(av[1], INFILE);
		if (close(pipe_fd[0]) != -1)
			if (dup2(infile_fd, STDIN_FILENO) != -1)
				if (dup2(pipe_fd[1], STDOUT_FILENO) != -1)
					if (close(infile_fd) != -1)
						if (close(pipe_fd[1]) != -1)
							return (execve(path, cmds, envp));
		exit_error("error in infile_process", 2);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		leave_clean(cmds, path);
		exit_error("waitpid in infile", 2);
	}
	leave_clean(cmds, path);
	return (EXIT_SUCCESS);
}

int	outfile_process(char **av, int *pipe_fd, char **envp, char *path, char **cmds)
{
	int		outfile_fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork in outfile", 2);
	else if (pid == 0)
	{
		outfile_fd = open_file(av[4], OUTFILE);
		if (close(pipe_fd[1]) != -1)
			if (dup2(outfile_fd, STDOUT_FILENO) != -1)
				if (dup2(pipe_fd[0], STDIN_FILENO) != -1)
					if (close(outfile_fd) != -1)
						if (close(pipe_fd[0]) != -1)
							return (execve(path, cmds, envp));
	exit_error("error in outfile_process", 2);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (waitpid(pid, NULL, 0) == -1)
	{
		leave_clean(cmds, path);
		exit_error("waitpid in infile", 2);
	}
	leave_clean(cmds, path);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	char	*path;
	char	**cmds;

	if (pipe(pipe_fd) == -1)
		exit_error("pipe in main", 2);
	if (ac == 5)
	{
		path = get_path(av[2], envp);
		if (!path)
			exit_error("command not found", 2);
		cmds = ft_split(av[2], ' ');
		if (infile_process(av, pipe_fd, envp, path, cmds) == -1)
			exit_error("execve in infile_process", 2);
		path = get_path(av[3], envp);
		if (!path)
			exit_error("command not found", 2);
		cmds = ft_split(av[3], ' ');
		if (outfile_process(av, pipe_fd, envp, path, cmds) == -1)
			exit_error("execve in infile_process", 2);
	}
	else
		exit_error("number of arguments", 2);
	return (0);
}


/*int	execution(char **av, int *pipe_fd, pid_t pid, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	
	if (pid == 0)	// CHILD PROCESS, WRITE
	{
		infile_fd = open_file(av[1], INFILE);
		if (close(pipe_fd[0]) != -1)
			if (dup2(infile_fd, STDIN_FILENO) != -1)
				if (dup2(pipe_fd[1], STDOUT_FILENO) != -1)
					if (close(infile_fd) != -1)
						if (close(pipe_fd[1]) != -1)
							return (execve(get_path(av[2], envp), ft_split(av[2], ' '), envp));
							//return (execve("/bin/cat", ft_split(av[2], ' '), env));
		exit_error("[>]	An error ocurred while executing child process.", 2);
	} 				// MAIN PROCESS, READ
	outfile_fd = open_file(av[4], OUTFILE);
	if (waitpid(pid, NULL, 0) != -1)
		if (close(pipe_fd[1]) != -1)
			if (dup2(outfile_fd, STDOUT_FILENO) != -1)
				if (dup2(pipe_fd[0], STDIN_FILENO) != -1)
					if (close(outfile_fd) != -1)
						if (close(pipe_fd[0]) != -1)
							return (execve(get_path(av[3], envp), ft_split(av[3], ' '), envp));
	exit_error("[>]	An error ocurred while executing main process.", 2);
}*/

// int	main(int ac, char **av, char **envp)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(pipe_fd) == -1)
// 		exit_error("pipe in main", 2);
// 	if (ac == 5)
// 	{
// 		pid1 = fork();
// 		if (pid1 == -1)
// 			exit_error("(pid1) fork in main", 2);
// 		else if (pid1 == 0)
// 			if (infile_process(av, pipe_fd, envp) == -1)
// 				exit_error("execve in infile_process", 2);
// 		if (waitpid(pid1, NULL, 0) == -1)
// 			exit_error("(pid1) waitpid in main", 2);
// 		pid2 = fork();
// 		if (pid2 == -1)
// 			exit_error("(pid2) fork in main", 2);
// 		else if (pid2 == 0)
// 			if (outfile_process(av, pipe_fd, envp) == -1)
// 				exit_error("execve in infile_process", 2);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		if (waitpid(pid2, NULL, 0) == -1)
// 			exit_error("(pid2) waitpid in main", 2);
// 	}
// 	else
// 		exit_error("number of arguments", 2);
// 	return (0);
// }