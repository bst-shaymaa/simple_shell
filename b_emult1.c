#include "shell.h"

/**
 * ft_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int ft_myhistory(info_t *info)
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
	return (ft_add_node_end(&(info->alias), str, 0) == NULL);
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
			ft_print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
