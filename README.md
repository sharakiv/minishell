# minishell

A simple shell implementation in C, recreating core bash functionality.

## Overview

This project is a simplified bash shell built from scratch as part of the 42 Tokyo curriculum. It handles command execution, pipes, redirections, and environment variables using low-level Unix system calls.

## Features

### Command Execution
- Execute commands using PATH resolution or absolute/relative paths
- Command history with readline

### Redirections
| Operator | Description |
|----------|-------------|
| `<` | Redirect input |
| `>` | Redirect output |
| `>>` | Redirect output (append mode) |
| `<<` | Heredoc |

### Pipes
- Pipeline commands with `|`
- Connect stdout of one command to stdin of the next

### Environment Variables
- Expand variables with `$VAR`
- Access exit status with `$?`

### Quoting
- Single quotes `'` - prevent interpretation of metacharacters
- Double quotes `"` - allow `$` expansion

### Built-in Commands
| Command | Description |
|---------|-------------|
| `echo` | Print text (supports `-n` flag) |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Print environment |
| `exit` | Exit shell |

### Signal Handling
| Signal | Behavior |
|--------|----------|
| `ctrl-C` | Display new prompt |
| `ctrl-D` | Exit shell |
| `ctrl-\` | Ignored |

## Tech Stack

- **Language:** C
- **System Calls:** fork, execve, pipe, dup2, waitpid
- **Libraries:** readline, libft

## Build
```bash
make
./minishell
```

## Author

Developed at 42 Tokyo