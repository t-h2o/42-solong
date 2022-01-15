#include	"sl.h"

static int
	all_one(char * line, int * len)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1')
		{
			printf("There is a hole up or down side\n");
			return (1);
		}
	}
	if (*len && i != *len)
	{
		printf("last line isn't same size\n");
		return (1);
	}
	*len = i;
	return (0);
}

static int
	map_error(char ** map)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	if (all_one(map[0], &len))
		return (1);
	printf("lenght of the 1st line : %d\n", len);
	j = 0;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if ((i == 0 || i == len - 1) && map[j][i] != '1')
			{
				printf("There is a hole right or left\n");
				return (1);
			}
		}
		if (len != i)
		{
			printf("There is asometrie\n");
			return (1);
		}
	}
	if (all_one(map[j - 1], &len))
		return (1);
	return (0);
}

static char
	**map_create(char *s)
{
	int		fd;
	int		n;
	int		i;
	char	*l;
	char	**r;

	fd = open(s, O_RDONLY);
	n = 0;
	l = (char *) 1;
	while (l)
	{
		l = get_next_line(fd);
		free(l);
		n++;
	}
	printf("\n\nLINE : %d\n\n", n);
	close(fd);
	r = malloc(sizeof(char *) * n);
	if (!r)
		return (0);
	r[n] = 0;
	fd = open(s, O_RDONLY);
	i = 0;
	while (i < n)
		r[i++] = get_next_line(fd);
	close(fd);
	return (r);
}

char
	**sl_map(char *s)
{
	char ** r;

	r = map_create(s);
	if (!r)
		exit(0);
	if (map_error(r))
		exit(0);
	return (r);
}
