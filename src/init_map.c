/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:15:38 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/10 18:51:54 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_get_map_dimensions(t_game *game, char *map_path)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message("Error while reading the map content.");
	str = get_next_line(fd);
	if (!(str))
		ft_error_message("Empty file.");
	game->map.width = ft_strlen(str) - 1;
	gnl_clear(fd);
	close(fd);
	game->map.height = ft_count_lines(map_path);
	if (game->map.height < 3)
		ft_error_message("Map is too small.");
	free(str);
}

int	ft_count_lines(char *map_path)
{
	int		fd;
	int		line_length;
	char	*str;

	line_length = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message("Error while reading the map content.");
	str = get_next_line(fd);
	if (!str)
		ft_error_message("Empty file.");
	while (str)
	{
		line_length++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (line_length);
}

void	ft_allocate_map_memory(t_game *game)
{
	int	i;

	i = 0;
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		ft_error_message("Memory allocation failed");
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[i])
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			ft_error_message("Memory allocation failed");
		}
		i++;
	}
}

void	ft_validate_line(char *str, t_game *game, int i)
{
	if (!str && i == 0)
		ft_error_message("Empty file.");
	if (!str)
		ft_error_message("Map has fewer lines than expected.");
	if (((int)ft_strlen(str) - (str[ft_strlen(str) - 1] == '\n'))
		!= game->map.width)
		ft_error_message("Map must be rectangular.");
}

void	ft_fill_map_content(t_game *game, char *map_path)
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message("Error while reading the map content.");
	while (i < game->map.height)
	{
		str = get_next_line(fd);
		ft_validate_line(str, game, i);
		ft_strlcpy(game->map.grid[i], str, game->map.width + 1);
		free(str);
		i++;
	}
	str = get_next_line(fd);
	if (str)
	{
		free(str);
		ft_error_message("Map has more lines than expected.");
	}
	close(fd);
}
