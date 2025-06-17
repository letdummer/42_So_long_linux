/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:28 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/17 16:52:19 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_flood_fill_check(t_game *game)
{
	char	**temp_map;
	char	**exit_map;
	int		collectibles_found;
	int		exit_found;

	temp_map = ft_create_temp_map(game);
	if (!temp_map)
		ft_error_message(game, "Memory allocation failed");
	collectibles_found = ft_check_collectibles_path(game, temp_map,
			game->map.player_pos_x, game->map.player_pos_y);
	ft_free_temp_map(temp_map, game->map.height);
	exit_map = ft_create_temp_map(game);
	if (!exit_map)
		ft_error_message(game, "Memory allocation failed");
	exit_found = ft_check_exit_path(game, exit_map,
			game->map.player_pos_x, game->map.player_pos_y);
	ft_free_temp_map(exit_map, game->map.height);
	if (collectibles_found < game->map.collectibles)
		ft_error_message(game, "Not all collectibles are reachable!");
	if (!exit_found)
		ft_error_message(game,
			"Exit is not reachable after collecting all items!");
}

int	ft_check_collectibles_path(t_game *game, char **map, int x, int y)
{
	int	count;

	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width
		|| map[y][x] == MAP_WALL || map[y][x] == 'V' || map[y][x] == MAP_EXIT)
		return (0);
	count = 0;
	if (map[y][x] == MAP_COLLECT)
		count = 1;
	map[y][x] = 'V';
	count += ft_check_collectibles_path(game, map, x, y - 1);
	count += ft_check_collectibles_path(game, map, x + 1, y);
	count += ft_check_collectibles_path(game, map, x, y + 1);
	count += ft_check_collectibles_path(game, map, x - 1, y);
	return (count);
}

int	ft_check_exit_path(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width
		|| map[y][x] == MAP_WALL || map[y][x] == 'V')
		return (0);
	if (map[y][x] == MAP_EXIT)
		return (1);
	map[y][x] = 'V';
	if (ft_check_exit_path(game, map, x, y - 1))
		return (1);
	if (ft_check_exit_path(game, map, x + 1, y))
		return (1);
	if (ft_check_exit_path(game, map, x, y + 1))
		return (1);
	if (ft_check_exit_path(game, map, x - 1, y))
		return (1);
	return (0);
}
