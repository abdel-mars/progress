/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:43:06 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 09:49:11 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_map(int x, int y, char c, t_win *win)
{
	if (c == '1')
		mlx_put_image_to_window(win->mlx, win->win,
			win->img.wall, x * 64, y * 64);
	if (c == '0')
		mlx_put_image_to_window(win->mlx, win->win,
			win->img.background, x * 64, y * 64);
	if (c == 'P')
		mlx_put_image_to_window(win->mlx, win->win,
			win->img.character, x * 64, y * 64);
	if (c == 'E')
		mlx_put_image_to_window(win->mlx, win->win,
			win->img.exit, x * 64, y * 64);
	if (c == 'C')
		mlx_put_image_to_window(win->mlx, win->win,
			win->img.collectible, x * 64, y * 64);
}

int	render_img(t_win *win)
{
	int	y;
	int	x;

	y = 0;
	while (y < win->line)
	{
		x = 0;
		while (x < win->col)
		{
			put_map(x, y, win->map[y][x], win);
			x++;
		}
		y++;
	}
	return (0);
}
	