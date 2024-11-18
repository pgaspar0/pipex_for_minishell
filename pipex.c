/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/18 12:19:18 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* void	cuta_in_between(char **command, char **envp, int *pipe_fd)
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
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execve(caminho, command, envp);
} */

void	forka(char **command, char **envp)
{
	int	fpid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	fpid = fork();
	if (fpid == 0)
		cuta_in_between(command, envp, pipe_fd);
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		waitpid(fpid, NULL, 0);
	}
}

// implementei a ideia principal das múltiplas pipelines
// por agora com erro, dá loop infinito ao executar
int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	char	**last_command;

	i = 2;
	last_command = ft_split(av[ac - 2], ' ');
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC);
	dup2(fd[0], 0);
	while (i < ac - 2)
	{
		forka(ft_split(av[i], ' '), envp);
		i++;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_second(last_command, envp, fd[1]);
	else
	{
		// close(fd[0]);
		// close(fd[1]);
		waitpid(fpid, NULL, 0);
	}
	return (0);
}
