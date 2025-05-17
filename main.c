/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 20:56:49 by maandria         ###   ########.fr       */
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

int	main(int ac, char *av[])
{
	t_prog	prog;

	if (!av[1] || ac == 1)
	{
		print_error(3, NULL);
		exit(1);
	}
	prog = checker(av);
	prog.shapes = all_shape(&prog);
	if (prog.shapes == NULL)
		return (1);
	set_render(&prog);
	mlx_mouse_hook(prog.mlx_win, get_object, &prog);
	mlx_key_hook(prog.mlx_win, translate, &prog);
	mlx_hook(prog.mlx_win, 17, 1L << 0, quit_window, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 0, key_close, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
