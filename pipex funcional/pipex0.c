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

void	cuta_the(char **command, char **envp, int *pipe_fd, int fd)
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

void	cuta_the_second(char **command, char **envp, int *pipe_fd, int fd)
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
	dup2(fd, 1);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(caminho, command, envp);
}

int	main(int ac, char *av[], char *envp[])
{
	int fpid;
	int fd[2];
	int pipe_fd[2];
	char **first_command;
	char **second_command;

	(void)ac;
	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	first_command = ft_split(av[2], ' ');
	second_command = ft_split(av[3], ' ');
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC);
	fpid = fork();
	if (fpid == 0)
		cuta_the_first(first_command, envp, pipe_fd, fd[0]);
	else
	{
		waitpid(fpid, NULL, 0);
		cuta_the_second(second_command, envp, pipe_fd, fd[1]);
	}
	return (0);
}