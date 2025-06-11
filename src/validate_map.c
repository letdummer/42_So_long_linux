/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:25 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/09 14:31:28 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_validate_map_extension(char *file)
{
	char	*extension;

	if (file == NULL)
		ft_error_message("Invalid file!");
	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strcmp(extension, ".ber") != 0)
		ft_error_message("Invalid file. Must be '.ber");
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
