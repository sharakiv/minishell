/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:41:57 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 15:56:01 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
# define BUFFER_SIZE 1024
# ifndef MINISHELL_TOKEN_MAX
#  define MINISHELL_TOKEN_MAX 1024
# endif

extern volatile sig_atomic_t	g_signal_number;

typedef enum e_token_status
{
	STATE_NORMAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE
}								t_token_status;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}								t_quote_type;

typedef struct s_lexer_context
{
	char						*input;
	t_token_status				state;
	char						word_buffer[MINISHELL_TOKEN_MAX];
	int							buffer_index;
	char						*original_input;
	int							error_shown;
	t_quote_type				current_quote_type;
}								t_lexer_context;

typedef enum e_token_type
{
	WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}								t_token_type;

typedef struct s_token
{
	char						*content;
	t_token_type				type;
	t_quote_type				quote_type;
	struct s_token				*next;
}								t_token;

typedef struct s_redirect
{
	t_token_type				type;
	char						*file;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_heredoc
{
	char						*delimiter;
	char						*content;
	int							expand_var;
	struct s_heredoc			*next;
}								t_heredoc;

typedef struct s_cmd
{
	char						**args;
	int							argc;
	t_quote_type				*quote_types;
	t_redirect					*redirects;
	t_heredoc					*heredocs;
	int							heredoc_fd;
	int							in_pipeline;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_shell
{
	char						**envp;
	int							exit_status;
	int							should_exit;
	struct s_token				*tokens;
	struct s_cmd				*cmd;
}								t_shell;

typedef struct s_pipe_ctx
{
	int							**pipes;
	int							pipe_count;
	t_shell						*shell;
}								t_pipe_ctx;

int								process_input(char *input, t_shell *shell);
char							**get_envp(char **envp);
int								count_envp(char **envp);
void							free_envp(char **envp);

void							write_syntax_error(char *token);
void							write_syntax_error_with_input(char *token,
									char *original_input);
void							tokenize_pipe(t_lexer_context *ctx,
									t_token **tokens);
void							check_single_quote_state(t_lexer_context *ctx,
									char current_char);
void							check_double_quote_state(t_lexer_context *ctx,
									char current_char);
int								has_unclosed_quotes(t_lexer_context *ctx);
void							print_quotes_error(t_lexer_context *ctx);
void							tokenize_redirect_out(t_lexer_context *ctx,
									t_token **tokens);
void							tokenize_redirect_in(t_lexer_context *ctx,
									t_token **tokens);
int								is_ifs_char(char c);
void							free_tokens(t_token *tokens);
void							free_token_list(t_token *tokens);

t_token							*create_token(t_token_type type, char *content);
void							add_token_to_list(t_token **head,
									t_token *new_token);
int								flush_word_buffer(t_lexer_context *ctx,
									t_token **tokens);
void							add_char_to_buffer(t_lexer_context *ctx,
									char c);
void							init_lexer_context(t_lexer_context *ctx,
									char *input);
void							lexer(char *input, t_token **tokens);

t_token							*construct_token(enum e_token_type type,
									char *content);
void							delete_token(t_token *token);

int								is_ifs_char(char c);

t_token							*find_command_end(t_token *start);
t_token							*get_next_command_start(t_token *cmd_end);
int								is_redirect_token(t_token_type type);
int								is_operator_token(t_token_type type);

int								validate_syntax(t_token *tokens);
int								check_pipe_syntax(t_token *tokens);
int								check_redirect_syntax(t_token *tokens);

// parser_redirection_utils
t_redirect						*create_redirect(t_token_type type, char *file);
void							add_redirect_to_list(t_redirect **head,
									t_redirect *new_redirect);
int								handle_heredoc(t_cmd *cmd, t_token **tok);
t_heredoc						*create_heredoc(char *delimiter,
									int expand_var);
void							add_heredoc_to_list(t_heredoc **head,
									t_heredoc *new_heredoc);
void							cleanup_child(t_shell *shell);

t_cmd							*parse_single_command(t_token *start,
									t_token *end);
t_cmd							*create_cmd(void);
t_cmd							*cleanup_cmd(t_cmd *cmd);

void							setup_signal_handlers(void);
void							setup_signal_heredoc(void);
void							setup_signal_heredoc_child(void);
void							handle_sigint(int sig);
void							handle_sigquit_ignore(int sig);
void							handle_sigint_ignore(int sig);

char							*get_var_name(char *str, int start);
char							*get_env_value(char *var_name, char **envp);
char							*expand_variable(char *str, int pos,
									char **envp, int exit_status);
char							*expand_string(char *str, char **envp,
									int exit_status);
void							expand_cmd_list(t_cmd *cmd, char **envp,
									int exit_status);
char							*remove_char_at(char *str, int pos);
char							*remove_markers(char *str);
int								*save_quote_markers(char **args, int argc);
void							remove_empty_unquoted_args(t_cmd *cmd,
									int *had_quotes);

int								apply_redirections(t_cmd *cmd);

int								is_same_string(const char *s1, const char *s2);
char							*expand_heredoc_line(char *input,
									int expand_var, t_shell *shell);
void							write_heredoc_line(int fd, char *line);
int								read_heredoc(t_heredoc *heredoc,
									t_shell *shell);
int								read_all_heredocs(t_cmd *cmd, t_shell *shell);
int								read_pipeline_heredocs(t_cmd *cmd,
									t_shell *shell);
void							close_pipeline_heredocs(t_cmd *cmd);

// executor.c
int								executor(t_cmd *cmd, t_shell *shell);
int								execute_single_command(t_cmd *cmd,
									t_shell *shell);
int								execute_pipeline(t_cmd *cmd, t_shell *shell);
int								handle_pipe_error(t_cmd *cmd, t_pipe_ctx *ctx);
int								finish_pipeline(t_pipe_ctx *ctx, pid_t *pids,
									t_cmd *cmd);
void							close_all_pipes(int **pipes, int pipe_count);
void							cleanup_pipes_and_pids(int **pipes, pid_t *pids,
									int pipe_count);
int								wait_all_children(pid_t *pids, int total_cmds);
void							free_commands(t_cmd *commands);

// executor_utils.c
int								get_exit_status(int status);
int								execute_builtin_with_redirect(t_cmd *cmd,
									t_shell *shell);
void							restore_std_fds(int saved_stdin,
									int saved_stdout);
void							execute_external_command(t_cmd *cmd,
									t_shell *shell);
/// executor_error.c
void							child_exit(t_shell *shell, int code);
void							check_empty_command(t_cmd *cmd, t_shell *shell);
void							handle_path_error(char *cmd, t_shell *shell);
void							print_cmd_not_found(char *cmd, t_shell *shell);

// cmd_check.c
int								check_path_error(char *cmd);
void							print_not_found_error(char *cmd);
char							*handle_direct_path(char *cmd);

t_cmd							*parse_pipeline(t_token *tokens);
t_cmd							*parse_single_command(t_token *start,
									t_token *end);
void							free_cmd_list(t_cmd *cmd);

int								count_pipe(t_cmd *cmd);
int								count_commands(t_cmd *cmd);
void							setup_input_redirection(char *input_file);
void							setup_output_redirection(char *output_file);

void							setup_child_pipes(int **pipes, int pipe_count,
									int cmd_index);
void							cleanup_pipes_malloc_error(int **pipes,
									int count);
void							cleanup_pipes_pipe_error(int **pipes,
									int count);
void							execute_child_command(t_cmd *current,
									t_shell *shell);
int								**create_pipes(int pipe_count);
pid_t							*fork_commands(t_cmd *cmd, t_pipe_ctx *ctx);

int								is_builtin(t_cmd *cmd);

char							*find_command_path(char *cmd, char **envp);
char							**split_path(const char *path_env);

int								count_paths(const char *path_env);
char							*extract_path(const char *path_env, int *index);
char							*build_full_path(const char *dir,
									const char *cmd);
void							free_path_array(char **paths);

int								validate_input(char *s);

void							setup_signal_handlers(void);
void							setup_signal_ignore(void);
void							setup_signal_default(void);

// builtin
int								execute_builtin(t_cmd *cmd, t_shell *shell);
int								builtin_echo(t_cmd *cmd);
int								builtin_cd(t_cmd *cmd, t_shell *shell);
int								builtin_pwd(void);
int								builtin_export(t_cmd *cmd, t_shell *shell);
int								builtin_unset(t_cmd *cmd, t_shell *shell);
int								builtin_env(t_cmd *cmd, t_shell *shell);
int								builtin_exit(t_cmd *cmd, t_shell *shell);

int								validate_export_name(char *str);
int								update_env_var(char *arg, char **envp);
int								add_env_var(char *arg, t_shell *shell);
int								set_env_var(char *name, char *value,
									t_shell *shell);

#endif