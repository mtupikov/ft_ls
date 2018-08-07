#include "../inc/ft_ls_header.h"

void	ft_ls_algorithm(char *path);

void	print_usage()
{
	ft_printf("Usage: ./ft_ls [-artlR] [file ...]\n");
	exit(0);
}

void	error(const char *error)
{
	perror(error);
	exit(1);
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
			g_options.small_r = 1;
		else if (str[i] == 'R')
			g_options.big_r = 1;
		else if (str[i] == 't')
			g_options.t = 1;
		else if (str[i] == 'l')
			g_options.l = 1;
		else
			print_usage();
	return (1);
}

char	*add_valid_path(char *path, char *add)
{
	char *ret;
	char *temp;

	if (ft_strcmp(path, "./"))
	{
		temp = ft_strjoin(path, "/");
		ret = ft_strjoin(temp, add);
		ft_strdel(&temp);
	}
	else
		ret = ft_strjoin(path, add);
	return (ret);
}

int 	check_if_file(char *path)
{
	struct stat buf;

	if (path == (char *)0x1)
		return (1);
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
		return (0);
	if (!g_options.big_r)
	{
		if (g_options.l)
			;// print large info about file
		else
			ft_printf("%s\n", path);
	}
	return (1);
}

void	read_directory(DIR *dir, char *path)
{
	struct dirent	*sd;
	struct stat		buf;
	char			*new_p;

	while ((sd = readdir(dir)) != NULL)
		if (sd->d_name[0] != '.' || g_options.a == 1)
			ft_printf("%s\n", sd->d_name);
	ft_printf("\n");
	closedir(dir);
	if (g_options.big_r == 1)
	{
		dir = opendir(path);
		while ((sd = readdir(dir)) != NULL)
		{
			stat(sd->d_name, &buf);
			if (sd->d_name[0] != '.' && S_ISDIR(buf.st_mode))
			{
				new_p = add_valid_path(path, sd->d_name);
				ft_ls_algorithm(new_p);
				ft_strdel(&new_p);
			}
		}
		closedir(dir);
	}
}

void	ft_ls_algorithm(char *path)
{
	DIR *dir;

	if (check_if_file(path))
		return;
	ft_printf("%s:\n", path);
	dir = opendir(path);
	if (dir == NULL)
		error(path);
	read_directory(dir, path);
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

void	init_default_options()
{
	g_options.a = 0;
	g_options.big_r = 0;
	g_options.l = 0;
	g_options.small_r = 0;
	g_options.t = 0;
}

int main(int argc, char **argv)
{
	struct winsize	term;

	init_default_options();
	ioctl(1, TIOCGWINSZ, &term);
	g_options.win_h = term.ws_row;
	g_options.win_w = term.ws_col;
	handle_arguments(argc, argv);
	return (0);
}