#include "graphics.h"

int	find_holes(char **array, int rows)
{
	int	i;

	i = -1;
	if (!array || !array[0])
		return (0);
	while (array[0][++i])
		if (array[0][i] != '1' || array[rows - 1][i] != '1')
			exit(write(2, "Not fully walled\n", 16));
	i = -1;
	while (array[++i])
		if (array[i][0] != '1' || array[i][ft_strlen(array[0]) - 1] != '1')
			exit(write(2, "Not fully walled\n", 16));
	return (0);
}

void	count_items(char *array, t_world *world)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (array[i] == 'P')
			world->count.player ++;
		if (array[i] == 'C')
			world->count.collectible ++;
		if (array[i] == 'E')
			world->count.exit ++;
	}
}

char	**read_map(char *file, int rows, t_world *world)
{
	int		i;
	char	*buffer;
	char	**array;
	int		fd;

	fd = open(file, 0);
	i = 0;
	buffer = get_next_line(fd);
	array = malloc(sizeof(char *) * (rows + 1));
	while (buffer)
	{
		array[i++] = ft_substr(buffer, 0, ft_strrchr(buffer, '\n') - buffer);
		count_items(array[i - 1], world);
		free(buffer);
		buffer = get_next_line(fd);
	}
	array[i] = NULL;
	close(fd);
	if (world->count.player < 1)
		exit(write(1, "Error: Incorrect number of players\n", 34));
	if (world->count.exit < 1)
		exit(write(1, "Error: No exit\n", 15));
	if (world->count.collectible < 1)
		exit(write(1, "Error: No collectible\n", 21));
	return (array);
}

t_tile	**char2tile(t_world *world, int row_count, t_display *display)
{
	int		x;
	int		y;
	t_tile	**ret_array;

	ret_array = malloc(sizeof(t_tile *) * (row_count + 1));
	y = -1;
	while (++y < row_count)
	{
		ret_array[y] = malloc(sizeof(t_tile) * (ft_strlen(world->grid[0]) + 1));
		x = -1;
		while (++x < (int)(ft_strlen(world->grid[y])))
		{
			ret_array[y][x] = (t_tile){world->grid[y][x], NULL, };
			if (world->grid[y][x] == 'S')
				ret_array[y][x].data = ((t_enemy *)(append(&world->enemies, \
				new_obj("enemy", new_enemy(display, (t_xy){x, y}))))->data);
			if (world->grid[y][x] == 'C')
				ret_array[y][x].data = (t_coin *)(append(&world->coins, \
				new_obj("c", new_coin(display, (t_xy){x, y})))->data);
			if (world->grid[y][x] == 'P')
				world->player->pos = (t_xy){x, y};
		}
		ret_array[y][x] = (t_tile){0, NULL};
	}
	ret_array[y] = NULL;
	return (ret_array);
}

char	**scan_map(t_world *world, char *file)
{
	int		line_count;
	char	**char_array;
	int		i;
	int		fd;

	fd = open(file, 0);
	if (fd == -1)
		exit(write(2, "Error: Cannot read file\n", 23));
	line_count = count_newline(file);
	if (line_count == 1)
		exit(write(2, "Error: Incorrect length\n", 23));
	char_array = malloc(sizeof(char *) * (line_count + 1));
	char_array = read_map(file, line_count, world);
	i = -1;
	while (char_array[++i + 1])
		if (ft_strlen(char_array[i])
			!= ft_strlen(char_array[i + 1]))
			exit(write(2, "Error: Incorrect length\n", 23));
	find_holes(char_array, line_count);
	print_char_array(char_array);
	world->dimensions.y = line_count;
	world->dimensions.x = ft_strlen(char_array[0]);
	if (world->dimensions.y == world->dimensions.x)
		exit(write(2, "Error: Incorrect length\n", 23));
	return (char_array);
}