/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:25 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/16 23:57:12 by ldummer-         ###   ########.fr       */
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
	ft_validate_map_borders(game);
	ft_flood_fill_check(game);
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

void	ft_check_exit(t_game *game)
{
	int	exit_x;
	int	exit_y;
	int	accessible_sides;

	ft_find_exit_position(game, &exit_x, &exit_y);
	accessible_sides = 0;
	// Verifica os quatro lados da saída
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
		ft_error_message("Exit is completely surrounded by walls!");
}

void ft_find_exit_position(t_game *game, int *exit_x, int *exit_y)
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
				return;
			}
			x++;
		}
		y++;
	}
}

int ft_is_surrounded(t_game *game, int x, int y)
{
	if (y > 0 && (game->map.grid[y-1][x] != MAP_WALL && game->map.grid[y-1][x] != MAP_EXIT))
		return (0);
	if (y < game->map.height-1 && (game->map.grid[y+1][x] != MAP_WALL && game->map.grid[y+1][x] != MAP_EXIT))
		return (0);
	if (x > 0 && (game->map.grid[y][x-1] != MAP_WALL && game->map.grid[y][x-1] != MAP_EXIT))
		return (0);
	if (x < game->map.width-1 && (game->map.grid[y][x+1] != MAP_WALL && game->map.grid[y][x+1] != MAP_EXIT))
		return (0);
	return (1);
}

void ft_check_surrounded_objects(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_PLAYER && ft_is_surrounded(game, x, y))
				ft_error_message("Player is completely surrounded by walls/exits!");
			else if (game->map.grid[y][x] == MAP_COLLECT && ft_is_surrounded(game, x, y))
				ft_error_message("Collectible is completely surrounded by walls/exits!");
			else if (game->map.grid[y][x] == MAP_EXIT && ft_is_surrounded(game, x, y))
				ft_error_message("Exit is completely surrounded by walls/exits!");
			x++;
		}
		y++;
	}
}

void ft_validate_map_borders(t_game *game)
{
	int	x;
	int	y;

	// Verifica primeira e última linha
	y = 0;
	while (y < game->map.height)
	{
		if (y == 0 || y == game->map.height - 1)
		{
			x = 0;
			while (x < game->map.width)
			{
				if (game->map.grid[y][x] != MAP_WALL)
					ft_error_message("Map must be surrounded by walls!");
				x++;
			}
		}
		else // Verifica primeira e última coluna das linhas do meio
		{
			if (game->map.grid[y][0] != MAP_WALL || 
				game->map.grid[y][game->map.width - 1] != MAP_WALL)
				ft_error_message("Map must be surrounded by walls!");
		}
		y++;
	}
}

void ft_flood_fill_check(t_game *game) 
{
	char	**temp_map;
	int		collectibles_found;
	int		exit_found = 0;
	int		i;

	collectibles_found = 0;
	// Create temporary map
	temp_map = (char **)malloc(sizeof(char *) * game->map.height);
	//copy original map
	i = -1;
	while(i++ < game->map.height)
	{
		temp_map[i] = ft_strdup(game->map.grid[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			ft_error_message("Memory allocation failed in flood fill");
		}
	}
	// Start flood fill from player position
	ft_flood_fill(temp_map, game->map.player_pos_x, game->map.player_pos_y,
				&collectibles_found, &exit_found);
	// Check if all collectibles and exit are reachable
	if (collectibles_found != game->map.collectibles || !exit_found)
		ft_error_message("Not all paths are accessible!");
	// Free temporary map
	i = -1;
	while (i++ < game->map.height)
		free(temp_map[i]);
	free(temp_map);
}

void	ft_flood_fill(char **map, int x, int y, int *collec, int *exit_found)
{
	// Verifica limites do mapa e paredes
/* 	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == MAP_WALL 
		|| map[y][x] == 'V')
		return; */
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width
		|| map[y] == NULL)
		return ;
	if (map[y][x] == MAP_WALL || map[y][x] == 'V')
		return ;
	// Marca coletável encontrado
	if (map[y][x] == MAP_COLLECT)
		(*collec)++;
	// Marca saída encontrada
	else if (map[y][x] == MAP_EXIT)
	{
		*exit_found = 1;
		return ;
		// Não continua além da saída!
	}
	// Marca posição como visitada
	map[y][x] = 'V';
	// Recursivamente verifica todas as direções
	ft_flood_fill(map, x + 1, y, collec, exit_found);
	ft_flood_fill(map, x - 1, y, collec, exit_found);
	ft_flood_fill(map, x, y + 1, collec, exit_found);
	ft_flood_fill(map, x, y - 1, collec, exit_found);
}
