/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/02/12 16:21:24 by maandria         ###   ########.fr       */
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
	t_viewport view;

	view = mr_camera_init(1, &prog);
	printf(CYAN "Camera viewpoint : " RESET);
	printf("length = %f\twidth = %f\n", view.length, view.width);
	t_coord	px_position;
	int	x = 0;
	int	y = 0;
	while (y < (int)WIN_LENGTH)
	{
		while (x < (int)WIN_WIDTH)
		{
			px_position = mr_pixel_position(&prog, view, x, y);
			printf("Position : x = %f , y = %f , z = %f\n\n", px_position.x, px_position.y, px_position.z);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_hook(prog.mlx_win, 17, 1L << 0, quit_window, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
