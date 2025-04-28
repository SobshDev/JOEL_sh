/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-louis.bagnol
** File description:
** init_shell
*/

#include "minishell2.h"
#include "my.h"

static void init_base_values(shell_t *shell)
{
    shell->job_count = 0;
    shell->exit_value = 0;
    shell->in_logic_context = false;
    shell->in_group_context = false;
    shell->history = create_history();
    shell->history_expansion_failed = false;
    shell->current_history_entry = NULL;
    shell->env_private = get_env_values();
}

static void copy_env(shell_t *shell, char **env)
{
    char *host = my_getenv(env, "SESSION_MANAGER");
    int env_len = my_arraylen(env);

    shell->env = malloc(sizeof(char *) * (env_len + 1));
    for (int i = 0; i < env_len; i++)
        shell->env[i] = my_strdup(env[i]);
    shell->env[env_len] = NULL;
    shell->input = NULL;
    if (host != NULL) {
        host = host + my_strlen("local/");
        host = strtok(host, ":");
        add_env_value(shell, "HOST", host);
    }
}

static void init_aliases(shell_t *shell)
{
    char *aliases[][2] = {
        {"l", "ls -CF"}, {"ll", "ls -l"}, {"la", "ls -a"},
        {"..", "cd .."}, {"...", "cd ../.."}, {"q", "exit"},
        {"g", "git"}, {"gcm", "git commit -m"}, {"gs", "git status"},
        {"gp", "git push"}, {"gl", "git pull"}, {"c", "clear"},
        {"ls", "ls --color=tty"}
    };

    shell->aliases = malloc(sizeof(alias_t *) * 1);
    if (!shell->aliases) {
        perror("malloc");
        exit(84);
    }
    shell->aliases[0] = NULL;
    for (size_t i = 0; i < sizeof(aliases) / sizeof(aliases[0]); i++)
        add_alias_with_name_and_value(shell, aliases[i][0], aliases[i][1]);
}

static void init_local_vars(shell_t *shell)
{
    shell->local_vars = malloc(sizeof(env_value_t *));
    if (!shell->local_vars) {
        perror("malloc");
        exit(84);
    }
    shell->local_vars[0] = NULL;
}

static void init_special_vars(shell_t *shell)
{
    char *term = my_getenv(shell->env, "TERM");

    shell->special_vars = malloc(sizeof(special_vars_t));
    if (!shell->special_vars) {
        perror("malloc");
        exit(84);
    }
    shell->special_vars->term = term ? my_strdup(term) : NULL;
    shell->special_vars->cwd = getcwd(NULL, 0);
    shell->special_vars->precmd = NULL;
    shell->special_vars->cwdcmd = NULL;
    shell->special_vars->ignoreeof = 0;
    shell->special_vars->eofcount = 0;
}

void start_shell(shell_t *shell, char **env)
{
    copy_env(shell, env);
    init_base_values(shell);
    init_aliases(shell);
    init_local_vars(shell);
    init_special_vars(shell);
}
