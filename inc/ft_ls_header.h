/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:56:17 by mtupikov          #+#    #+#             */
/*   Updated: 2018/08/09 16:56:19 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_FT_LS_HEADER_H
# define FT_LS_FT_LS_HEADER_H

# include "../libft/includes/ft_printf.h"
# include <time.h>
# include <fcntl.h>
# include <sys/ttycom.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <grp.h>
# include <pwd.h>
# include <dirent.h>

/*
**	STRUCTS
*/

typedef struct		s_sizes
{
	int				link_size;
	int				owner;
	int				group;
	int				size_size;
	int				minor_size;
	int				major_size;
	int				total;
}					t_sizes;

typedef struct		s_options
{
	int				l;
	int				big_r;
	int				small_r;
	int				a;
	int				f;
	int				u;
	int				t;
	int				size;
	int				argc;
	t_sizes			sizes;
}					t_options;

/*
**	PROTOTYPES
*/

t_options			g_options;

/*
**	main_utils.c
*/

void				init_default_options();
void				check_args_errors(char **args);
int					num_len(int num);
void				init_default_sizes();
void				print_access_util(mode_t mode);

/*
**	ft_ls_algorithm.c
*/

void				ft_ls_algorithm(char *path);

/*
**	buffer_management.c
*/

int					count_elements_in_dir(DIR *dir);
void				allocate_buffer(struct stat	**buf,
					char **path_names, char *path);
void				print_buffer(struct stat **buf,
					char **path_names, char *path);
char				*add_valid_path(char *path, char *add);

/*
**	file_management.c
*/

int					check_if_file(char *path);
void				long_output(struct stat buf, char *filename, char *path);

/*
**	printing_management.c
*/

void				print_access(mode_t mode);
void				print_date(time_t date);
void				print_integer(int num, int out);
void				print_string(char *s, int out);
void				print_majmin(struct stat buf);

/*
**	sorting_management.c
*/

void				sort(struct stat **buf, char **path_names);

/*
**	sort_cmp_functions.c
*/

int					compare_lex(char *a, char *b);
int					compare_t(struct stat *a, struct stat *b);
int					compare_u(struct stat *a, struct stat *b);

#endif
