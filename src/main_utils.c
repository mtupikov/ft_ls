#include "../inc/ft_ls_header.h"

void	print_access_util(mode_t mode)
{
	if ((S_ISDIR(mode)) || (S_ISLNK(mode)))
	{
		if ((S_ISLNK(mode)))
			ft_putchar('l');
		else
			ft_putchar('d');
	}
}

void	init_default_sizes()
{
	g_options.sizes.link_size = 0;
	g_options.sizes.owner = 0;
	g_options.sizes.group = 0;
	g_options.sizes.size_size = 0;
	g_options.sizes.minor_size = 0;
	g_options.sizes.major_size = 0;
	g_options.sizes.total = 0;
}

void	init_default_options()
{
	g_options.a = 0;
	g_options.big_r = 0;
	g_options.l = 0;
	g_options.small_r = 1;
	g_options.t = 0;
	g_options.f = 0;
	g_options.u = 0;
	g_options.argc = 0;
	init_default_sizes();
}

int 	num_len(int num)
{
	int ret;

	ret = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		ret++;
		num /= 10;
	}
	return (ret);
}

void	check_args_errors(char **args)
{
	int			i;
	struct stat	buf;

	i = -1;
	while(args[++i])
		if (stat(args[i], &buf) != 0)
		{
			perror(args[i]);
			args[i] = (char *)0x1;
		}
		else
			g_options.argc++;
}

