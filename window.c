/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ma <abdel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:32:00 by abdel-ma          #+#    #+#             */
/*   Updated: 2024/06/26 09:40:31 by abdel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_win(t_win *win)
{
    mlx_destroy_window(win->mlx, win->win);
    exit(0);
}

int key_hook(int keycode, t_win *win)
{
    if (keycode == 53) // ESC key
        close_win(win);
    printf("Key pressed: %d\n", keycode);
    return (0);
}

void create_background(t_win *win)
{
    int x, y;

    x = 0;
    while (x < WIN_WIDTH)
    {
        y = 0;
        while (y < WIN_HEIGHT)
        {
            mlx_put_image_to_window(win->mlx, win->win, win->background, x, y);
            y += win->img_height;
        }
        x += win->img_width;
    }
}

void check_image(void *img, const char *filename)
{
    if (!img)
    {
        fprintf(stderr, "Error loading image: %s\n", filename);
        perror("Error detail");
        exit(1);
    }
}

void init_window(t_win *win)
{
    win->mlx = mlx_init();
    if (!win->mlx)
    {
        fprintf(stderr, "Error initializing MLX\n");
        exit(1);
    }

    win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
    if (!win->win)
    {
        fprintf(stderr, "Error creating window\n");
        exit(1);
    }
}

void load_images(t_win *win)
{
    win->background = mlx_xpm_file_to_image(win->mlx, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/background.xpm", &win->img_width, &win->img_height);
    check_image(win->background, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/background.xpm");

    win->imag = mlx_xpm_file_to_image(win->mlx, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/character.xpm", &win->img_width, &win->img_height);
    check_image(win->imag, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/character.xpm");

    win->collectible = mlx_xpm_file_to_image(win->mlx, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/collectible.xpm", &win->img_width, &win->img_height);
    check_image(win->collectible, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/collectible.xpm");

    win->exit = mlx_xpm_file_to_image(win->mlx, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/exit.xpm", &win->img_width, &win->img_height);
    check_image(win->exit, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/exit.xpm");

    win->wall = mlx_xpm_file_to_image(win->mlx, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/wall.xpm", &win->img_width, &win->img_height);
    check_image(win->wall, "/nfs/homes/abdel-ma/Desktop/my_so_long/images/wall.xpm");
}

void check_args(t_win *win, int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Error\nInvalid number of arguments\n");
        exit(0);
    }
    size_t len = ft_strlen(argv[1]);
    if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
    {
        ft_printf("Error\nInvalid number of arguments\n");
        exit(0);
    }
}

int collectible_counter(t_win *win)
{
    int x;
    int y;
    int c;

    x = 0;
    y = 0;
    c = 0;
    while (x < win->line)
    {
        while (y < win->col)
        {
            if (win->map[x][y] == 'c')
            {
                c++;
            }
            y++;
        }
        y = 0;
        x++;
    }
    return (c);
}

int line_size(t_win *win, int fd)
{
    char *c;
    int x;

    x = 0;
    (void)win;
    while (1)
    {
        c = get_next_line(fd);
        if (!c)
        break;
        x++;
        free(c);
    }
    if (x == 0)
    {
        ft_printf("Error\nThe file is empty or not exist");
        exit(0);
    }
    return (x);
}

int col_size(t_win *win, int fd)
{
    char *c;
    int y;
    int tmp;

    (void)win;
    c = get_next_line(fd);
    y = ft_strlen(c) - 1;
    tmp = y;
    free (c);
    if (fd < 0)
    {
        ft_printf("err\n fd is empty\n");
        exit(0);
    }
    while (1)
    {
        c = get_next_line(fd);
        if (!c);
            break;
        y = ft_strlen(c) - 1;
        if (tmp != y)
        return (-1);
        free(c);
    }
    return (y);
}

void	player_position(t_win *win)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < win->line)
	{
		while (y < win->col)
		{
			if (win->map[x][y] == 'P')
			{
				win->player_x = y;
				win->player_y = x;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	free_img(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img.exit);
	if (win->img.collectible)
		mlx_destroy_image(win->mlx, win->img.collectible);
	if (win->img.character)
		mlx_destroy_image(win->mlx, win->img.character);
	if (win->img.background)
		mlx_destroy_image(win->mlx, win->img.background);
	if (win->img.wall)
		mlx_destroy_image(win->mlx, win->img.wall);
	mlx_destroy_display(win->mlx);
	free_map(win);
	free(win->mlx);
	exit(0);
}

void    put_images(t_win *win)
{
    int len;
    len = 64;
    win->img.wall = mlx_xpm_file_to_image(win->mlx, WALL, &len, &len);
    win->img.character = mlx_xpm_file_to_image(win->mlx, CHARACTER, &len, &len);
    win->img.collectible = mlx_xpm_file_to_image(win->mlx, COLLECTIBLE, &len, &len);
    win->img.background = mlx_xpm_file_to_image(win->mlx, BACKGROUND, &len, &len);
    win->img.exit = mlx_xpm_file_to_image(win->mlx, EXIT, &len, &len);
    }