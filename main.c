/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/06 14:40:27 by maandria         ###   ########.fr       */
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
	t_list		*tmp_obj;
	t_object	*object;

	tmp_obj = prog->obj;
	object = prog->obj->content;
	while (prog->obj)
	{
		if (ft_strncmp(object->id, id, ft_strlen(id)) == 0)
		{
			prog->obj = tmp_obj;
			return (object);
		}
		else
		{
			prog->obj = prog->obj->next;
			object = prog->obj->content;
		}
	}
	prog->obj = tmp_obj;
	return (NULL);
}

void	check_list(t_prog *prog)
{
	t_prog		*tmp;
	t_object	*object;
	t_list		*tmp_obj;

	tmp = prog;
	tmp_obj = tmp->obj;
	while (tmp->obj)
	{
			object = tmp->obj->content;
			printf("Id : %s\n", object->id);
			tmp->obj = tmp->obj->next;
	}
	tmp->obj = tmp_obj;
}

int	gradient(int y, t_color *colors)
{
	int	color;
	int	r;
	int	g;
	int	b;
	r = (colors->red - (y * 255) / WIN_WIDTH);
	g = (colors->green - (y * 255) / WIN_WIDTH);
	b = colors->blue;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_gradient(t_prog *prog)
{
	int		*data;
	int		color;
	int		x;
	int		y;
	t_color	c;
	void	*img;

	y = 0;
	c = (t_color){255, 255, 255};
	img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	data = (int *)mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
	while (y < WIN_WIDTH)
	{
		color = gradient(y, &c);
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
	t_viewport	view;
	t_coord		px_position;
	t_coord		rt;
	t_ray		ray;
	float		time;
	t_object	*obj;
	t_color		*color;
	
	check_list(&prog);
	view = mr_camera_init(1, &prog);
	printf(CYAN "Camera viewport : " RESET);
	printf("length = %f\twidth = %f\n", view.length, view.width);
	draw_gradient(&prog);
	obj = find_id(&prog, "sp");
	color = obj->color;
	float	y = 0;
	while (y < (WIN_WIDTH))
	{
		float	x = 0;
		while (x < (WIN_LENGTH))
		{
			px_position = mr_pixel_position(&prog, view, x, y);
			ray = op_quadrique_value_sp(px_position, &prog);
			printf("main ray : x = %f, y = %f, z = %f", ray.v.x, ray.v.y, ray.v.z);
			time = inter_sp(&prog, ray);
			rt = ray_launch(px_position, ray.v, time);
			if (time > 0)
				mlx_pixel_put(prog.mlx, prog.mlx_win, x, y, gradient(y, color));
			if (x == (WIN_LENGTH / 2) && y == (WIN_WIDTH / 2))
				mlx_pixel_put(prog.mlx, prog.mlx_win, x, y, 0xff0000);
			x++;
		}
		x = 0;
		y++;
	}
	/*********** Fin Test execution ***********/
	check_list(&prog);
	mlx_hook(prog.mlx_win, 17, 1L << 0, quit_window, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 0, key_close, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
