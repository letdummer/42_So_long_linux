/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:12:47 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/10 18:12:48 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_update_grid(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
		game->img.floor, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	if (game->map.grid[y][x] == MAP_WALL)
		ft_update_wall(game, x, y);
	else if (game->map.grid[y][x] == MAP_COLLECT)
		mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
			game->img.collect, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	else if (game->map.grid[y][x] == MAP_EXIT)
		ft_update_exit(game, x, y);
	else if (game->map.grid[y][x] == MAP_PLAYER)
		mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
			ft_player_images(game), x * TILE_SIZE, (y * TILE_SIZE)
			+ HUD_HEIGHT);
}

void	ft_update_exit(t_game *game, int x, int y)
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

void	ft_update_wall(t_game *game, int x, int y)
{
	char	*wall_path;

	wall_path = ft_walls_tiles(game, x, y);
	game->img.wall = mlx_xpm_file_to_image(game->mlx_connect,
			wall_path, &game->img.width, &game->img.height);
	mlx_put_image_to_window(game->mlx_connect, game->mlx_wind,
		game->img.wall, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	mlx_destroy_image(game->mlx_connect, game->img.wall);
}

void	ft_load_player_images(t_game *game)
{
	game->img.player_up_1 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_UP_1, &game->img.width, &game->img.height);
	game->img.player_up_2 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_UP_2, &game->img.width, &game->img.height);
	game->img.player_down_1 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_DOWN_1, &game->img.width, &game->img.height);
	game->img.player_down_2 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_DOWN_2, &game->img.width, &game->img.height);
	game->img.player_left_1 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_LEFT_1, &game->img.width, &game->img.height);
	game->img.player_left_2 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_LEFT_2, &game->img.width, &game->img.height);
	game->img.player_right_1 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_RIGHT_1, &game->img.width, &game->img.height);
	game->img.player_right_2 = mlx_xpm_file_to_image(game->mlx_connect,
			PLAYER_RIGHT_2, &game->img.width, &game->img.height);
}

void	*ft_player_images(t_game *game)
{
	if (game->img.last_direction == KEY_W
		|| game->img.last_direction == KEY_UP)
	{
		if (game->img.step_count % 2 == 0)
			return (game->img.player_up_1);
		return (game->img.player_up_2);
	}
	if (game->img.last_direction == KEY_S
		|| game->img.last_direction == KEY_DOWN)
	{
		if (game->img.step_count % 2 == 0)
			return (game->img.player_down_1);
		return (game->img.player_down_2);
	}
	if (game->img.last_direction == KEY_A
		|| game->img.last_direction == KEY_LEFT)
	{
		if (game->img.step_count % 2 == 0)
			return (game->img.player_left_1);
		return (game->img.player_left_2);
	}
	if (game->img.step_count % 2 == 0)
		return (game->img.player_right_1);
	return (game->img.player_right_2);
}
