#include "shell.h"

/**
 * ft_get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **ft_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = ft_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * ft_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int ft_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = ft_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = ft_delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * ft_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int ft_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(ft_strlen(var) + ft_strlen(value) + 2);
	if (!buf)
		return (1);
	ft_strcpy(buf, var);
	ft_strcat(buf, "=");
	ft_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = ft_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	ft_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
