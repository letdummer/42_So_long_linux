/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:28:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/17 17:29:02 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_validate_map_extension(char *file)
{
	char	*extension;
	char	*basename;

	if (!file)
		ft_error_message(NULL, "Invalid file!");
	if (file[0] == '.')
	{
		if (file[1] == '/')
			file += 2;
		else
			ft_error_message(NULL, "It's a hidden file, not a map '.ber'!");
	}
	basename = ft_strrchr(file, '/');
	if (basename)
		basename++;
	else
		basename = file;
	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strcmp(extension, ".ber") != 0)
	{
		ft_error_message(NULL, "Invalid file. Must be '.ber'");
		exit(1);
	}	
	if (extension == basename)
		ft_error_message(NULL, "Invalid. It's a hidden file.");
}

void	ft_validate_map_content(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		ft_check_line_content(game->map.grid[y], y, game);
		y++;
	}
	if (game->map.exits != 1)
		ft_error_message(game, "The map must have exactly one exit.");
	if (game->map.player != 1)
		ft_error_message(game, "The map must have exactly one player.");
	if (game->map.collectibles < 1)
		ft_error_message(game, "The map must have at least one collectible.");
	ft_validate_map_borders(game);
	ft_check_surrounded_objects(game);
	ft_flood_fill_check(game);
}

char	**ft_create_temp_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * game->map.height);
	if (!temp_map)
		ft_error_message(game, "Memory allocation failed");
	i = 0;
	while (i < game->map.height)
	{
		temp_map[i] = ft_strdup(game->map.grid[i]);
		if (!temp_map[i])
		{
			ft_free_temp_map(temp_map, i);
			ft_error_message(game, "Memory allocation failed");
		}
		i++;
	}
	return (temp_map);
}

void	ft_validate_map_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (y == 0 || y == game->map.height - 1)
		{
			x = 0;
			while (x < game->map.width)
			{
				if (game->map.grid[y][x] != MAP_WALL)
					ft_error_message(game, "Map must be surrounded by walls!");
				x++;
			}
		}
		else
		{
			if (game->map.grid[y][0] != MAP_WALL
				|| game->map.grid[y][game->map.width - 1] != MAP_WALL)
				ft_error_message(game, "Map must be surrounded by walls!");
		}
		y++;
	}
}
