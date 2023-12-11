#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@b: the byte to fill *str with
 *@n: the amount of bytes to be filled
 *Return: (str) a pointer to the memory area str
 */
char *_memset(char *str, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = b;
	return (str);
}

/**
 * ffree - frees a string of strings
 * @p: string of strings
 */
void ffree(char **p)
{
	char **a = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
