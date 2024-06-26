/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:56:05 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 10:33:02 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_C

# include "./mlx/mlx.h"
# include "libft/libft.h"

#include "mlx/mlx.h"
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
# include <stdlib.h>

// Constants
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_NAME "so_long"

#define BACKGROUND "./images/background.xpm"
#define CHARACTER "./images/character.xpm"
#define COLLECTIBLE "./images/collectible.xpm"
#define EXIT "./images/exit.xpm"
#define WALL "./images/wall.xpm"


# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

typedef struct s_img
{
	void	*collectible;
	void	*character;
	void	*background;
	void	*wall;
	void	*exit;
}	t_img;



typedef struct s_win 
{
    t_img img;
    void *mlx;
    void *win;
    void *background;
    void *imag;
    char **map;
    int score;
    void *collectible;
    void *exit;
    void *wall;
    int img_width;
    int img_height;
    int player;
    int player_on_thedoor;
    int player_x;
    int player_y;
    int move;
    int line;
    char **map_fill;
    int col;
    int end_game;
    
    
} t_win;

// Function prototypes
int     close_win(t_win *win);
int     key_hook(int keycode, t_win *win);
void    create_background(t_win *win);
void    check_image(void *img, const char *filename);
void    init_window(t_win *win);
void    load_images(t_win *win);
void    check_args(t_win *win, int argc, char **argv);
int collectible_counter(t_win *win);
int line_size(t_win *win, int fd);
void	get_maps(t_win *win, int fd);
void	free_img(t_win *win);
void	player_position(t_win *win);
int col_size(t_win *win, int fd);
int line_size(t_win *win, int fd);
int collectible_counter(t_win *win);
void check_args(t_win *win, int argc, char **argv);
void	start_game(t_win *win);
int	key_handler(int keycode, t_win *win);
void init_validations(t_win *win, int fd);
void	valid_path(t_win *win, int fd);
int	floodfill(t_win *win);
bool	fill(t_win *win, char c, int line, int col);
void	valid_map(t_win *win);
void	map_path_allocation(t_win *win, int fd);
static void	ft_walls(t_win *win);
void	check_map(t_win *win);
static void	check_char(t_win *Win, char c, int line, int col);
void ft_exit(char *s, t_win *win);
void	free_map(t_win *win);
int	close_window(t_win *win);
void	free_map_fill(t_win *win);


#endif

