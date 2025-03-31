/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** minishell2
*/

#ifndef MINISHELL2_H_
    #define MINISHELL2_H_

    #include <stdbool.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <errno.h>

    #include "parser.h"

    #define EXIT 1
    #define ERROR 84
    #define BUFFER_SIZE 1024

typedef struct history_entry_s {
    char *command;
    int id;
    struct history_entry_s *next;
    struct history_entry_s *prev;
} history_entry_t;

typedef struct history_s {
    history_entry_t *head;
    history_entry_t *tail;
    int count;
} history_t;

typedef struct env_value_s {
    char *env;
    char *value;
} env_value_t;

typedef struct alias_s {
    char *name;
    char *value;
} alias_t;

typedef struct special_vars_s {
    char *term;
    char *cwd;
    char *precmd;
    char *cwdcmd;
    size_t ignoreeof;
    size_t eofcount;
} special_vars_t;

typedef struct shell_s {
    char *input;
    char **env;
    int job_count;
    unsigned int exit_value;
    bool in_logic_context;
    bool in_group_context;
    history_t *history;
    bool history_expansion_failed;
    history_entry_t *current_history_entry;
    env_value_t **env_private;
    env_value_t **local_vars;
    alias_t **aliases;
    special_vars_t *special_vars;
} shell_t;

typedef struct builtins_s {
    char *name;
    void (*handler)(shell_t *shell, node_t *node);
} builtins_t;

typedef void (*node_handler_t)(shell_t *shell, node_t *node);

typedef struct input_state_s {
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    int cursor_pos;
    char seq[3];
    shell_t *shell;
    bool history_panel_visible;
} input_state_t;

// Core

void my_shell(shell_t *shell);
void my_tty_shell(shell_t *shell);
void handle_cmd_line(shell_t *shell);
void my_exec(shell_t *shell, node_t *node);
void start_shell(shell_t *shell, char **env);
env_value_t **get_env_values(void);

// Commands

void my_cd(shell_t *shell, node_t *node);
void my_setenv(shell_t *shell, node_t *node);
void my_unsetenv(shell_t *shell, node_t *node);
void my_env(shell_t *shell, node_t *node);
void my_exit(shell_t *shell, node_t *node);
void my_history(shell_t *shell, node_t *node);
void my_alias(shell_t *shell, node_t *node);
void my_unset(shell_t *shell, node_t *node);
void add_alias_with_name_and_value(shell_t *shell,
    char *name, char *value);

// AST

void execute_ast(shell_t *shell, node_t *node);
void execute_sequence(shell_t *shell, node_t *node);
void execute_pipe(shell_t *shell, node_t *node);
void execute_redirection(shell_t *shell, node_t *node);
void execute_command(shell_t *shell, node_t *node);
void execute_background(shell_t *shell, node_t *node);
void execute_or(shell_t *shell, node_t *node);
void execute_and(shell_t *shell, node_t *node);
void execute_group(shell_t *shell, node_t *node);
void execute_if(shell_t *shell, node_t *node);
void execute_while(shell_t *shell, node_t *node);

// Utils

bool read_input(shell_t *shell);
void read_tty_input(shell_t *shell);
void setup_terminal(void);
void restore_terminal(void);
void handle_key_input(shell_t *shell);
void free_shell(shell_t *shell);
char *my_getenv(char **env, char *name);
void change_env_value(shell_t *shell, char *name, char *value);
void add_env_value(shell_t *shell, char *name, char *value);
void remove_env_value(shell_t *shell, char *name);
int my_arraylen(char **array);
char *my_str_replace(char *str, const char *old, const char *new);
void expand_variables(shell_t *shell, node_t *node);
void expand_backticks(node_t *node);
void expand_aliases(shell_t *shell, node_t *node);
void expand_globbing(node_t *node);
bool evaluate_condition(shell_t *shell, node_t *condition);

// Input handling

void print_prompt(input_state_t *state);
int get_prompt_len(char *user, char *home, char *path);
void initialize_input_state(input_state_t *state, shell_t *shell);

// History

history_t *create_history(void);
void destroy_history(history_t *history);
void add_history_entry(history_t *history, const char *command);
history_entry_t *get_history_entry(history_t *history, int id);
void print_history(history_t *history, int num_entries);
void expand_history(shell_t *shell);

// Local variables

void my_vars(shell_t *shell, node_t *node);
void set_local_var(shell_t *shell, char *name, char *value);
void unset_local_var(shell_t *shell, char *name);
char *get_local_var(shell_t *shell, char *name);
bool is_cmd_var_assignement(node_t *cmd_node);

// Special variables

void set_special_var(shell_t *shell, const char *name, const char *value);
bool is_special_var(const char *name);
void update_cwd(shell_t *shell);
void execute_precmd(shell_t *shell);

#endif /* !MINISHELL2_H_ */
