/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/16 04:33:00 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// implementei a ideia principal das múltiplas pipelines
// por agora com erro, dá loop infinito ao executar
int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	int		pipe_fd[2];
	char	**last_command;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	i = 2;
	last_command = ft_split(av[ac - 2], ' ');
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC);
	while (i < ac - 2)
	{
		fpid = fork();
		if (fpid == 0)
			cuta_the_first(ft_split(av[i], ' '), envp, pipe_fd, fd[0]);
		else
		{
			waitpid(fpid, NULL, 0);
			cuta_in_between(ft_split(av[i + 1], ' '), envp, pipe_fd);
		}
		i++;
	}
	fpid = fork();
	if (fpid == 0)
	{
		// cuta_in_between(ft_split(av[i], ' '), envp, pipe_fd);
		cuta_the_second(last_command, envp, pipe_fd, fd[1]);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(fpid, NULL, 0);
		// cuta_the_second(last_command, envp, pipe_fd, fd[1]);
	}
	return (0);
}
