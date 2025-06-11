/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:45:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/10 21:53:09 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_update_player_pos(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_pos_y][game->map.player_pos_x] = MAP_FLOOR;
	ft_update_grid(game, game->map.player_pos_x, game->map.player_pos_y);
	game->map.player_pos_x = new_x;
	game->map.player_pos_y = new_y;
	game->map.grid[new_y][new_x] = MAP_PLAYER;
	ft_update_grid(game, new_x, new_y);
	game->img.step_count++;
	game->moves++;
	ft_render_hud(game);
}

void	ft_move_player(t_game *game, int direction)
{
	int	aux_x;
	int	aux_y;

	aux_x = game->map.player_pos_x;
	aux_y = game->map.player_pos_y;
	game->img.last_direction = direction;
	if (direction == KEY_W || direction == KEY_UP)
		aux_y += -1;
	else if (direction == KEY_A || direction == KEY_LEFT)
		aux_x += -1;
	else if (direction == KEY_S || direction == KEY_DOWN)
		aux_y += 1;
	else if (direction == KEY_D || direction == KEY_RIGHT)
		aux_x += 1;
	if (ft_validate_move(aux_x, aux_y, game))
		ft_update_player_pos(game, aux_x, aux_y);
}

int	ft_special_tiles(int aux_x, int aux_y, t_game *game)
{
	int	i;
	int	j;

	if (game->map.grid[aux_y][aux_x] == MAP_COLLECT)
	{
		game->collected_items++;
		if (game->collected_items == game->map.collectibles)
		{
			i = -1;
			while (++i < game->map.height)
			{
				j = -1;
				while (++j < game->map.width)
					if (game->map.grid[i][j] == MAP_EXIT)
						ft_update_grid(game, j, i);
			}
		}
		return (1);
	}
	if (game->map.grid[aux_y][aux_x] == MAP_EXIT
		&& game->collected_items == game->map.collectibles)
	{
		ft_win(game);
	}
	return (0);
}

int	ft_handle_collectables(t_game *game)
{
	game->collected_items++;
	if (game->collected_items == game->map.collectibles)
		ft_update_exit(game, game->map.player_pos_x, game->map.player_pos_y);
	return (1);
}

int	ft_validate_move(int aux_x, int aux_y, t_game *game)
{
	if (aux_y < 0 || aux_x < 0 || aux_y >= game->map.height
		|| aux_x >= game->map.width)
		return (0);
	if (game->map.grid[aux_y][aux_x] == MAP_WALL)
		return (0);
	if (game->map.grid[aux_y][aux_x] == MAP_FLOOR)
		return (1);
	return (ft_special_tiles(aux_x, aux_y, game));
}
