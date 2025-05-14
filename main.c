/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/01 11:19:06 by atolojan         ###   ########.fr       */
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
	while (prog->obj)
	{
		object = (t_object *) prog->obj->content;
		if (ft_strncmp(object->id, id, ft_strlen(id)) == 0)
		{
			prog->obj = tmp_obj;
			return (object);
		}
		else
		{
			prog->obj = prog->obj->next;
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
	tmp_obj = tmp->shapes;
	while (tmp->shapes)
	{
		object = tmp->shapes->content;
		printf("Id : %s , num : %d\n", object->id, object->num);
		tmp->shapes = tmp->shapes->next;
	}
	tmp->shapes = tmp_obj;
}

int	gradient(int y, t_color *colors)
{
	int	color;
	int	r;
	int	g;
	int	b;
	r = ((int)(colors->red) - (y * 255) / WIN_WIDTH) % 255;
	g = ((int)(colors->green) - (y * 255) / WIN_WIDTH) % 255;
	b = ((int)(colors->blue) - (y * 255) / WIN_WIDTH) % 255;
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

	if (!av[1] || ac == 1)
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
	set_data(av[1], &(prog.obj), &prog);
	if (check_element(&(prog.obj)) == 0)
	{
		ft_putstr_fd(RED "Error :\nWrong number of element\n" RESET, 2);
		exit(1);
	}
	prog.shapes = all_shape(&prog);
	if (prog.shapes == NULL)
		return (1);
	set_render(&prog);
	check_list(&prog);
	mlx_mouse_hook(prog.mlx_win, get_object, &prog);
	mlx_key_hook(prog.mlx_win, translate, &prog);
	mlx_hook(prog.mlx_win, 17, 1L << 0, quit_window, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 0, key_close, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
