/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:54:27 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/08 21:17:08 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.c"

void	free_map_fill(t_win *win)
{
	int	i;

	i = 0;
	while (win->map_fill[i])
	{
		free(win->map_fill[i]);
		i++;
	}
	free(win->map_fill);
}

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	free_img(win);
	free_map(win);
	exit (0);
}