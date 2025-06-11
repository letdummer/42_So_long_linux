/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/09 14:26:17 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_wind(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = (game->map.height * TILE_SIZE) + HUD_HEIGHT;
	if (window_width > WIND_WIDTH)
		ft_error_message("Map is too wide. Maximum width is 30 tiles.");
	if (window_height > WIND_HEIGHT)
		ft_error_message("Map is too tall. Maximum height is 16 tiles.");
	setenv("OBJC_DISABLE_INITIALIZE_FORK_SAFETY", "YES", 1);
	game->mlx_connect = mlx_init();
	if (game->mlx_connect == NULL)
		ft_error_message("Error on the MLX");
	game->mlx_wind = mlx_new_window(game->mlx_connect,
			window_width, window_height, "so_long");
	if (game->mlx_wind == NULL)
	{
		free(game->mlx_connect);
		ft_error_message("Error creating window");
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

void	ft_render_hud(t_game *game)
{
	int		x;
	int		y;
	char	*collectibles;
	char	*moves;

	y = -1;
	while (++y < HUD_HEIGHT)
	{
		x = 0;
		while (++x < game->map.width * TILE_SIZE)
		{
			mlx_pixel_put(game->mlx_connect, game->mlx_wind,
				x, y, HUD_COLOR);
		}
	}
	moves = ft_strjoin("Moves: ", ft_itoa(game->moves));
	collectibles = ft_strjoin("Collectibles: ",
			ft_strjoin(ft_itoa(game->collected_items),
				ft_strjoin("/", ft_itoa(game->map.collectibles))));
	mlx_string_put(game->mlx_connect, game->mlx_wind,
		10, 20, TEXT_COLOR, moves);
	mlx_string_put(game->mlx_connect, game->mlx_wind,
		10, 40, TEXT_COLOR, collectibles);
	free(moves);
	free(collectibles);
}
