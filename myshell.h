#ifndef SHELL_H
#define SHELL_H


#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>


/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2



#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@argg: a string generated from getline containing arguements
 *@arggv: an array of strings generated from arg
 *@paath: a string path for the current command
 *@arc: the argument count
 *@line_cnt: the error count
 *@err_numb: the error code for exit()s
 *@linecnt_flag: if on count this line of input
 *@fnm: the program filename
 *@enviro: linked list local copy of environ
 *@enviroon: custom modified copy of environ from LL env
 *@his: the history node
 *@alas: the alias node
 *@env_chng: on if environ was changed
 *@stats: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmd_buff_typ: CMD_type ||, &&, ;
 *@redfd: the fd from which to read line input
 *@histcnt: the history line number count
 */
typedef struct passinfo
{
	char *argg;
	char **arggv;
	char *paath;
	int arc;
	unsigned int line_cnt;
	int err_numb;
	int linecnt_flag;
	char *fnm;
	struct list_t *enviro;
	struct list_t *his;
	struct list_t *alas;
	char **enviroon;
	int env_chng;
	int stats;

	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_typ; /* CMD_type ||, &&, ; */
	int redfd;
	int histcnt;
} info_t;

/**
 * struct liststr - singly linked list
 * @numb: the number field
 * @string: a string
 * @nxt: points to the next node
 */
typedef struct liststr
{
	int numb;
	char *string;
	struct liststr *nxt;
} list_t;



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


/* hsh.c */
int hshhh(info_t *, char **);
int fn_bultin(info_t *);
void fn_cmd(info_t *);
void foork_cmd(info_t *);



/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _ept(char *);
int _eptchr(char);
int _ptfd(char c, int fd);
int _ptsfd(char *str, int fd);

/* path.c */
int a_cmd(info_t *, char *);
char *dou_chars(char *, int, int);
char *fn_paath(info_t *, char *, char *);

/* string_functions.c */
int _slen(char *);
int _strcom(char *, char *);
char *start_with(const char *, const char *);
char *_scat(char *, char *);

/* string_functions2.c */
char *_scpy(char *, char *);
char *_strup(const char *);
void _puuts(char *);
int _ptchr(char);

/* string_functions4.c */
char **strtoow(char *, char *);
char **strtoow2(char *, char);

/* memory_functions */
char *_memst(char *, char, unsigned int);
void ffr(char **);
void *_reloc(void *, unsigned int, unsigned int);

/* string_functions3.c */
char *_sncpy(char *, char *, int);
char *_sncat(char *, char *, int);
char *_strchar(char *, char);

/* memory_functions2.c */
int bfr(void **);

/* more_functions.c */
int inactive(info_t *);
int a_delim(char, char *);
int _analpha(int);
int _ati(char *);

/* builtin_emulators.c */
int _ourexit(info_t *);
int _ourcd(info_t *);
int _ourhelp(info_t *);

/* builtin_emulators2.c */
int _ourhistory(info_t *);
int _ouralas(info_t *);

/* getline.c module */
ssize_t get_input(info_t *);
int _gline(info_t *, char **, size_t *);
void signhandler(int);

/* more_functions2.c */
int _erati(char *);
void print_err(info_t *, char *);
int prnt_d(int, int);
char *conv_number(long int, int, int);
void rm_comments(char *);

/* info.c module */
void clear_info(info_t *);
void s_info(info_t *, char **);
void fr_info(info_t *, int);

/* env2.c module */
char **get_enviro(info_t *);
int _unsenv(info_t *, char *);
int _senv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_his_file(info_t *info);
int write_his(info_t *info);
int read_his(info_t *info);
int build_his_lst(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* liststr.c module */
list_t *ad_nod(list_t **, const char *, int);
list_t *ad_nod_end(list_t **, const char *, int);
size_t prnt_lst_str(const list_t *);
int del_nod_at_inx(list_t **, unsigned int);
void fr_list(list_t **);

/* env.c module */
char *_genv(info_t *, const char *);
int _oenv(info_t *);
int _osetenv(info_t *);
int _ounsetenv(info_t *);
int pop_env_list(info_t *);

/* liststr2.c module */
size_t list_ln(const list_t *);
char **lst_to_str(list_t *);
size_t prnt_lst(const list_t *);
list_t *nod_start_with(list_t *, char *, char);
ssize_t get_nod_inx(list_t *, list_t *);

/* chain.c */
int a_chain(info_t *, char *, size_t *);
void chk_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_string(char **, char *);

#endif
