#include "../inc/ft_ls_header.h"

void	print_access(mode_t mode)
{
	print_access_util(mode);
	ft_putchar((S_ISFIFO(mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(mode)) ? 'c' : '\0');
	ft_putchar((S_ISBLK(mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(mode)) ? '-' : '\0');
	ft_putchar((S_ISSOCK(mode)) ? 's' : '\0');
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_ISVTX && S_ISDIR(mode))
		ft_putchar('t');
	else if (mode & S_ISVTX)
		ft_putchar('T');
	else if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
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

void	print_majmin(struct stat buf)
{
	int		i;
	int		min;
	int		maj;

	min = num_len(minor(buf.st_rdev));
	maj = num_len(major(buf.st_rdev));
	i = 0;
	if (num_len(maj) != g_options.sizes.major_size)
		while (i++ < g_options.sizes.major_size - maj)
			ft_putchar(' ');
	ft_putnbr(major(buf.st_rdev));
	ft_putchar(',');
	i = 0;
	if (num_len(min) != g_options.sizes.minor_size)
		while (i++ < g_options.sizes.minor_size - min)
			ft_putchar(' ');
	ft_putnbr(minor(buf.st_rdev));
	ft_putchar(' ');
}