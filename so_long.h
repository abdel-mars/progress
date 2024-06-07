/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:56:05 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/07 22:30:12 by abdel-ma         ###   ########.fr       */
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

// Constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_NAME "so_long"

// Struct definition
typedef struct s_win {
    void *mlx;
    void *win;
    void *background;
    void *img;
    int **map;
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
#endif

