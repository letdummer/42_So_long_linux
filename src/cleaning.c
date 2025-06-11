/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:11:09 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/09 14:26:17 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error_message(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

void	gnl_clear(int fd)
{
	char	*temp;

	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
	}
}

void	ft_free_images(t_game *game)
{
	if (!game || !game->mlx_connect)
		return ;
	if (game->img.floor)
		mlx_destroy_image(game->mlx_connect, game->img.floor);
	if (game->img.collect)
		mlx_destroy_image(game->mlx_connect, game->img.collect);
	if (game->img.exit)
		mlx_destroy_image(game->mlx_connect, game->img.exit);
	if (game->img.player_up_1)
		mlx_destroy_image(game->mlx_connect, game->img.player_up_1);
	if (game->img.player_up_2)
		mlx_destroy_image(game->mlx_connect, game->img.player_up_2);
	if (game->img.player_down_1)
		mlx_destroy_image(game->mlx_connect, game->img.player_down_1);
	if (game->img.player_down_2)
		mlx_destroy_image(game->mlx_connect, game->img.player_down_2);
	if (game->img.player_left_1)
		mlx_destroy_image(game->mlx_connect, game->img.player_left_1);
	if (game->img.player_left_2)
		mlx_destroy_image(game->mlx_connect, game->img.player_left_2);
	if (game->img.player_right_1)
		mlx_destroy_image(game->mlx_connect, game->img.player_right_1);
	if (game->img.player_right_2)
		mlx_destroy_image(game->mlx_connect, game->img.player_right_2);
}

int	handle_close(t_game *game)
{
	int	i;

	if (!game)
		exit (0);
	ft_free_images(game);
	if (game->mlx_wind && game->mlx_connect)
		mlx_destroy_window(game->mlx_connect, game->mlx_wind);
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	if (game->mlx_connect)
		free(game->mlx_connect);
	free(game);
	exit(0);
	return (0);
}
