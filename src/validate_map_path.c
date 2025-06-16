/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:28:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/16 20:01:28 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_validate_map_path(t_game *game)
{
	char **temp_map;
	int collectibles;
	int exit_found;
	
	//ft_check_collectibles_surroundings(game);	
	temp_map = ft_create_temp_map(game);
	collectibles = 0;
	exit_found = 0;
	ft_flood_fill(game, temp_map, game->map.player_pos_x, 
		game->map.player_pos_y, &collectibles, &exit_found);
	// Verifica se todos os coletáveis são acessíveis
	if (collectibles != game->map.collectibles)
	{
		ft_free_temp_map(temp_map, game->map.height);
		ft_error_message("Some collectibles are not reachable!");
	}
	// Verifica se a saída é acessível
	if (!exit_found)
	{
		ft_free_temp_map(temp_map, game->map.height);
		ft_error_message("Exit is not reachable!");
	}
	ft_free_temp_map(temp_map, game->map.height);
}

char	**ft_create_temp_map(t_game *game)
{
	char **temp_map;
	int i;
	
	temp_map = (char **)malloc(sizeof(char *) * game->map.height);
	if (!temp_map)
		ft_error_message("Memory allocation failed");	
	i = 0;
	while (i < game->map.height)
	{
		temp_map[i] = ft_strdup(game->map.grid[i]);
		if (!temp_map[i])
		{
			ft_free_temp_map(temp_map, i);
			ft_error_message("Memory allocation failed");
		}
		i++;
	}
	return (temp_map);
}


/*
void	ft_validate_map_walls(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (y == 0 || y == game->map.height - 1
				|| x == 0 || x == game->map.width - 1)
			{
				if (game->map.grid[y][x] != MAP_WALL)
					ft_error_message("Map must be surrounded by walls!");
			}
			x++;
		}
		y++;
	}
}
 */