#include "shell.h"

/**
 * ft_strlen - returns the length of a string
 * @str: the string
 * Return: length of string
 */
int ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}
/**
 * ft_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *ft_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (p);
}

/**
 * ft_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *ft_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * ft_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *ft_strdup(const char *str)
{
	int length = 0;
	char *ptr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	for (length++; length--;)
		ptr[length] = *--str;
	return (ptr);
}
