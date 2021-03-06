/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:59:05 by mtupikov          #+#    #+#             */
/*   Updated: 2018/08/09 16:59:06 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls_header.h"

void	swap(struct stat **buf, char **path_names, int l, int r)
{
	char		*c_tmp;
	struct stat	tmp;

	tmp = *buf[l];
	*buf[l] = *buf[r];
	*buf[r] = tmp;
	c_tmp = ft_strjoin(path_names[r], "");
	ft_strdel(&path_names[r]);
	path_names[r] = ft_strjoin(path_names[l], "");
	ft_strdel(&path_names[l]);
	path_names[l] = c_tmp;
}

void	do_sort(struct stat **buf, char **path_names,
		int (*cmp_b)(struct stat *, struct stat *),
		int (*cmp_l)(char *, char *))
{
	int i;
	int j;

	j = 0;
	while (++j < g_options.size)
	{
		i = 0;
		while (buf[++i])
			if ((cmp_l != NULL && cmp_l(path_names[i - 1],
				path_names[i]) > 0) ||
				(cmp_b != NULL && cmp_b(buf[i - 1], buf[i]) > 0))
				swap(buf, path_names, i - 1, i);
	}
}

void	sort(struct stat **buf, char **path_names)
{
	if (g_options.f == 1)
		return ;
	do_sort(buf, path_names, NULL, compare_lex);
	if (g_options.t == 1 && g_options.u == 0)
		do_sort(buf, path_names, compare_t, NULL);
	if (g_options.u == 1)
		do_sort(buf, path_names, compare_u, NULL);
}
