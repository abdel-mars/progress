/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:07:38 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 09:42:24 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_game(t_win *win)
{	
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->col * 64,
			win->line * 64, "So_long");
	mlx_hook(win->win, 02, 1L, key_handler, win);
	mlx_hook(win->win, 17, 1L << 17, close_window, win);
	put_images(win);
	render_img(win);
	mlx_loop(win->mlx);
}
