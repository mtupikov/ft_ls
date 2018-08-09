#include "../inc/ft_ls_header.h"

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

int 	count_elements_in_dir(DIR *dir)
{
	int	ret;

	ret = 0;
	while (readdir(dir) != NULL)
		ret++;
	closedir(dir);
	return (ret);
}

void 	check_sizes(struct stat	buf)
{
	if (num_len(buf.st_nlink) > g_options.sizes.link_size)
		g_options.sizes.link_size = num_len(buf.st_nlink);
	if (getgrgid(buf.st_gid) &&
		(int)ft_strlen(getgrgid(buf.st_gid)->gr_name) > g_options.sizes.group)
		g_options.sizes.group = (int)ft_strlen(getgrgid(buf.st_gid)->gr_name);
	if (getpwuid(buf.st_uid) &&
		(int)ft_strlen(getpwuid(buf.st_uid)->pw_name) > g_options.sizes.owner)
		g_options.sizes.owner = (int)ft_strlen(getpwuid(buf.st_uid)->pw_name);
	if (num_len((int)buf.st_size) > g_options.sizes.size_size)
		g_options.sizes.size_size = num_len((int)buf.st_size);
	if (num_len(minor(buf.st_rdev)) > g_options.sizes.minor_size)
		g_options.sizes.minor_size = num_len(minor(buf.st_rdev));
	if (num_len(major(buf.st_rdev)) > g_options.sizes.major_size)
		g_options.sizes.major_size = num_len(major(buf.st_rdev));
	g_options.sizes.total += buf.st_blocks;
}

void	allocate_buffer(struct stat	**buf, char **path_names, char *path)
{
	DIR				*dir;
	struct dirent	*sd;
	int 			i;
	char			*new_p;

	i = 0;
	dir = opendir(path);
	while ((sd = readdir(dir)) != NULL)
	{
		buf[i] = malloc(sizeof(struct stat));
		new_p = add_valid_path(path, sd->d_name);

		stat(new_p, buf[i]);

		check_sizes(*buf[i]);

		ft_strdel(&new_p);
		path_names[i] = ft_strjoin(sd->d_name, "");
		i++;
	}
	buf[i] = NULL;
	path_names[i] = NULL;
	closedir(dir);

}

void	print_buffer(struct stat **buf, char **path_names, char *path)
{
	int i;

	g_options.a ? g_options.size++ : 0;
	if (g_options.l && g_options.size > 2)
	{
		ft_putstr("total ");
		ft_putnbr(g_options.sizes.total);
		ft_putchar('\n');
	}
	i = -1;
	while (buf[++i] != NULL)
		if (path_names[i][0] != '.' || g_options.a == 1)
		{
			if (g_options.l)
				long_output(*buf[i], path_names[i], path);
			else
				ft_printf("%s\n", path_names[i]);
		}
	g_options.sizes.total = 0;
}


