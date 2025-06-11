/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:28 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/11 09:25:46 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_game		*game;
	char		*map_path;

	map_path = av[1];
	if (ac != 2)
		ft_error_message("Usage: ./so_long ./maps/map.ber");
	ft_validate_map_extension(map_path);
	game = ft_init_game();
	if (!game)
		ft_error_message("Failed to initialize game.");
	ft_map_init(game, map_path);
	ft_init_wind(game);
	ft_render_images(game);
	ft_map_images(game);
	ft_render_hud(game);
	mlx_key_hook(game->mlx_wind, handle_input, game);
	//mlx_hook(game->mlx_wind, 17, 0, handle_close, game);
	mlx_hook(game->mlx_wind, 33, 1L<<17, handle_close, game); // Linux
	mlx_loop(game->mlx_connect);
	return (0);
}

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx_connect = NULL;
	game->mlx_wind = NULL;
	game->img.floor = NULL;
	game->img.wall = NULL;
	game->img.collect = NULL;
	game->img.exit = NULL;
	game->img.player_up_1 = NULL;
	game->img.player_up_2 = NULL;
	game->img.player_down_1 = NULL;
	game->img.player_down_2 = NULL;
	game->img.player_left_1 = NULL;
	game->img.player_left_2 = NULL;
	game->img.player_right_1 = NULL;
	game->img.player_right_2 = NULL;
	game->img.last_direction = KEY_D;
	game->img.step_count = 0;
	game->collected_items = 0;
	game->moves = 0;
	return (game);
}

void	ft_map_init(t_game *game, char *map_path)
{
	game->map.collectibles = 0;
	game->map.exits = 0;
	game->map.player = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_pos_x = 0;
	game->map.player_pos_y = 0;
	ft_get_map_dimensions(game, map_path);
	ft_allocate_map_memory(game);
	ft_fill_map_content(game, map_path);
	ft_validate_map_content(game);
}

void	ft_win(t_game *game)
{
	ft_printf("WIN!\n");
	sleep(1);
	handle_close(game);
}
