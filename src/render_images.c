/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/10 18:12:15 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_images(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
				game->img.floor, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
			if (game->map.grid[y][x] == MAP_WALL)
				ft_render_wall(game, x, y);
			else if (game->map.grid[y][x] == MAP_COLLECT)
				mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
					game->img.collect, x * TILE_SIZE, (y * TILE_SIZE)
					+ HUD_HEIGHT);
			else if (game->map.grid[y][x] == MAP_EXIT)
				render_exit(game, x, y);
			else if (game->map.grid[y][x] == MAP_PLAYER)
				mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
					ft_player_images(game), x * TILE_SIZE, (y * TILE_SIZE)
					+ HUD_HEIGHT);
		}
	}
}

void	ft_render_wall(t_game *game, int x, int y)
{
	char	*wall_path;
	void	*temp_wall;

	wall_path = ft_walls_tiles(game, x, y);
	temp_wall = mlx_xpm_file_to_image(game->mlx_connect,
			wall_path, &game->img.width, &game->img.height);
	if (temp_wall)
	{
		mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
			temp_wall, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
		mlx_destroy_image(game->mlx_connect, temp_wall);
	}
}

void	render_exit(t_game *game, int x, int y)
{
	void	*exit_open;

	if (game->collected_items == game->map.collectibles)
	{
		exit_open = mlx_xpm_file_to_image(game->mlx_connect, EXIT_OPEN,
				&game->img.width, &game->img.height);
		mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
			exit_open, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
		mlx_destroy_image(game->mlx_connect, exit_open);
	}
	else
		mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
			game->img.exit, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
}

void	ft_render_images(t_game *game)
{
	game->img.floor = mlx_xpm_file_to_image(game->mlx_connect, FLOOR,
			&game->img.width, &game->img.height);
	game->img.wall = NULL;
	game->img.collect = mlx_xpm_file_to_image(game->mlx_connect, COLLECTIBLE,
			&game->img.width, &game->img.height);
	game->img.exit = mlx_xpm_file_to_image(game->mlx_connect, EXIT,
			&game->img.width, &game->img.height);
	ft_load_player_images(game);
	game->img.last_direction = KEY_D;
	game->img.step_count = 0;
}

char	*ft_walls_tiles(t_game *game, int x, int y)
{
	if (x == 0 && y == 0)
		return (WALL_TOP_LEFT);
	if (x == game->map.width - 1 && y == 0)
		return (WALL_TOP_RIGHT);
	if (x == 0 && y == game->map.height - 1)
		return (WALL_BOTTOM_LEFT);
	if (x == game->map.width - 1 && y == game->map.height - 1)
		return (WALL_BOTTOM_RIGHT);
	if (y == 0)
		return (WALL_TOP);
	if (y == game->map.height - 1)
		return (WALL_BOTTOM);
	if (x == 0)
		return (WALL_LEFT);
	if (x == game->map.width - 1)
		return (WALL_RIGHT);
	return (WALL);
}
