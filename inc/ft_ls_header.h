#ifndef FT_LS_FT_LS_HEADER_H
# define FT_LS_FT_LS_HEADER_H

#include "../libft/includes/ft_printf.h"
#include <time.h>
#include <fcntl.h>
#include <sys/ttycom.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*
**	DEFINES
*/



/*
**	STRUCTS
*/

typedef struct		s_options
{
	int 			l;
	int 			big_r;
	int 			small_r;
	int 			a;
	int 			t;
	int 			win_h;
	int 			win_w;
}					t_options;

typedef struct		s_file
{
	char 			*path;

	struct s_file	*next;
}					t_file;

/*
**	PROTOTYPES
*/

t_options			g_options;


#endif
