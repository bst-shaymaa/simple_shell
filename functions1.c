#include "shell.h"
/**
 * ft_is_delim - checks if character is a delimeter
 * @ch: the char to check
 * @dlm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int ft_is_delim(char ch, char *dlm)
{
	while (*dlm)
		if (*dlm++ == ch)
			return (1);
	return (0);
}

/**
 *ft_isalpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int ft_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *ft_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int ft_atoi(char *str)
{
	int i, sign = 1, flags = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flags != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * ft_erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int ft_erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
