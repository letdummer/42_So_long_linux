/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/17 17:00:43 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_wind(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	if (window_width > WIND_WIDTH)
		ft_error_message(game, "Map is too wide. Maximum width is 30 tiles.");
	if (window_height > WIND_HEIGHT)
		ft_error_message(game, "Map is too tall. Maximum height is 16 tiles.");
	game->mlx_connect = mlx_init();
	if (game->mlx_connect == NULL)
		ft_error_message(game, "Error on the MLX");
	game->mlx_wind = mlx_new_window(game->mlx_connect,
			window_width, window_height, "so_long");
	if (game->mlx_wind == NULL)
	{
		ft_error_message(game, "Error creating window");
		handle_close(game);
	}
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		ft_printf("The game was closed by pressing the key (ESC).");
		handle_close(game);
	}
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT)
	{
		ft_move_player(game, key);
	}
	return (0);
}
