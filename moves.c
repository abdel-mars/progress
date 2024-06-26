/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:10:17 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/08 21:14:44 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_handler(int keycode, t_win *win)
{
	int	col;
	int	line;

	col = win->player_x;
	line = win->player_y;
	if (keycode == A)
		col--;
	else if (keycode == W)
		line--;
	else if (keycode == S)
		line++;
	else if (keycode == D)
		col++;
	else if (keycode == ESC)
		close_window(win);
	if (win->end_game != 1)
		move_player(win, col, line, keycode);
	return (0);
}
