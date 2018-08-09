/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:59:23 by mtupikov          #+#    #+#             */
/*   Updated: 2018/08/09 16:59:27 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls_header.h"

void	sort_args(int argc, char **argv)
{
	int		i;
	int		j;
	char	*c_tmp;

	i = -1;
	while (argv[++i])
		argv[i] = ft_strjoin(argv[i], "");
	j = 0;
	while (++j < argc)
	{
		i = 0;
		while (argv[++i])
		{
			if (g_options.small_r * ft_strcmp(argv[i - 1], argv[i]) > 0)
			{
				c_tmp = ft_strjoin(argv[i - 1], "");
				ft_strdel(&argv[i - 1]);
				argv[i - 1] = ft_strjoin(argv[i], "");
				ft_strdel(&argv[i]);
				argv[i] = c_tmp;
			}
		}
	}
}

void	print_usage(void)
{
	ft_printf("Usage: ./ft_ls [-lrRafut] [file ...]\n");
	exit(0);
}

int		check_ls_flags(char *str)
{
	int i;

	if (str[0] != '-')
		return (0);
	i = 0;
	if (ft_strlen(str) == 1)
		print_usage();
	while (str[++i])
		if (str[i] == 'a')
			g_options.a = 1;
		else if (str[i] == 'r')
			g_options.small_r = -1;
		else if (str[i] == 'R')
			g_options.big_r = 1;
		else if (str[i] == 't')
			g_options.t = 1;
		else if (str[i] == 'l')
			g_options.l = 1;
		else if (str[i] == 'f')
			g_options.f = 1;
		else if (str[i] == 'u')
			g_options.u = 1;
		else
			print_usage();
	return (1);
}

void	handle_arguments(int argc, char **argv)
{
	int i;

	i = 1;
	while (1)
		if (argc > 1 && argv[i] && check_ls_flags(argv[i]))
			i++;
		else
			break ;
	if (argc - i == 0)
	{
		ft_ls_algorithm("./");
		return ;
	}
	if (g_options.f)
		g_options.a = 1;
	sort_args(argc, &argv[i]);
	check_args_errors(&argv[i]);
	i--;
	while (argv[++i])
	{
		ft_ls_algorithm(argv[i]);
		if (argv[i + 1] != NULL && argv[i] != (char *)0x1)
			ft_printf("\n");
	}
}

int		main(int argc, char **argv)
{
	init_default_options();
	handle_arguments(argc, argv);
	return (0);
}
