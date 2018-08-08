#include "../inc/ft_ls_header.h"

void 	long_output(struct stat buf, char *filename)
{
	print_access(buf.st_mode);
	print_integer(buf.st_nlink, g_options.sizes.link_size);
	print_string(getpwuid(buf.st_uid)->pw_name, g_options.sizes.owner);
	print_string(getgrgid(buf.st_gid)->gr_name, g_options.sizes.group);
	print_integer((int)buf.st_size, g_options.sizes.size_size);
	g_options.u == 1 ?	print_date(buf.st_atimespec.tv_sec) :
						print_date(buf.st_mtimespec.tv_sec);
	ft_putendl(filename);
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
			long_output(buf, path);
		else
			ft_printf("%s\n", path);
	}
	return (1);
}
