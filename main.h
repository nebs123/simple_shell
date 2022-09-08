#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#define OK 0
#define ACCESS_DENIED -1
extern char **environ;
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void copy_arr(char **origin, char **dest, unsigned int len);
char **str_split(char *str);
char **str_split2(char *str);
char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
char *_strstr(char *haystack, const char *needle);
int _strcmp(const char *s1, const  char *s2);
char **str_delim(char *str, char delim);
char *_getenv(const char *name);
int _strlen(const char *s);
char *get_path(char *file, int *status);
int command(char *path, char **split, char **env);
void free_mem(char **buf, size_t *num, char ***split, char **path);
int perr(char *prog, int count, char *cmd, int stat);
int builtin(char **args, char *buf, char *path, int exit_st);
void printenv(void);
char **copier(char **arr, unsigned int *arr_size, unsigned int increment,
	      unsigned int next);
char *check_file(char *file, struct stat *info, int *status);
void write_int(int num);
int _putchar(char c);
#endif
