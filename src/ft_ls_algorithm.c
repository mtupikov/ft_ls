#include "../inc/ft_ls_header.h"

void	recursion(struct stat **buf, char **path_names, char *path)
{
	char	*new_p;
	int 	i;

	i = -1;
	while (buf[++i] != NULL)
	{
		if (path_names[i][0] != '.' && S_ISDIR(buf[i]->st_mode)) {
			new_p = add_valid_path(path, path_names[i]);
			ft_ls_algorithm(new_p);
			ft_strdel(&new_p);
		}
	}
}

void	free_all(struct stat **buf, char **path_names)
{
	int i;

	i = -1;
	while (buf[++i] != NULL)
	{
		ft_strdel(&path_names[i]);
		free(buf[i]);
	}
	free(buf);
	free(path_names);
}

void	read_directory(DIR *dir, char *path)
{
	struct stat		**buf;
	char			**path_names;
	int 			count_elem;

	count_elem = count_elements_in_dir(dir);
	g_options.size = count_elem;
	buf = malloc(sizeof(struct stat *) * (count_elem + 1));
	path_names = malloc(sizeof(char *) * (count_elem + 1));
	allocate_buffer(buf, path_names,path);
	sort(buf, path_names);
	print_buffer(buf, path_names);
	if (g_options.big_r == 1)
		recursion(buf, path_names, path);
	free_all(buf, path_names);
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


