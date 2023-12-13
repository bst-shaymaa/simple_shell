#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

void ft_eputs(char *);
int ft_eputchar(char);
int ft_putfd(char c, int fd);
int ft_putsfd(char *str, int fd);
int ft_strlen(char *);
int ft_strcmp(char *, char *);
char *ft_starts_with(const char *, const char *);
char *ft_strcat(char *, char *);
char *ft_strcpy(char *, char *);
char *ft_strdup(const char *);
void ft_puts(char *);
int ft_putchar(char);
char *ft_strncpy(char *, char *, int);
char *ft_strncat(char *, char *, int);
char *ft_strchr(char *, char);
char **ft_strtow(char *, char *);
char **ft_strtow2(char *, char);
char *ft_memset(char *, char, unsigned int);
void ft_ffree(char **);
void *ft_realloc(void *, unsigned int, unsigned int);
int ft_bfree(void **);
int ft_interactive(info_t *);
int ft_is_delim(char, char *);
int ft_isalpha(int);
int ft_atoi(char *);
int ft_erratoi(char *);
void ft_print_error(info_t *, char *);
int ft_print_d(int, int);
char *ft_convert_number(long int, int, int);
void ft_remove_comments(char *);
list_t *ft_add_node(list_t **, const char *, int);
list_t *ft_add_node_end(list_t **, const char *, int);
size_t ft_print_list_str(const list_t *);
int ft_delete_node_at_index(list_t **, unsigned int);
void ft_free_list(list_t **);
size_t ft_list_len(const list_t *);
char **ft_list_to_strings(list_t *);
size_t ft_print_list(const list_t *);
list_t *ft_node_starts_with(list_t *, char *, char);
ssize_t ft_get_node_index(list_t *, list_t *);

#endif
