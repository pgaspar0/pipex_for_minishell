/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/15 19:35:41 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	int		pipe_fd[2];
	char	**first_command;
	char	**second_command;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	i = 2;
	last_command = ft_split(av[ac - 2], ' ');
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC);
	while (i < ac - 1)
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
		cuta_the_first(first_command, envp, pipe_fd, fd[0]);
	else
	{
		waitpid(fpid, NULL, 0);
		cuta_the_second(last_command_command, envp, pipe_fd, fd[1]);
	}
	i++;
	return (0);
}
