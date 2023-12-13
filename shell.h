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

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

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
	int cmd_buff_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

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
size_t ft_get_node_index(list_t *, list_t *);
char *ft_get_history_file(info_t *info);
int ft_write_history(info_t *info);
int ft_read_history(info_t *info);
int ft_build_history_list(info_t *info, char *buf, int linecount);
int ft_renumber_history(info_t *info);
int ft_is_cmd(info_t *info, char *path);
char *ft_dup_chars(char *pathstr, int start, int stop);
char *ft_find_path(info_t *info, char *pathstr, char *cmd);
int ft_hsh(info_t *info, char **argv);
int ft_find_builtin(info_t *info);
void ft_find_cmd(info_t *info);
void ft_fork_cmd(info_t *info);
list_t *ft_add_node(list_t **head, const char *str, int num);
size_t ft_print_list_str(const list_t *h);
void ft_free_list(list_t **head_ptr);
size_t ft_get_node_index(list_t *head, list_t *node);
size_t ft_list_len(const list_t *h);
char **ft_list_to_strings(list_t *head);
list_t *ft_node_starts_with(list_t *node, char *prefix, char c);
list_t *ft_add_node_end(list_t **head, const char *str, int num);
size_t ft_print_list_str(const list_t *h);
int ft_delete_node_at_index(list_t **head, unsigned int index);
ssize_t ft_input_buf(info_t *info, char **buffer, size_t *len);
ssize_t ft_get_input(info_t *info);
ssize_t ft_read_buf(info_t *info, char *buffer, size_t *size);
int ft_getline(info_t *info, char **ptr, size_t *length);
void ft_sigintHandler(__attribute__((unused))int sn);
char **ft_get_environ(info_t *info);
int ft_unsetenv(info_t *info, char *c);
int ft_setenv(info_t *info, char *v, char *val);
char **ft_get_environ(info_t *info);
int ft_unsetenv(info_t *info, char *v);
int ft_setenv(info_t *info, char *v, char *val);
int ft_is_chain(info_t *info, char *buffer, size_t *ptr);
void ft_check_chain(info_t *info, char *buffer, size_t *ptr, size_t n, size_t len);
int replace_alias(info_t *info);
int ft_replace_vars(info_t *info);
int ft_replace_string(char **prev, char *new);
int ft_myhistory(info_t *info);
int ft_unset_alias(info_t *info, char *str);
int ft_set_alias(info_t *info, char *str);
int ft_print_alias(list_t *node);
int ft_myalias(info_t *info);






#endif
