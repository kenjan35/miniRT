/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:44:39 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/16 14:47:49 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	roll(t_coord vec, t_coord axis, double angle)
{
	t_coord	res1;
	t_coord	res2;
	t_coord	res3;
	t_coord	result;

	res1 = op_vect_n_lamda(angle, vec);
	res2 = op_vect_n_lamda(sin(angle), op_cross_prod(axis, vec));
	res3 = op_vect_n_lamda(op_dot_prod(axis, vec) * (1 - cos(angle)), axis);
	result = op_vector_addition(op_vector_addition(res1, res2), res3);
	return (result);
}

void	set_roll(t_viewport *view, double angle)
{
	t_coord	new_up;
	t_coord	new_right;

	new_up = roll(view->cam.c_up, view->cam.c_forward, angle);
	new_right = roll(view->cam.c_right, view->cam.c_forward, angle);
	view->cam.c_up = new_up;
	view->cam.c_right = new_right;
}

int	rotate(int key, t_prog *prog)
{
	prog->pixel = 2.5;
	if (key == 'd')
		rotate_x(prog->to_move, 0.1);
	else if (key == 'a')
		rotate_x(prog->to_move, -0.1);
	else if (key == 'w')
		rotate_y(prog->to_move, 0.1);
	else if (key == 's')
		rotate_y(prog->to_move, -0.1);
	else if (key == 'e')
		rotate_z(prog->to_move, 0.1);
	else if (key == 'q')
		rotate_z(prog->to_move, -0.1);
	else
		return (resize(key, prog));
	mlx_destroy_image(prog->mlx, prog->img);
	set_render(prog);
	return (1);
}
