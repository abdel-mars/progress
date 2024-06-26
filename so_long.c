/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:56:00 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 09:54:09 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void start_map(t_win *win)
{
    win->player_x = 0;
	win->player_y = 0;
	win->player_on_thedoor = 0;
	win->exit = 0;
	win->player = 0;
	win->line = 0;
	win->col = 0;
	win->end_game = 0;
	win->move = 1;
}
int main(int argc, char **argv)
{
    t_win win;
    int   fd;
    int   fd_x;
    int   fd_y;
    int   fd_map;
    
    fd_x = open(argv[1], O_RDONLY);
    fd_y = open(argv[1], O_RDONLY);
    fd_map = open(argv[1], O_RDONLY);
    check_args(&win, argc, argv);
    start_map(&win);
    win.score = collectible_counter(&win);
    win.line = line_size(&win, fd_y);
    win.col = col_size(&win, fd_x);
    fd = open(argv[1], O_RDONLY);
    get_maps(&win, fd);
    init_validations(&win, fd_map);
    if (win.col == -1)
        ft_exit("EEError\n", &win);
    close(fd_x);
    close(fd_y);
    close(fd);
    close(fd_map);
    player_position(&win);
    start_game(&win);
    
}
