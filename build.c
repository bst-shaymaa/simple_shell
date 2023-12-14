#include "shell.h"

/**
 * ft_myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int ft_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			ft_print_error(info, "Illegal number: ");
			ft_eputs(info->argv[1]);
			ft_eputchar('\n');
			return (1);
		}
		info->err_num = ft_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * ft_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ft_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		ft_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = ft_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = ft_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (ft_strcmp(info->argv[1], "-") == 0)
	{
		if (!ft_getenv(info, "OLDPWD="))
		{
			ft_puts(s);
			ft_putchar('\n');
			return (1);
		}
		ft_puts(ft_getenv(info, "OLDPWD=")), ft_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = ft_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		ft_print_error(info, "can't cd to ");
		ft_eputs(info->argv[1]), ft_eputchar('\n');
	}
	else
	{
		ft_setenv(info, "OLDPWD", ft_getenv(info, "PWD="));
		ft_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ft_myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ft_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	ft_puts("help call works. Function not yet implemented \n");
	if (0)
		ft_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
#include "shell.h"

/**
 * ft_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int ft__myhistory(info_t *info)
{
	ft_print_list(info->history);
	return (0);
}

/**
 * ft_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = ft_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = ft_delete_node_at_index(&(info->alias),
		ft_get_node_index(info->alias, ft_node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * ft_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_set_alias(info_t *info, char *str)
{
	char *p;

	p = ft_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (ft_unset_alias(info, str));

	ft_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * ft_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = ft_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			ft_putchar(*a);
		ft_putchar('\'');
		ft_puts(p + 1);
		ft_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ft_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ft_myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			ft_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = ft_strchr(info->argv[i], '=');
		if (p)
			ft_set_alias(info, info->argv[i]);
		else
			ft_print_alias(ft_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}