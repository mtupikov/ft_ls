#include "../inc/ft_ls_header.h"

void	print_usage()
{
	ft_printf("Usage: ./ft_ls [-artlR] [file ...]\n");
	exit(0);
}

void	error(const char *error)
{
	perror(error);
	exit(2);
}

int 	check_ls_flags(char *str)
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
			((g_options.f = 1) && (g_options.a = 1));
		else if (str[i] == 'u')
			g_options.u = 1;
		else
			print_usage();
	return (1);
}

void	handle_arguments(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc > 1 && check_ls_flags(argv[1]))
		i++;
	if (argc - i == 1)
	{
		ft_ls_algorithm("./");
		return;
	}
	check_args_errors(&argv[i + 1]);
	while (argv[++i])
	{
		ft_ls_algorithm(argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf("\n");
	}
}

int main(int argc, char **argv)
{
	init_default_options();
	handle_arguments(argc, argv);
	return (0);
}