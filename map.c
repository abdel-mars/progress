/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:18:39 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 09:55:28 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_win *win)
{
	int	i;

	i = 0;
	while (win->map[i])
	{
		free(win->map[i]);
		i++;
	}
	free(win->map);
}

void ft_exit(char *s, t_win *win)
{
	ft_printf("Error\nSomething is wrong!\n%s\n", s);
	if (win->map[0])
		free_map(win);
	exit(0);
}

void	get_maps(t_win *win, int fd)
{
	int		i;
	char	*c;
	int		y;

	i = 0;
	y = win->line + 1;
	win->map = malloc(sizeof(char *) * y);
	if (!win->map)
		ft_exit("Error\n", win);
	while (i < y)
	{
		c = get_next_line(fd);
		win->map[i] = ft_strtrim(c, "\n");
		i++;
		free(c);
	}
}

static void	check_char(t_win *Win, char c, int line, int col)
{
	if (c == 'C')
		Win->score++;
	else if (c == 'E')
		Win->exit++;
	else if (c == 'P')
	{
		Win->player++;
		Win->player_x = col;
		Win->player_y = line;
	}
	else if (c == '1' || c == '0')
		return ;
	else
		ft_exit("Error\nInvalid characters", Win);
}

void	check_map(t_win *win)
{
	int	line;
	int	col;

	line = 0;
	while (win->map[line])
	{
		col = 0;
		while (win->map[line][col])
		{
			check_char(win, win->map[line][col], line, col);
			col++;
		}
		line++;
	}
	if (win->score == 0)
		ft_exit("Error\nThere's no collectible", win);
	else if (win->exit == 0)
		ft_exit("Error\nThere's no door", win);
	else if (win->exit > 1)
		ft_exit("Error\nJust one door per map", win);
	else if (win->player == 0)
		ft_exit("Error\nThere's no player", win);
	else if (win->player > 1)
		ft_exit("Error\nJust one player per map", win);
}

static void	ft_walls(t_win *win)
{
	int	i;
	int	c;

	i = 0;
	while (win->map[i])
	{
		c = 0;
		while (win->map[i][c])
		{
			if (win->map[0][c] != '1' || win->map[win->line - 1][c] != '1')
				ft_exit("Error\nThe map is not surrounded by walls", win);
			if (win->map[i][0] != '1' || win->map[i][win->col - 1] != '1')
				ft_exit("Error\nThe map is not surrounded by walls", win);
			c++;
		}
		i++;
	}
}

void	map_path_allocation(t_win *win, int fd)
{
	int		i;
	char	*c;
	int		y;

	i = 0;
	y = win->line + 1;
	win->map_fill = (char **)malloc(sizeof(char *) * y);
	if (!win->map_fill)
		free_img(win);
	while (i < y)
	{
		c = get_next_line(fd);
		win->map_fill[i] = ft_strtrim(c, "\n");
		i++;
		free(c);
	}
}


void	valid_map(t_win *win)
{
	int	col;
	int	line;
	int	size;

	col = 0;
	line = 0;
	size = ft_strlen(win->map[0]);
	while (win->map[line] != 0)
	{
		col = ft_strlen(win->map[line]);
		if (col != size)
			ft_exit("Error\nYour map is not rectangular", win);
		line++;
	}
	ft_walls(win);
}

bool	fill(t_win *win, char c, int line, int col)
{
	static bool		exit = false;
	static int		cols = 0;

	if (line < 0 || col < 0 || line >= win->line || col >= win->col)
		return (false);
	else if (win->map_fill[line][col] == 'X')
		return (false);
	else if (win->map_fill[line][col] == '1')
		return (false);
	else if (win->map_fill[line][col] == 'E')
		exit = true;
	if (win->map_fill[line][col] == 'C')
		cols++;
	win->map_fill[line][col] = 'X';
	fill(win, c, line + 1, col);
	fill(win, c, line, col + 1);
	fill(win, c, line - 1, col);
	fill(win, c, line, col - 1);
	return (cols == win->score && exit);
}

int	floodfill(t_win *win)
{
	char	b;
	int		line;
	int		col;
	bool	valid;

	b = win->map_fill[win->player_y][win->player_x];
	line = win->player_y;
	col = win->player_x;
	valid = fill(win, b, line, col);
	return (valid);
}

void	valid_path(t_win *win, int fd)
{
	map_path_allocation(win, fd);
	if (!floodfill(win))
	{
		ft_printf ("Error\nInvalid path to on the map\n");
		free_img(win);
		close(fd);
	}
	free_map_fill(win);	
}

void init_validations(t_win *win, int fd)
{
    ft_printf("init validation...\n");
    check_map(win);
    valid_map(win);
    valid_path(win, fd);
}
