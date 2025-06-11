/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:25 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/11 13:55:55 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_validate_map_extension(char *file)
{
	char	*extension;
	char	*basename;
	
	if (file == NULL)
		ft_error_message("Invalid file!");
	if (file[0] == '.')
	{
		if (file[1] == '/')
			file += 2;
		else
		ft_error_message("It's a hidden file, not a map '.ber'!");
	}
	basename = ft_strrchr(file, '/');
	if (basename)
		basename++;
	else
		basename = file;
	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strcmp(extension, ".ber") != 0)
		ft_error_message("Invalid file. Must be '.ber");
	if (extension == basename)
		ft_error_message("Invalid. It's a hidden file.");
}

void	ft_validate_map_content(t_game *game)
{
	int		y;

	y = 0;
	while (y < game->map.height)
	{
		ft_check_line_content(game->map.grid[y], y, game);
		y++;
	}
	if (game->map.exits != 1)
		ft_error_message("The map must have exactly one exit.");
	if (game->map.player != 1)
		ft_error_message("The map must have exactly one player.");
	if (game->map.collectibles < 1)
		ft_error_message("The map must have at least one collect.");

	ft_validate_map_walls(game);
	ft_check_exit(game);
	ft_validate_map_path(game);
}

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
			ft_error_message("Invalid map.\nFound invalid characters.");
		i++;
	}

}
void ft_check_exit(t_game *game)
{
	int exit_x;
	int exit_y;
	int accessible_sides;

	ft_find_exit_position(game, &exit_x, &exit_y);
	accessible_sides = 0;
	// Verifica os quatro lados da saída
	if (exit_y > 0 && game->map.grid[exit_y - 1][exit_x] != MAP_WALL)
		accessible_sides++;
	if (exit_y < game->map.height - 1 && game->map.grid[exit_y + 1][exit_x] != MAP_WALL)
		accessible_sides++;
	if (exit_x > 0 && game->map.grid[exit_y][exit_x - 1] != MAP_WALL)
		accessible_sides++;
	if (exit_x < game->map.width - 1 && game->map.grid[exit_y][exit_x + 1] != MAP_WALL)
		accessible_sides++;
	if (accessible_sides == 0)
		ft_error_message("Exit is completely surrounded by walls!");
}

void ft_find_exit_position(t_game *game, int *exit_x, int *exit_y)
{
	int x;
	int y;

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
				return;
			}
			x++;
		}
		y++;
	}
}
