/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:27:07 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/21 19:40:40 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global değişken
t_minishell	g_minishell;

int	check_if_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_parse	**parse;
	t_fd	*fd;

	(void)argc;
	(void)argv;
	ft_init(envp);
	while (1) 
	{
		input = readline("minishell$ ");
		if (check_if_empty(input) == 1)
			continue ;
		adjsut_all(input, parse, fd);
		add_history(input);
	}
	return 0;
}
