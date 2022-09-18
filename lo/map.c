#include "long.h"

/*int	ft_extension(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if ((s[i] == 'r') && (s[i-1] == 'e') && (s[i-2] == 'b') && (s[i-3] == '.'))
		return 1;
	return 0;
}*/

int	ft_ext(char *s)
{
	s = ft_strchr(s, '.');
	if (ft_strcmp(".ber", s) == 0)
		return (1);
	return 0;
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

int	ft_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (i == 0 || i == (ft_strlen(s)-1))
		{
			if (s[i] != '1')
				return (0);
		}
		if (s[i] != 'C' && s[i] != 'P' && s[i] != 'E' && s[i] != '0' 
			&& s[i] != '1')
			return 0;
		i++;
	}
	return i;
}

void	ft_ss(char **t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (t[i] != '\n')
	{
		
	}
}


int	main()
{
	char *s;
	int	fd = open("map.ber", O_RDONLY);

	s = get_next_line(fd);
	return 0;
}


