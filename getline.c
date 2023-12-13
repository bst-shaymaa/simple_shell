#include "shell.h"

/**
 * ft_input_buf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t ft_input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, ft_sigintHandler);
#if USE_GETLINE
		r = ft_getline(buffer, &len_p, stdin);
#else
		r = ft_getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			ft_remove_comments(*buffer);
			ft_build_history_list(info, *buffer, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * ft_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t ft_get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t n = 0;
	char **buffer_pt = &(info->arg), *ptr;

	ft_putchar(BUF_FLUSH);
	n = ft_input_buf(info, &buffer, &len);
	if (n == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buffer + i;

		ft_check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (ft_is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buff_type = CMD_NORM;
		}

		*buffer_pt = ptr;
		return (ft_strlen(ptr));
	}

	*buffer_pt = buffer;
	return (n);
}

/**
 * ft_read_buf - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: r
 */
ssize_t ft_read_buf(info_t *info, char *buffer, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(info->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}

/**
 * ft_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int ft_getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t n;
	ssize_t r = 0, s = 0;
	char *pt = NULL, *new_ptr = NULL, *c;

	pt = *ptr;
	if (pt && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = ft_read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = ft_strchr(buffer + i, '\n');
	n = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = _realloc(pt, s, s ? s + n : n + 1);
	if (!new_ptr)
		return (pt ? free(pt), -1 : -1);

	if (s)
		ft_strncat(new_ptr, buffer + i, n - i);
	else
		ft_strncpy(new_ptr, buffer + i, n - i + 1);

	s += n - i;
	i = n;
	pt = new_ptr;

	if (length)
		*length = s;
	*ptr = pt;
	return (s);
}

/**
 * ft_sigintHandler - blocks ctrl-C
 * @sn: the signal number
 *
 * Return: void
 */
void ft_sigintHandler(__attribute__((unused))int sn)
{
	ft_puts("\n");
	ft_puts("$ ");
	ft_putchar(BUF_FLUSH);
}
