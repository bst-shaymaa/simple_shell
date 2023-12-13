#include "shell.h"

/**
 * ft_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int ft_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * ft_print_error - prints an error message
 * @info: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void ft_print_error(info_t *info, char *errstr)
{
	ft_eputs(info->fname);
	ft_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	ft_eputs(": ");
	ft_eputs(info->argv[0]);
	ft_eputs(": ");
	ft_eputs(errstr);
}

/**
 * ft_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fld: the filedescriptor to be writting in
 *
 * Return: number of characters printed
 */
int ft_print_d(int input, int fld)
{
	int (*ft_putchar)(char) = ft_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fld == STDERR_FILENO)
		ft_putchar = ft_eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		ft_putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			ft_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	ft_putchar('0' + current);
	count++;

	return (count);
}

/**
 * ft_convert_number - converter function, a clone of itoa
 * @n: number
 * @bs: base
 * @flags: argument flags
 *
 * Return: string
 */
char *ft_convert_number(long int n, int bs, int flags)
{
	static char *array;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long number = n;

	if (!(flags & CONVERT_UNSIGNED) && n < 0)
	{
		number = -n;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bs];
		number /= bs;
	} while (number != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * ft_remove_comments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void ft_remove_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
