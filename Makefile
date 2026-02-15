# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 03:41:43 by sharaki           #+#    #+#              #
#    Updated: 2025/12/20 11:32:18 by sharaki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell

CC = cc

SRCS = src/main/main.c \
       src/main/process.c \
       src/lexer/lexer.c \
       src/lexer/lexer_error.c \
       src/lexer/lexer_pipe.c \
       src/lexer/lexer_quotes.c \
       src/lexer/lexer_redirection.c \
       src/lexer/lexer_utils.c \
       src/parser/parser.c \
       src/parser/parser_utils.c \
       src/parser/parser_command.c \
       src/parser/parser_redirection.c \
       src/parser/parser_redirection_utils.c \
       src/parser/parser_validation_pipe.c \
       src/parser/parser_cleanup.c \
       src/utility/token.c \
       src/utility/token_list.c \
       src/expander/expander.c \
       src/expander/expander_string.c \
       src/expander/expander_utils.c \
       src/expander/expander_markers.c \
       src/expander/expander_args.c \
       src/executor/apply_redirections.c \
       src/executor/heredoc.c \
       src/executor/heredoc_child.c \
       src/executor/heredoc_utils.c \
       src/executor/executor.c \
       src/executor/executor_error.c \
       src/executor/executor_utils.c \
       src/executor/cmd_check.c \
       src/executor/path_finder.c \
       src/executor/path_utils.c \
       src/executor/pipe.c \
       src/executor/pipe_exec.c \
       src/executor/pipe_utils.c \
       src/executor/pipe_cleanup.c \
       src/signal/signal.c \
       src/builtin/builtin_cd.c \
       src/builtin/builtin_echo.c \
       src/builtin/builtin_env.c \
       src/builtin/builtin_pwd.c \
       src/builtin/builtins.c \
       src/builtin/builtin_unset.c \
       src/builtin/env_utils.c \
       src/builtin/builtin_exit.c \
       src/builtin/exit_utils.c \
       src/builtin/cd_utils.c \
       src/builtin/builtin_export.c \
       src/builtin/export_env.c \
       src/builtin/export_print.c \


CFLAGS = -Wall -Wextra -Werror -I.

LDFLAGS = -lreadline

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re