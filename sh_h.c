#include "shell.h"

/**
 * ft_hsh - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ft_hsh(info_t *info, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			ft_puts("$ ");
		ft_eputchar(BUF_FLUSH);
		r = ft_get_input(info);
		if (r != -1)
		{
			ft_set_info(info, av);
			builtin_ret = ft_find_builtin(info);
			if (builtin_ret == -1)
				ft_find_cmd(info);
		}
		else if (interactive(info))
			ft_putchar('\n');
		ft_free_info(info, 0);
	}
	ft_write_history(info);
	ft_free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * ft_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int ft_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", ft_myexit},
		{"env", ft_myenv},
		{"help", ft_myhelp},
		{"history", ft_myhistory},
		{"setenv", ft_mysetenv},
		{"unsetenv", ft_myunsetenv},
		{"cd", ft_mycd},
		{"alias", ft_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (ft_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * ft_find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ft_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!ft_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = ft_find_path(info, ft_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		ft_fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || ft_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && ft_is_cmd(info, info->argv[0]))
			ft_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			ft_print_error(info, "not found\n");
		}
	}
}

/**
 * ft_fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ft_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = ft_fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, ft_get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				ft_print_error(info, "Permission denied\n");
		}
	}
}
