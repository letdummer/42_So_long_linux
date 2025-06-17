/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:15:38 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/17 16:49:08 by ldummer-         ###   ########.fr       */
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
		ft_error_message(game, "Error while geting map dimensions.");
	str = get_next_line(fd);
	if (!(str))
		ft_error_message(game, "Empty file.");
	game->map.width = ft_strlen(str) - 1;
	gnl_clear(fd);
	close(fd);
	game->map.height = ft_count_lines(game, map_path);
	if (game->map.height < 3)
		ft_error_message(game, "Map is too small.");
	free(str);
}

int	ft_count_lines(t_game *game, char *map_path)
{
	int		fd;
	int		line_length;
	char	*str;

	line_length = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message(game, "Error in count_lines.");
	str = get_next_line(fd);
	if (!str)
		ft_error_message(game, "Empty file.");
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
		ft_error_message(game, "Memory allocation failed");
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[i])
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			ft_error_message(game, "Memory allocation failed");
		}
		i++;
	}
}

void	ft_validate_line(int fd, char *str, t_game *game, int i)
{
	if (!str && i == 0)
		ft_error_message(game, "Empty file.");
	if (!str)
		ft_error_message(game, "Map has fewer lines than expected.");
	if (((int)ft_strlen(str) - (str[ft_strlen(str) - 1] == '\n'))
		!= game->map.width)
	{
		free(str);
		gnl_clear(fd);
		close(fd);
		ft_error_message(game, "Map must be rectangular.");
	}
}

void	ft_fill_map_content(t_game *game, char *map_path)
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message(game, "Error in fill map_content.");
	while (i < game->map.height)
	{
		str = get_next_line(fd);
		ft_validate_line(fd, str, game, i);
		ft_strlcpy(game->map.grid[i], str, game->map.width + 1);
		free(str);
		i++;
	}
	str = get_next_line(fd);
	if (str)
	{
		free(str);
		gnl_clear(fd);
		close(fd);
		ft_error_message(game, "Map has more lines than expected.");
	}
	close(fd);
}
