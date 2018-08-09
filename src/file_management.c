/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:59:11 by mtupikov          #+#    #+#             */
/*   Updated: 2018/08/09 16:59:12 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls_header.h"

void	print_owner(struct stat buf)
{
	char *tmp;

	if (getpwuid(buf.st_uid))
		print_string(getpwuid(buf.st_uid)->pw_name, g_options.sizes.owner);
	else
	{
		tmp = ft_itoa(buf.st_uid);
		print_string(tmp, g_options.sizes.owner);
		ft_strdel(&tmp);
	}
	ft_putchar(' ');
}

void	print_group(struct stat buf)
{
	char *tmp;

	if (getgrgid(buf.st_gid))
		print_string(getgrgid(buf.st_gid)->gr_name, g_options.sizes.group);
	else
	{
		tmp = ft_itoa(buf.st_gid);
		print_string(tmp, g_options.sizes.group);
		ft_strdel(&tmp);
	}
	ft_putchar(' ');
}

void	long_output(struct stat buf, char *filename, char *path)
{
	char c_buf[1024];
	char *tmp;

	print_access(buf.st_mode);
	print_integer(buf.st_nlink, g_options.sizes.link_size);
	print_owner(buf);
	print_group(buf);
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		print_majmin(buf);
	else
		print_integer((int)buf.st_size, g_options.sizes.size_size);
	ft_putchar(' ');
	g_options.u == 1 ? print_date(buf.st_atimespec.tv_sec) :
						print_date(buf.st_mtimespec.tv_sec);
	ft_putstr(filename);
	path == NULL ?
	(tmp = ft_strjoin(filename, ""))
	: (tmp = add_valid_path(path, filename));
	if (readlink(tmp, c_buf, 1024) != -1)
	{
		ft_putstr(" -> ");
		ft_putstr(c_buf);
	}
	ft_strdel(&tmp);
	ft_putchar('\n');
}

int		check_if_file(char *path)
{
	struct stat buf;
	char		c_buf[1024];
	int			is_link;

	if (path == (char *)0x1)
		return (1);
	lstat(path, &buf);
	if ((is_link = (int)readlink(path, c_buf, 1024)) < 0 &&
		!(S_ISREG(buf.st_mode)) && !(S_ISFIFO(buf.st_mode)))
		return (0);
	if (S_ISDIR(buf.st_mode) && !is_link)
		return (0);
	if (!g_options.big_r)
	{
		if (g_options.l)
			long_output(buf, path, NULL);
		else
			ft_printf("%s\n", path);
	}
	return (1);
}
