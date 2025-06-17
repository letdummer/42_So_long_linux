make re
./so_long ./maps/valid/map1.ber 

# valgrind --leak-check=full --show-leak-kinds=all ./so_long maps/your_map.ber

# cc -g -Wall -Wextra -Werror -I/usr/include/X11 -Iincludes \
# src/*.c \
# -L./libft -lft \
# -L./minilibx-linux -lmlx -lXext -lX11 \
#-o so_long