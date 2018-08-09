/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmp_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:58:58 by mtupikov          #+#    #+#             */
/*   Updated: 2018/08/09 16:58:59 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls_header.h"

int		compare_lex(char *a, char *b)
{
	return (g_options.small_r * ft_strcmp(a, b));
}

int		compare_t(struct stat *a, struct stat *b)
{
	return (g_options.small_r == 1 ?
			(a->st_mtimespec.tv_sec < b->st_mtimespec.tv_sec) :
			(a->st_mtimespec.tv_sec > b->st_mtimespec.tv_sec));
}

int		compare_u(struct stat *a, struct stat *b)
{
	return (g_options.small_r == 1 ?
			(a->st_atimespec.tv_sec < b->st_atimespec.tv_sec) :
			(a->st_atimespec.tv_sec > b->st_atimespec.tv_sec));
}
