#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define TYPE_PIPE 1
#define TYPE_BREAK 2
#define TYPE_REIN 3
#define TYPE_REOUT 4

typedef struct		s_set
{
	char			*args[30];
	int				fds[2];
	int				type;
	int				fd;
	struct s_set	*next;
	struct s_set	*prev;
}					t_tokens;

int run(t_tokens *tokens, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		pipe_open;

	ret = EXIT_FAILURE;
	pipe_open = 0;
	if (tokens->type == TYPE_PIPE || (tokens->prev && tokens->prev->type == TYPE_PIPE))
	{
		pipe_open = 1;
		pipe(tokens->fds);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		printf("child process========================\n");
		if (tokens->type == TYPE_PIPE)
			dup2(tokens->fds[1], STDOUT_FILENO);

		if (tokens->type == TYPE_BREAK)
			dup2(tokens->fd, STDIN_FILENO);

		if (tokens->prev && (tokens->prev->type == TYPE_PIPE))
			dup2(tokens->prev->fds[0], STDIN_FILENO);
		if ((ret = execve(tokens->args[0], tokens->args, env) < 0))
			exit(0); 
		printf("child process finished===============\n");
	}
	else
	{
		printf("parent process=======================\n");
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(tokens->fds[1]);
			if (!tokens->next || tokens->type == TYPE_BREAK)
				close(tokens->fds[0]);
		}
		if (tokens->prev && tokens->prev->type == TYPE_PIPE)
			close(tokens->prev->fds[0]);
		if (tokens->type == TYPE_BREAK)
			close(tokens->fd);
		printf("parent process finished==============\n");
	}
	return (ret);
}
#if 0
int main(int argc, char *argv[], char *env[]) {
	t_tokens	set1;
	set1.args[0] = "/bin/ls";
	set1.args[1] = "-al";
	set1.args[2] = NULL;
	set1.type = TYPE_PIPE;

	t_tokens	set2;
	set2.args[0] = "/usr/bin/grep";
	set2.args[1] = "main";
	set2.args[2] = NULL;
	set2.type = TYPE_BREAK;
	set2.fd = open("test.txt", O_CREAT | O_APPEND | O_WRONLY, 0755);

	set1.prev = NULL;
	set1.next = &set2;
	set2.prev = &set1;
	set2.next = NULL;
	printf("first run\n");
	run(&set1, env);
	printf("second run\n");
	run(&set2, env);
	return (0);
}
#endif

#if 0
int main(int argc, char *argv[], char *env[]) {
	t_tokens	set1;
	set1.args[0] = "/bin/ls";
	set1.args[1] = "-al";
	set1.args[2] = NULL;
	set1.type = TYPE_BREAK;
	set1.fd = open("test.txt", O_CREAT | O_APPEND | O_WRONLY, 0755);

	printf("first run\n");
	run(&set1, env);
	return (0);
}
#endif
int main(int argc, char *argv[], char *env[]) {
	t_tokens	set1;
	set1.args[0] = "/usr/bin/sort";
	set1.args[1] = NULL;
	set1.type = TYPE_BREAK;
	set1.fd = open("test.txt", O_RDONLY);

	run(&set1, env);
	return (0);
}
