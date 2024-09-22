/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:39:55 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/21 19:27:56 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// handler for execution in pipes
void	ft_execute_commands(t_parse *parse, t_file *file, t_fd **fd)
{
	if (!file)
	{
		ft_execve_or_builtin();
		dup2(parse->in_file, STDIN_FILENO);
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			; // redirect in
		else if (file->type == SMALLER)
			; // redirect out
		else if (file->type == APPEND)
			; // append
		else if (file->type == HERE_DOC)
			ft_heredoc(parse, &file, fd);
		if (file == NULL && parse->next == NULL)
			; // return fd
	}
}

// check whether builtin or not
void	ft_execve_or_builtin(char **str)
{
	int	pid;
	int	type;

	type = ft_builtin_or_not(str);
	if (type != 0) // also control number of token I guess, ask göktuğ
	{
		ft_execute_builtins(str);
		return  ;
	}
	// signal handling
	pid = fork();
	if (pid == 0) // child process
	{
		if (type == 0)
			ft_execve();
		else
		{
			ft_execute_builtins(str);
			exit(1);
		}
	}
}

// check which comman dfunction will be executed
void	ft_check_which_command_execute(t_parse **parse, t_fd **fd)
{
	int	type;

	type = ft_builtin_or_not((*parse)->args[0]);
	// set pipe flag to 0
	if (parse[1])
	{
		// set pipe flag to 1
		ft_handle_pipe(parse, fd);
	}
	else
		ft_execute_commands(*parse, (*parse)->file, fd);
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
		continue ;
	if (type == 0)
	{
		if (ft_is_exited(g_minishell.exit_status))
			g_minishell.exit_status = ft_get_exit_status(g_minishell.exit_status);
		else
			g_minishell.exit_status = 130; // represent the ctrl + c
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrl_c());
}

void	ft_execution(t_parse **parse, t_fd *fd)
{
	ft_check_which_command_execute(parse, &fd);
}
