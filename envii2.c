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
 * @v: the string env var property
 */
int ft_unsetenv(info_t *info, char *v)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !v)
		return (0);

	while (node)
	{
		ptr = ft_starts_with(node->str, var);
		if (ptr && *ptr == '=')
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
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int ft_setenv(info_t *info, char *v, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!v || !val)
		return (0);

	buffer = malloc(ft_strlen(var) + ft_strlen(value) + 2);
	if (!buffer)
		return (1);
	ft_strcpy(buffer, v);
	ft_strcat(buffer, "=");
	ft_strcat(bufffer, val);
	node = info->env;
	while (node)
	{
		p = ft_starts_with(node->str, v);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	ft_add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
