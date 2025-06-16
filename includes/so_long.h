/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:17:23 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/16 23:58:29 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// LIBRARIES
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h> 
# include "../minilibx-linux/mlx.h"
# include "../libft/libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include "../libft/get_next_line/get_next_line.h"

#include <X11/keysym.h>				//descomentar para usar no linux
//# include <Carbon/Carbon.h>			// Include for event handling on macOS

# define TILE_SIZE 64
# define WIND_WIDTH 1920
# define WIND_HEIGHT 1080
# define HUD_HEIGHT 64
# define HUD_COLOR 0x282828
# define TEXT_COLOR 0xFFFFFF

// COLORS
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define END_COLOR "\033[0;39m"

// key codes for linux
# define KEY_ESC  			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364

//# define KEY_Q				113

// map element definition
# define MAP_WALL		'1'
# define MAP_FLOOR		'0'
# define MAP_COLLECT	'C'
# define MAP_EXIT		'E'
# define MAP_PLAYER		'P'

# define WALL_TOP_LEFT "assets/walls/tile_0_0.xpm"
# define WALL_TOP_RIGHT "assets/walls/tile_0_2.xpm"
# define WALL_BOTTOM_LEFT "assets/walls/tile_2_0.xpm"
# define WALL_BOTTOM_RIGHT "assets/walls/tile_2_2.xpm"
# define WALL_LEFT "assets/walls/tile_1_0.xpm"
# define WALL_RIGHT "assets/walls/tile_1_2.xpm"
# define WALL_TOP "assets/walls/tile_0_1.xpm"
# define WALL_BOTTOM "assets/walls/tile_2_1.xpm"
# define FLOOR "assets/walls/tile_1_1.xpm"

# define WALL "assets/walls/wall_bush.xpm"
# define COLLECTIBLE "assets/collectible.xpm"
# define EXIT "assets/exit.xpm"
# define EXIT_OPEN "assets/exit_open.xpm"

# define PLAYER_UP_1 "assets/player/player_up_1.xpm"
# define PLAYER_UP_2 "assets/player/player_up_2.xpm"
# define PLAYER_DOWN_1 "assets/player/player_down_1.xpm"
# define PLAYER_DOWN_2 "assets/player/player_down_2.xpm"
# define PLAYER_RIGHT_1 "assets/player/player_right_1.xpm"
# define PLAYER_RIGHT_2 "assets/player/player_right_2.xpm"
# define PLAYER_LEFT_1 "assets/player/player_left_1.xpm"
# define PLAYER_LEFT_2 "assets/player/player_left_2.xpm"
# define PLAYER "assets/player/player.xpm"

//	STRUCTURES
typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*collect;
	void	*exit;
	void	*player_up_1;
	void	*player_up_2;
	void	*player_down_1;
	void	*player_down_2;
	void	*player_left_1;
	void	*player_left_2;
	void	*player_right_1;
	void	*player_right_2;
	int		last_direction;
	int		step_count;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		walls;
	int		floor;
	int		collectibles;
	int		player;
	int		exits;
	int		player_pos_x;
	int		player_pos_y;
}	t_map;

typedef struct s_game
{
	void	*mlx_connect;
	void	*mlx_wind;
	t_map	map;
	t_img	img;
	int		collected_items;
	int		moves;
	int		game_over;
	int		win;
}	t_game;

// CLEANING.C
void	ft_error_message(char *message);
void	gnl_clear(int fd);
void	ft_free_images(t_game *game);
int		handle_close(t_game *game);
void	ft_free_temp_map(char **temp_map, int height);

// INIT_MAP.C
void	ft_get_map_dimensions(t_game *game, char *map_path);
int		ft_count_lines(char *map_path);
void	ft_allocate_map_memory(t_game *game);
void	ft_validate_line(char *str, t_game *game, int i);
void	ft_fill_map_content(t_game *game, char *map_path);

// INIT_WINDOW.C
void	ft_init_wind(t_game *game);
int		handle_input(int key, t_game *game);
void	ft_render_hud(t_game *game);

// MOVEMENTS.C
void	ft_update_player_pos(t_game *game, int new_x, int new_y);
void	ft_move_player(t_game *game, int direction);
int		ft_special_tiles(int aux_x, int aux_y, t_game *game);
int		ft_handle_collectables(t_game *game);
int		ft_validate_move(int pos_aux_x, int pos_aux_y, t_game *game);

// RENDER_IMAGES.C
void	ft_map_images(t_game *game);
void	ft_render_wall(t_game *game, int x, int y);
void	render_exit(t_game *game, int x, int y);
void	ft_render_images(t_game *game);
char	*ft_walls_tiles(t_game *game, int x, int y);

// SO_LONG.C
t_game	*ft_init_game(void);
void	ft_map_init(t_game *game, char *map_path);
void	ft_win(t_game *game);

// UPDATE_IMAGES.C
void	ft_update_grid(t_game *game, int x, int y);
void	ft_update_exit(t_game *game, int x, int y);
void	ft_update_wall(t_game *game, int x, int y);
void	ft_load_player_images(t_game *game);
void	*ft_player_images(t_game *game);

// VALIDATE_MAP.C
void	ft_validate_map_extension(char *file);
void	ft_validate_map_content(t_game *game);
void	ft_check_line_content(char *str, int y, t_game *game);
void	ft_check_exit(t_game *game);
void	ft_find_exit_position(t_game *game, int *exit_x, int *exit_y);

// VALIDATE_MAP_PATH.C
void	ft_validate_map_path(t_game *game);
char	**ft_create_temp_map(t_game *game);
void	ft_flood_fill(char **map, int x, int y, int *collectibles, int *exit_found);
void	ft_flood_fill_check(t_game *game);
void	ft_validate_map_borders(t_game *game);

//void	ft_validate_map_walls(t_game *game);
//void	ft_check_collectibles_surroundings(t_game *game);

#endif