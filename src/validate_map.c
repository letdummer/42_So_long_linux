/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:25 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/17 17:08:03 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_check_line_content(char *str, int y, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if (str[i] == MAP_COLLECT)
			game->map.collectibles++;
		else if (str[i] == MAP_EXIT)
			game->map.exits++;
		else if (str[i] == MAP_PLAYER)
		{
			game->map.player++;
			game->map.player_pos_x = i;
			game->map.player_pos_y = y;
		}
		else if (str[i] != MAP_WALL && str[i] != MAP_FLOOR
			&& str[i] != MAP_COLLECT && str[i] != MAP_EXIT
			&& str[i] != MAP_PLAYER)
			ft_error_message(game, "Found invalid characters.");
		i++;
	}
}

void	ft_check_exit(t_game *game)
{
	int	exit_x;
	int	exit_y;
	int	accessible_sides;

	ft_find_exit_position(game, &exit_x, &exit_y);
	accessible_sides = 0;
	if (exit_y > 0 && game->map.grid[exit_y - 1][exit_x] != MAP_WALL)
		accessible_sides++;
	if (exit_y < game->map.height - 1
		&& game->map.grid[exit_y + 1][exit_x] != MAP_WALL)
		accessible_sides++;
	if (exit_x > 0 && game->map.grid[exit_y][exit_x - 1] != MAP_WALL)
		accessible_sides++;
	if (exit_x < game->map.width - 1
		&& game->map.grid[exit_y][exit_x + 1] != MAP_WALL)
		accessible_sides++;
	if (accessible_sides == 0)
		ft_error_message(game, "Exit is completely surrounded by walls!");
}

void	ft_find_exit_position(t_game *game, int *exit_x, int *exit_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_EXIT)
			{
				*exit_x = x;
				*exit_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	ft_check_surrounded_objects(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_PLAYER
				&& ft_is_surrounded(game, x, y))
				ft_error_message(game, "Player is surrounded by walls!");
			else if (game->map.grid[y][x] == MAP_COLLECT
				&& ft_is_surrounded(game, x, y))
				ft_error_message(game, "Collectible is surrounded by walls!");
			else if (game->map.grid[y][x] == MAP_EXIT
				&& ft_is_surrounded(game, x, y))
				ft_error_message(game, "Exit is surrounded by walls!");
			x++;
		}
		y++;
	}
}

int	ft_is_surrounded(t_game *game, int x, int y)
{
	if (y > 0 && (game->map.grid[y - 1][x] != MAP_WALL
		&& game->map.grid[y - 1][x] != MAP_EXIT))
		return (0);
	if (y < game->map.height - 1 && (game->map.grid[y + 1][x] != MAP_WALL
		&& game->map.grid[y + 1][x] != MAP_EXIT))
		return (0);
	if (x > 0 && (game->map.grid[y][x - 1] != MAP_WALL
		&& game->map.grid[y][x - 1] != MAP_EXIT))
		return (0);
	if (x < game->map.width - 1 && (game->map.grid[y][x + 1] != MAP_WALL
		&& game->map.grid[y][x + 1] != MAP_EXIT))
		return (0);
	return (1);
}
