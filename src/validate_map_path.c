/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:28:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/11 14:15:34 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_validate_map_path(t_game *game)
{
	char **temp_map;
	int collectibles;
	int exit_found;
	
	ft_check_collectibles_surroundings(game);	
	temp_map = ft_create_temp_map(game);
	collectibles = 0;
	exit_found = 0;
	ft_flood_fill(temp_map, game->map.player_pos_x, 
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

void	ft_flood_fill(char **map, int x, int y, int *collectibles, int *exit_found)
{
	// Verifica limites do mapa e paredes
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == MAP_WALL 
		|| map[y][x] == 'F')
		return;
	
	// Marca coletável encontrado
	if (map[y][x] == MAP_COLLECT)
		(*collectibles)++;
	// Marca saída encontrada
	else if (map[y][x] == MAP_EXIT)
		*exit_found = 1;
	
	// Marca posição como visitada
	map[y][x] = 'F';
	
	// Recursivamente verifica todas as direções
	ft_flood_fill(map, x + 1, y, collectibles, exit_found);
	ft_flood_fill(map, x - 1, y, collectibles, exit_found);
	ft_flood_fill(map, x, y + 1, collectibles, exit_found);
	ft_flood_fill(map, x, y - 1, collectibles, exit_found);
}

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

void	ft_check_collectibles_surroundings(t_game *game)
{
	int		x;
	int		y;
	int		accessible_sides;
	char	element_type[20];

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_COLLECT ||
				game->map.grid[y][x] == MAP_EXIT ||
				game->map.grid[y][x] == MAP_PLAYER)
			{
				accessible_sides = 0;
				
				// Verifica os quatro lados do elemento
				if ((y > 0 && game->map.grid[y - 1][x] != MAP_WALL)
					|| (y > 0 && game->map.grid[y - 1][x] != MAP_EXIT))
					accessible_sides++;
				if ((y < game->map.height - 1 && game->map.grid[y + 1][x] != MAP_WALL)
					|| (y < game->map.height - 1 && game->map.grid[y + 1][x] != MAP_EXIT))
					accessible_sides++;
				if ((x > 0 && game->map.grid[y][x - 1] != MAP_WALL)
					|| (x > 0 && game->map.grid[y][x - 1] != MAP_EXIT))
					accessible_sides++;
				if ((x < game->map.width - 1 && game->map.grid[y][x + 1] != MAP_WALL)
					|| (x < game->map.width - 1 && game->map.grid[y][x + 1] != MAP_EXIT))
					accessible_sides++;
				
				// Define o tipo de elemento para a mensagem de erro
				if (game->map.grid[y][x] == MAP_COLLECT)
					ft_strlcpy(element_type, "Collectible", 20);
				else if (game->map.grid[y][x] == MAP_EXIT)
					ft_strlcpy(element_type, "Exit", 20);
				else
					ft_strlcpy(element_type, "Player", 20);
				
				// Verifica se o elemento está cercado
				if (accessible_sides == 0)
				{
					ft_error_message(element_type);
				}
			}
			x++;
		}
		y++;
	}
}
