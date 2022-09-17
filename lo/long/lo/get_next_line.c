#include "long.h"

char	*read_buff_size(int fd, char *lines)
{
	char	*bufer;
	int		i;

	i = 1;
	bufer = malloc(BUFFER_SIZE + 1);
	if (!bufer)
		return (NULL);
	while (i && !(ft_strchr(lines, '\n')))
	{
		i = read(fd, bufer, BUFFER_SIZE);
		if (i == -1)
		{
			free(bufer);
			return (NULL);
		}
		bufer[i] = '\0';
		lines = ft_strjoin(lines, bufer);
	}
	free (bufer);
	return (lines);
}

char	*one_line(char *lines)
{
	int	i;

	i = 0;
	if (!lines[i])
		return (NULL);
	while (lines[i] != '\n' && lines[i])
		i++;
	return (ft_substr(lines, 0, ++i));
}

char	*lines_rest(char *file_line)
{
	int		j;
	char	*dup;

	j = 0;
	while (file_line[j] != '\n' && file_line[j])
		j++;
	if (!file_line[j])
	{
		free(file_line);
		return (NULL);
	}
	dup = ft_substr(file_line, ++j, ft_strlen(file_line));
	free(file_line);
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	*file_line;
	char		*o_line;
	int	i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file_line = read_buff_size(fd, file_line);
	if (!file_line)
		return (NULL);
	o_line = one_line(file_line);
	file_line = lines_rest(file_line);
	return (o_line);
}

int	ft_ones(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(void)
{
	printf("Error\n");
	exit(1);
}

int	ft_border(char *s)
{
	if (s[0] != '1' || s[ft_strlen(s) - 1] != '1')
		return 0;
	return 1;
}

int	ft_lines(char **s)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(s[0]);
	while (s[i])
	{
		if (ft_strlen(s[i]) != len)
			return 0;
		i++;
	}
	return 1;
}

void	ft_start(t_map *map)
{
	map->coin = 0;
	map->player = 0;
	map->columns = 0;
	map->exit = 0;
	map->lines = 0;
}

void	ft_check(char *s, t_map *lst)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 'P' && s[i] != 'C' && s[i] != 'E' && 
			s[i] != '0' && s[i] != '1')
			ft_error();
		if (s[i] == 'P')
			lst->player += 1;
		if (s[i] == 'C')
			lst->coin += 1;
		if (s[i] == 'E')
			lst->exit += 1;
		i++;
	}
}

void	ft_params(t_map *lst)
{
	if (lst->player != 1)
		ft_error();
	if (lst->coin < 1)
		ft_error();
	if (lst->exit != 1)
		ft_error();
}

t_map	counter(fd)
{
	int		i;
	char	*s;
	char	*t;
	t_map	lst;
	char	**map;
	int		j = 0;
	int		c = 0;


	i = 0;
	while (1)
	{
		t = get_next_line(fd);
		if (t == NULL)
			break;
		s = ft_strjoin(s, t);
		i++;
	}
	ft_start(&lst);
	lst.lines = i;
	printf("nbr of lines is %d\n", lst.lines);
	printf("%s\n", s);
	printf("%d\n", i);
	map = ft_split(s, '\n');
	if (i >= ft_strlen(map[0]))
		ft_error();
	if (!ft_ones(map[0]) || !ft_ones(map[i-1]))
		ft_error();
	while (c < i)
	{
		if (ft_border(map[c]) == 0)
			ft_error();
		ft_check(map[c], &lst);
		c++;
	}
	ft_params(&lst);
	printf("is is %d\n", lst.player);
	printf("is is %d\n", lst.exit);
	printf("is is %d\n", lst.coin);
	if (ft_lines(map) == 0)
		ft_error();
	lst.columns = ft_strlen(map[0]);
	printf("nbr of columns is %d \n", lst.columns);
	while (j < i)
	{
	 	printf("%s\n", map[j]);
		j++;
	}
	return (lst);
}

int	ft_ext(char *s)
{
	char *t;
	if (!ft_strchr(s, '.'))
		ft_error();
	t = ft_strchr(s, '.');
	if (ft_strcmp(t, ".ber") == 0)
		return 1;
	return 0;
}

int	main(int ac, char *av[])
{
	if (ac != 2)
		ft_error();
	if (ft_ext(av[1]) == 0)
		ft_error();
	int fd = open("map.ber", O_RDONLY);
	char **s;
	t_map lst;

	void	*mlx_ptr;
	void	*win_ptr;
	
	lst = counter(fd);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 100 *lst.columns, 100*lst.lines, "pp");
	mlx_loop(mlx_ptr);

	printf("lines %d\n", lst.lines);
	return 0;
}
