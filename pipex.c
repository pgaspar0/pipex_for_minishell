/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/22 10:13:20 by jorcarva         ###   ########.fr       */
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

static void	keeping_up_main(char *av[], int *fd, int *i, int ac)
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		here_doc(av[2]);
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		*i = 3;
	}
	else
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] == -1)
			exit(EXIT_FAILURE);
		dup2(fd[0], 0);
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
		{
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		*i = 2;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	char	**command;
	char	**last_command;

	if (ac)
		keeping_up_main(av, fd, &i, ac);
	last_command = ft_split(av[ac - 2], ' ');
	while (i < ac - 2)
	{
		command = ft_split(av[i], ' ');
		forka(command, envp);
		free_matriz(command);
		i++;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_second(last_command, envp, fd[1]);
	else
		waitpid(fpid, NULL, 0);
	free_matriz(command);
	free_matriz(last_command);
	return (0);
}
