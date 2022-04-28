/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/04/26 16:27:13 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static void	ft_print_title(void)
{
	ft_putstr_fd("\n\033[0;92m::::     :::: ::::::::::: ::::    :::", 1);
	ft_putstr_fd(" ::::::::::: ::::::::  :::    ::: :::::::::: ::: ", 1);
	ft_putstr_fd("       :::             :::             \n", 1);
	ft_putstr_fd("+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:    ", 1);
	ft_putstr_fd(":+:    :+: :+:    :+: :+:        :+:        :+:  ", 1);
	ft_putstr_fd("            :+:            \n", 1);
	ft_putstr_fd("+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    ", 1);
	ft_putstr_fd("+:+        +:+    +:+ +:+        +:+        +:+  ", 1);
	ft_putstr_fd("             +:+           \n", 1);
	ft_putstr_fd("+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    ", 1);
	ft_putstr_fd("+#++:++#++ +#++:++#++ +#++:++#   +#+        +#+  ", 1);
	ft_putstr_fd("              +#+          \n", 1);
	ft_putstr_fd("+#+       +#+     +#+     +#+  +#+#+#     +#+    ", 1);
	ft_putstr_fd("       +#+ +#+    +#+ +#+        +#+        +#+  ", 1);
	ft_putstr_fd("	       +#+            \n", 1);
	ft_putstr_fd("#+#       #+#     #+#     #+#   #+#+#     #+#    ", 1);
	ft_putstr_fd("#+#    #+# #+#    #+# #+#        #+#        #+#  ", 1);
	ft_putstr_fd("            #+#            \n", 1);
	ft_putstr_fd("###       ### ########### ###    #### ###########", 1);
	ft_putstr_fd(" ########  ###    ### ########## ########## #####", 1);
	ft_putstr_fd("#####      ###    ##########\033[0;m\n\n", 1);
}

static void	prompt(t_data *data)
{
	while (1)
	{
		data->line = readline(RL_PROMPT);
		if (data->line)
		{
			if (*data->line)
				add_history(data->line);
			data->token_list = lexer(data->line);
			data->line = NULL;
			if (data->token_list != NULL)
			{
				analyzer(data);
				if (data->token_list != NULL)
					executor(data->export, data);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			free_exit(data, EXIT_SUCCESS);
		}
	}
}

static void	launch_ms(t_data *data, char **av)
{
	while (av != NULL && *av != NULL)
	{
		data->line = ft_strdup(*av);
		if (data->line)
		{
			data->token_list = lexer(data->line);
			data->line = NULL;
			if (data->token_list != NULL)
			{
				analyzer(data);
				if (data->token_list != NULL)
					executor(data->export, data);
			}
		}
		else
		{
			ft_putstr_fd("Bad input\n", 2);
			free_exit(data, EXIT_SUCCESS);
		}
		++av;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	set_signal(DEFAULT);
	if (ac == 1)
	{
		data_init(&data, envp);
		ft_print_title();
		prompt(&data);
	}
	else if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		data_init(&data, envp);
		launch_ms(&data, av + 2);
		free_exit(&data, g_status);
	}
	else
	{
		printf("\e[1;37mUsage:\e[0m %s runs without any argument,", av[0]);
		printf(" or in testing mode with -c flag as first argument.\n");
	}
	return (0);
}
