#include "shell.h"

/**
 * ft_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ft_is_chain(info_t *info, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->ft_cmd_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->ft_cmd_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->ft_cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * ft_check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the buffer char
 * @ptr: address of current position in buffer
 * @n: starting position in buffer
 * @len: length of buf
 *
 * Return: Void
 */
void ft_check_chain(info_t *info, char *buffer, size_t *ptr,
		size_t n, size_t len)
{
	size_t j = *ptr;

	if (info->ft_cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[n] = 0;
			j = len;
		}
	}
	if (info->ft_cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[n] = 0;
			j = len;
		}
	}

	*ptr = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = ft_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = ft_strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = ft_strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * ft_replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ft_replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!ft_strcmp(info->argv[i], "$?"))
		{
			ft_replace_string(&(info->argv[i]),
				ft_strdup(ft_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!ft_strcmp(info->argv[i], "$$"))
		{
			ft_replace_string(&(info->argv[i]),
				ft_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = ft_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			ft_replace_string(&(info->argv[i]),
				ft_strdup(ft_strchr(node->str, '=') + 1));
			continue;
		}
		ft_replace_string(&info->argv[i], ft_strdup(""));

	}
	return (0);
}

/**
 * ft_replace_string - replaces string
 * @prev: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ft_replace_string(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}
