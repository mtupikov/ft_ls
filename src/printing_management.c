#include "../inc/ft_ls_header.h"

void	print_access(mode_t mode)
{
	ft_putchar((S_ISFIFO(mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(mode)) ? 's' : '\0');
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar((mode & S_ISVTX) ? 'T' : '-');
	ft_putstr("  ");
}

void	print_date(time_t date)
{
	char 	*str_date;

	str_date = ctime(&date);
	write(STDOUT_FILENO, str_date + 9, 1);
	ft_putchar(' ');
	write(STDOUT_FILENO, str_date + 4, 3);
	ft_putchar(' ');
	write(STDOUT_FILENO, str_date + 11, 5);
	ft_putchar(' ');
}

void	print_integer(int num, int out)
{
	int i;

	i = 0;
	if (num_len(num) != out)
		while (i++ < out - num_len(num))
			ft_putchar(' ');
	ft_putnbr(num);
	ft_putchar(' ');
}

void	print_string(char *s, int out)
{
	int i;
	int len;

	len = (int)ft_strlen(s);
	i = 0;
	if (len != out)
		while (i++ < out - len)
			ft_putchar(' ');
	ft_putstr(s);
	ft_putchar(' ');
}

