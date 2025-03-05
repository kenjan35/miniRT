/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/05 14:59:48 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

void	check_file(char *av)
{
	int		sub_len;

	sub_len = (int)ft_strlen(av);
	if (av[sub_len - 1] != 't' || av[sub_len -2] != 'r' || \
		av[sub_len - 3] != '.' || !av[sub_len - 4] || \
		!ft_isalnum(av[sub_len - 4]))
	{
		print_error(3, NULL);
		exit(1);
	}
}

t_object	*find_id(t_prog *prog, char *id)
{
	t_prog		*tmp;
	t_object	*object;

	tmp = prog;
	object = tmp->obj->content;
	while (tmp->obj->next)
	{
		if (ft_strncmp(object->id, id, ft_strlen(id)) == 0)
			return (object);
		else
		{
			tmp->obj = tmp->obj->next;
			object = tmp->obj->content;
		}
	}
	if (ft_strncmp(object->id, id, ft_strlen(id)) == 0)
		return (object);
	else
		return (NULL);
}

void	check_list(t_prog *prog)
{
	t_prog		*tmp;
	t_object	*object;

	tmp = prog;
	while (tmp->obj->next)
	{
			object = tmp->obj->content;
			printf("Id : %s\n", object->id);
			tmp->obj = tmp->obj->next;
	}
	object = tmp->obj->content;
	printf("Id : %s\n", object->id);
}

int	gradient(int y)
{
	int	color;
	int	r;
	int	g;
	int	b;
	r = 255 - (y * 255) / WIN_WIDTH;
	g = 255 - (y * 255) / WIN_WIDTH;
	b = 255;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_gradient(t_prog *prog)
{
	int		*data;
	int		color;
	int		x;
	int		y;
	void	*img;

	y = 0;
	img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	data = (int *)mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
	while (y < WIN_WIDTH)
	{
		color = gradient(y);
		x = 0;
		while (x < WIN_LENGTH)
		{
			data[y * WIN_LENGTH + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, img, 0, 0);
	mlx_destroy_image(prog->mlx, img);
}

int	main(int ac, char *av[])
{
	t_prog	prog;

	(void)ac;
	if (!av[1])
	{
		print_error(3, NULL);
		exit(1);
	}
	check_file(av[1]);
	if (init_prog(&prog) == 0)
	{
		ft_putstr_fd(RED "Error :\nRendering problem\n" RESET, 2);
		exit(1);
	}
	set_data(av[1], &(prog.obj));
	if (check_element(&(prog.obj)) == 0)
	{
		ft_putstr_fd(RED "Error :\nWrong number of element\n" RESET, 2);
		exit(1);
	}

	/*********** Debut Test execution ***********/
	t_viewport view;

	view = mr_camera_init(1, &prog);
	printf(CYAN "Camera viewport : " RESET);
	printf("length = %f\twidth = %f\n", view.length, view.width);
	draw_gradient(&prog);
	t_coord	px_position;
	float	y = 0;
	while (y < (WIN_WIDTH))
	{
		float	x = 0;
		while (x < (WIN_LENGTH))
		{
			px_position = mr_pixel_position(&prog, view, x, y);
			printf("\nPosition : x = %f , y = %f , z = %f\n\n", px_position.x, px_position.y, px_position.z);
			if (x == (WIN_LENGTH / 2) && y == (WIN_WIDTH / 2))
			{
				int i = 0;
				while (i < 5)
				{
					int	j = 0;
					while (j < 5)
					{
						mlx_pixel_put(prog.mlx, prog.mlx_win, x + j, y + i, 0xff0000);
						j++;
					}
					i++;
				}
			}
			// if (px_position.y < 0 || px_position.z < 0)
			// 	mlx_pixel_put(prog.mlx, prog.mlx_win, x + (-1 * px_position.y), y + (-1 * px_position.z), 0xffff00);
			// else
			mlx_pixel_put(prog.mlx, prog.mlx_win, x + px_position.y, y + px_position.z, 0xffffff);
			x++;
		}
		x = 0;
		y++;
	}
	/*********** Fin Test execution ***********/

	mlx_hook(prog.mlx_win, 17, 1L << 0, quit_window, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 0, key_close, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
