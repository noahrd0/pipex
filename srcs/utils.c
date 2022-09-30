/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:01:06 by nradal            #+#    #+#             */
/*   Updated: 2022/09/30 18:01:37 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *file, int type)
{
	int	outfile_fd;

	if (type == INFILE)
	{
		if (access(file, R_OK))
			return (-1);
		return (open(file, O_RDONLY));
	}
	else
	{
		outfile_fd = open(file, O_WRONLY | O_CREAT, 0777);
		if (access(file, W_OK))
			return (-1);
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
		exit_perror("malloc in clean_cmd", 2);
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
	if (!ft_isalpha(cmd[0]))
		return (NULL);
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
		if (access(bin, F_OK) == 0)
			return (return_free(bin, cmd));
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (return_free(NULL, cmd));
}

int	waiting_pid(pid_t pid, int *pipe_fd, int close_pipe)
{
	if (close_pipe == YES)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		ft_putendl_fd("[>]	waiting pid in waiting_pid", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
