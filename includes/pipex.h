/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:14:43 by noahrd0           #+#    #+#             */
/*   Updated: 2022/10/03 15:54:59 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//	LIBRARIES ###############################################################
# include "../libft/includes/libft.h"//										#
# include <fcntl.h>//														#
# include <sys/wait.h>//													#
// ##########################################################################

//	DEFINE ##################################################################
# define INFILE 0//															#
# define OUTFILE 1//														#
# define YES 0//															#
# define NO 1//																#
// ##########################################################################

//	FUNCTIONS ###############################################################
//	CHILD_PROCESS_C															#
int		infile_process(char **av, int *pipe_fd, char **envp, char *path);//	#
int		outfile_process(char **av, int *pipe_fd, char **envp, char *path);//#
//	UTILS_C																	#
int		open_file(char *file, int type);//									#
char	*clean_cmd(char *cmd);//											#
char	*get_path(char *cmd, char **env);//									#
int		waiting_pid(pid_t pid, int *pipe_fd, int close_pipe);//				#
//	ERROR_FREE_C															#
void	exit_perror(char *str, int fd);//									#
void	exit_error(char *str, int fd);//									#
char	*return_free(char *ret, char *fr);//								#
void	leave_clean(char **cmds, char *path);//								#
// ##########################################################################

#endif