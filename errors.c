#include "shell.h"

/**
 *ft_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void ft_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		ft_eputchar(str[i]);
		i++;
	}
}

/**
 * ft_eputchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int ft_eputchar(char ch)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * ft_putfd - writes the character c to given fd
 * @ch: The character to print
 * @flds: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int ft_putfd(char ch, int flds)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(flds, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * ft_putsfd - prints an input string
 * @str: the string to be printed
 * @fld: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int ft_putsfd(char *str, int fld)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += ft_putfd(*str++, fld);
	}
	return (i);
}
