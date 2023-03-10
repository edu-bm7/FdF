/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:05 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/05 04:02:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	kill_mlx(t_map_data *map_data);

void	mlx_exit(t_map_data *map_data)
{
	free_map((void **)map_data->initial_coord);
	free_map((void **)map_data->iso_coord);
}

int	handle_keyrelease(int keysym, t_map_data *map_data)
{
	if (keysym == XK_ESCAPE)
		kill_mlx(map_data);
	return (0);
}

static void	kill_mlx(t_map_data *map_data)
{
	mlx_exit(map_data);
	if (map_data->img.mlx_img)
		mlx_destroy_image(map_data->mlx_ptr, map_data->img.mlx_img);
	if (map_data->win_ptr)
		mlx_destroy_window(map_data->mlx_ptr, map_data->win_ptr);
	if (map_data->mlx_ptr)
	{
		mlx_destroy_display(map_data->mlx_ptr);
		free(map_data->mlx_ptr);
	}
	exit(0);
}

int	handle_mouse(t_map_data *map_data)
{
	kill_mlx(map_data);
	return (0);
}

void	initialize_mlx(t_map_data *map_data)
{
	map_data->mlx_ptr = mlx_init();
	if (map_data->mlx_ptr == NULL)
	{
		ft_printf("Error: Mlx initialization error\n");
		exit (MLX_ERROR);
	}
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (map_data->win_ptr == NULL)
	{
		free(map_data->win_ptr);
		ft_printf("Error: Mlx window error\n");
		exit (MLX_ERROR);
	}
	map_data->img.mlx_img = mlx_new_image(map_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	map_data->img.addr = mlx_get_data_addr(map_data->img.mlx_img,
			&map_data->img.bpp, &map_data->img.line_len,
			&map_data->img.endian);
}
