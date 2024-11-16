/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:05:09 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/15 19:31:32 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_caminho(char **path_copy, char **command)
{
	int		i;
	int		status;
	char	*caminho;

	i = 0;
	while (path_copy[i])
	{
		caminho = ft_strjoin(path_copy[i], "/");
		caminho = ft_strjoin(caminho, command[0]);
		status = access(caminho, X_OK | F_OK);
		if (status == 0)
			return (caminho);
		free(caminho);
		i++;
	}
	return (NULL);
}

void	cuta_the_first(char **command, char **envp, int *pipe_fd, int fd)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	path = getenv("PATH");
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		perror("Error");
		free_matrix(path_copy);
		free_matrix(command);
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(caminho, command, envp);
}

void	cuta_in_between(char **command, char **envp, int *pipe_fd)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	path = getenv("PATH");
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		perror("Error");
		free_matrix(path_copy);
		free_matrix(command);
		exit(1);
	}
	dup2(pipe_fd[0], 0);
	dup2(pipe[1], 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(caminho, command, envp);
}

void	cuta_the_second(char **command, char **envp, int *pipe_fd, int fd)
{
	char *caminho;
	char *path;
	char **path_copy;

	path = getenv("PATH");
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		perror("Error");
		free_matrix(path_copy);
		free_matrix(command);
		exit(1);
	}
	dup2(pipe_fd[0], 0);
	dup2(fd, 1);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(caminho, command, envp);
}