/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/20 18:22:50 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	char	**last_command;

	if (!ft_strcmp(av[1], "here_doc"))
	{
		here_doc(av[2]);
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		i = 3;
	}
	else
	{
		fd[0] = open(av[1], O_RDONLY);
		dup2(fd[0], 0);
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		i = 2;
	}
	last_command = ft_split(av[ac - 2], ' ');
	while (i < ac - 2)
	{
		forka(ft_split(av[i], ' '), envp);
		i++;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_second(last_command, envp, fd[1]);
	else
		waitpid(fpid, NULL, 0);
	return (0);
}
