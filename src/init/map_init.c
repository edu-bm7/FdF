/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:16 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:18 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	atoi_map_row(int row, char **map, t_map_data *map_data);
static void	copy_map(t_map_data *map_data);
void		scale_down_map(t_map_data *map_data);

void	initialize_map_data(const char *file, t_map_data *map_data)
{
	char	*map_row;
	char	*map_trim;
	char	**map;
	int		row;
	int		fd;

	fd = open_file(file);
	map_row = get_next_line(fd);
	map_trim = map_row;
	row = 0;
	while (map_row != NULL)
	{
		map_trim = ft_strtrim(map_row, "\n");
		map = ft_split(map_trim, ' ');
		atoi_map_row(row, map, map_data);
		row++;
		free(map_row);
		free(map_trim);
		free_map((void **)map);
		map_row = get_next_line(fd);
	}
	close(fd);
}

void	allocate_initial_coord(t_map_data *map_data)
{
	int	rows;
	int	columns;

	rows = map_data->rows;
	columns = map_data->columns;
	map_data->initial_coord = ft_calloc(rows + 1, sizeof(t_point *));
	if (!map_data->initial_coord)
	{
		perror("Error: Can't allocate initial coordinates matrix : \n");
		exit (1);
	}
	while (--rows >= 0)
	{
		map_data->initial_coord[rows] = ft_calloc(columns, sizeof(t_point));
	}
}

void	allocate_iso_coord(t_map_data *map_data)
{
	int	rows;
	int	columns;

	rows = map_data->rows;
	columns = map_data->columns;
	map_data->iso_coord = ft_calloc(rows + 1, sizeof(t_point *));
	if (!map_data->iso_coord)
	{
		perror("Error: Can't allocate isometric coordinates matrix : \n");
		exit (1);
	}
	while (--rows >= 0)
	{
		map_data->iso_coord[rows] = ft_calloc(columns, sizeof(t_point));
	}
	copy_map(map_data);
	find_min(map_data);
}

static void	atoi_map_row(int row, char **map, t_map_data *map_data)
{
	int		columns;
	char	*has_color;

	columns = 0;
	while (columns < map_data->columns)
	{
		map_data->initial_coord[row][columns].x = columns;
		map_data->initial_coord[row][columns].y = row;
		map_data->initial_coord[row][columns].z = ft_atoi(map[columns]);
		has_color = ft_strchr(map[columns], ',');
		if (has_color)
		{
			has_color++;
			map_data->initial_coord[row][columns].color = ft_atoi(has_color);
		}
		else
			map_data->initial_coord[row][columns].color = DEFAULT_COLOR;
		columns++;
	}
}

static void	copy_map(t_map_data *map_data)
{
	int		row;
	int		column;
	t_point	**matrix;

	row = 0;
	map_data->max.x = 0;
	map_data->max.y = 0;
	matrix = map_data->initial_coord;
	while (row < map_data->rows)
	{
		column = 0;
		while (column < map_data->columns)
		{
			map_data->iso_coord[row][column].x = matrix[row][column].x;
			map_data->iso_coord[row][column].y = matrix[row][column].y;
			map_data->iso_coord[row][column].z = matrix[row][column].z;
			map_data->iso_coord[row][column].color = matrix[row][column].color;
			scale_coordinates(&map_data->iso_coord[row][column]);
			rotate_point(&map_data->iso_coord[row][column]);
			find_max(map_data, map_data->iso_coord[row][column].x,
				map_data->iso_coord[row][column].y);
			column++;
		}
		row++;
	}
}
