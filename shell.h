#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define WRITE_BUFF 1024
#define READ_BUFF 1024
#define BUFF -1

#define CMD_CHAIN 3
#define CMD_AND 2
#define CMD_OR 1
#define CMD_ 0

#define CNVRT_LOWERCASE 1
#define CNVRT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct list_str - singly linked list
 * @nex: number
 * @str: string
 * @next: points to the next node
 */
typedef struct list_str
{
	int nex;
	char *str;
	struct list_str *next;
} list_dt;

/**
 * struct passdata - contains arguments to pass into a function
 * @stats: returned status of the last command executed
 * @path: path for the current command
 * @environ: modified copy of environ
 * @cmnd_buff: address of pointer
 * @rfd: fd to read line input
 * @c_hist: history line count
 * @env: local copy of environ
 * @linec_f: input line count
 * @ch_env: changed environ
 * @argv: array of strings
 * @argc: argument count
 * @cmd_buft: CMD type
 * @linec: line count
 * @nerr: error code
 * @fname: file name
 * @history: history
 * @arg: arguments
 * @alias: alias
 */
typedef struct passdata
{
	unsigned int linec;
	list_dt *history;
	char **cmnd_buff;
	list_dt *alias;
	char **environ;
	list_dt *env;
	int cmd_buft;
	int linec_f;
	char **argv;
	char *fname;
	int c_hist;
	char *path;
	int ch_env;
	char *arg;
	int stats;
	int nerr;
	int argc;
	int rfd;
} data_dt;

#define DATA_INIT \
{0, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, NULL, 0, 0, 0, 0, 0, 0}

/**
 * struct builtin - builtin string and related function
 * @type: the builtin command type
 * @func: function 
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_dt *);
} bltin;

/* main.c */
int main(int ac, char **av);

/* strings.c */
int str_leng(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *itstarts(const char *, const char *);

/* strings1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);
void itputs(char *);

/* strings2.c */
char *cpy_str(char *dest, char *src, int a);
char *cat_str(char *dest, char *src, int a);
char *str_char(char *str, char c);

/* interactive.c */
int interact(data_dt *info);
int __delim(char c, char *delim);
int __alpha(int c);
int intostr(char *s);

/* checks.c */
int chain_delim(data_dt *data, char *buf, size_t *pntr);
void chain_check(data_dt *data, char *buf, size_t *pntr, size_t x, size_t leng);

/* replace.c */
int replace_alias(data_dt *data);
int replace_str(char **old, char *n);
int replace_vars(data_dt *data);

/* tokenize.c */
char **str_tok(char *str, char*d);
char **tok_strn(char *str, char d);

/* _realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *mem_sets(char *, char, unsigned int);
void _frees(char **);

/* pars.c */
char *fpath(data_dt *, char *, char *);
char *chars_dp(char *, int, int);
int cmnd(data_dt *, char *);

/* free_memory.c */
int mfree(void **);

/* itlists.c */
list_dt *add_node(list_dt **, const char *, int);
list_dt *node_end(list_dt **, const char *, int);
int rmv_node(list_dt **, unsigned int);
size_t list_strs(const list_dt *);
void free_list(list_dt **);

/* itlists1.c */
size_t list_leng(const list_dt *);
char **list_arr(list_dt *);
size_t list_print(const list_dt *);
list_dt *itstarts_node(list_dt *, char *, char );
ssize_t nindex(list_dt *, list_dt *);

/* env.c */
char **_getenv_(data_dt *);
int _setenv_(data_dt *, char *, char *);
int _unsetenv_(data_dt *, char *);

/* errs.c */
void puts_err(char *);
int _putcharerr(char);
int wr_fd(char c, int fd);
int _putsfd(char *str, int fd);

/* errs1.c */
int err_stoi(char *);
void print_err(data_dt *, char *);
int print_dec(int, int);
char *itconverts(long int, int, int);
void rmv_cmnts(char *);

/* environ.c */
int penv(data_dt *);
char *_getenv(data_dt *, const char *);
int psetenv(data_dt *);
int punsetenv(data_dt *);
int penv_list(data_dt *);

/* built_in.c */
int pexit(data_dt *);
int pcd(data_dt *);
int phelp(data_dt *);

/* built_in1.c */
int phistory(data_dt *);
int _unsets_alias_(data_dt *, char *);
int _sets_alias_(data_dt *, char *);
int _print_alias_(list_dt *nd);
int palias(data_dt *);

/* get_data.c */
void set_dt(data_dt *, char **);
void clear_dt(data_dt *);
void free_dt(data_dt *, int);

/* history.c */
char *hist_file(data_dt *data);
int wr_hist(data_dt *data);
int rd_hist(data_dt *data);
int list_hist(data_dt *data, char *buf, int line_count);
int rnum_hist(data_dt *data);

/* get_line.c */
ssize_t inbuf(data_dt *, char **, size_t *);
ssize_t gets_in(data_dt *);
int _getline(data_dt *, char **, size_t *);
void sig_handler(int);

/* hsh.c */
int hsh(data_dt *data, char **av);
int loc_bltin(data_dt *);
void loc_cmd(data_dt *data);
void frk_cmd(data_dt *data);

#endif
