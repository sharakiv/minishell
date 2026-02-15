/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:14:22 by kteranis          #+#    #+#             */
/*   Updated: 2025/12/06 06:01:46 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static char	*get_env_var(char *name, char **envp);
static int	cd_error(char *arg, char *msg);
static char	*get_cd_target(t_cmd *cmd, t_shell *shell, int *error);
static int	update_pwd_vars(char *old_pwd, t_shell *shell);

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target;
	char	*old_pwd;
	int		error;

	target = get_cd_target(cmd, shell, &error);
	if (error)
		return (1);
	if (!target || target[0] == '\0')
		return (0);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(target);
		return (1);
	}
	update_pwd_vars(old_pwd, shell);
	free(old_pwd);
	return (0);
}

static char	*get_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	cd_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

static char	*get_cd_target(t_cmd *cmd, t_shell *shell, int *error)
{
	char	*home;

	*error = 0;
	if (cmd->argc == 1)
	{
		home = get_env_var("HOME", shell->envp);
		if (!home)
		{
			cd_error(NULL, "HOME not set");
			*error = 1;
			return (NULL);
		}
		return (home);
	}
	return (cmd->args[1]);
}

static int	update_pwd_vars(char *old_pwd, t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	set_env_var("OLDPWD", old_pwd, shell);
	set_env_var("PWD", new_pwd, shell);
	free(new_pwd);
	return (0);
}
