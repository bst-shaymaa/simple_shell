#include "shell.h"

/**
 * ft_clear_info - initializes info_t struct
 * @info: struct address
 */
void ft_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * ft_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void ft_set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = ft_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		ft_replace_alias(info);
		ft_replace_vars(info);
	}
}

/**
 * ft_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void ft_free_info(info_t *info, int all)
{
	ft_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			ft_free_list(&(info->env));
		if (info->history)
			ft_free_list(&(info->history));
		if (info->alias)
			ft_free_list(&(info->alias));
		ft_ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		ft_putchar(BUF_FLUSH);
	}
}