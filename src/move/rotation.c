/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:44:39 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/01 11:08:15 by atolojan         ###   ########.fr       */
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

void	rotate_x(t_object *obj, double angle)
{
	double	y;
	double	z;
	t_coord	to_coord;
	double	norm;

	y = obj->orient->or_y * cos(angle) - obj->orient->or_z * sin(angle);
	z = obj->orient->or_y * sin(angle) + obj->orient->or_z * cos(angle);
	obj->orient->or_y = y;
	obj->orient->or_z = z;
	to_coord = orient2coord(obj->orient);
	norm = op_norm(to_coord);
	obj->orient->or_x /= norm;
	obj->orient->or_y /= norm;
	obj->orient->or_z /= norm;
}

void	rotate_y(t_object *obj, double angle)
{
	double	x;
	double	z;
	t_coord	to_coord;
	double	norm;

	x = obj->orient->or_x * cos(angle) + obj->orient->or_z * sin(angle);
	z = -(obj->orient->or_x * sin(angle)) + obj->orient->or_z * cos(angle);
	obj->orient->or_x = x;
	obj->orient->or_z = z;
	to_coord = orient2coord(obj->orient);
	norm = op_norm(to_coord);
	obj->orient->or_x /= norm;
	obj->orient->or_y /= norm;
	obj->orient->or_z /= norm;
}

void	rotate_z(t_object *obj, double angle)
{
	double	x;
	double	y;
	t_coord	to_coord;
	double	norm;

	x = obj->orient->or_x * cos(angle) - obj->orient->or_y * sin(angle);
	y = obj->orient->or_x * sin(angle) + obj->orient->or_y * cos(angle);
	obj->orient->or_x = x;
	obj->orient->or_y = y;
	to_coord = orient2coord(obj->orient);
	norm = op_norm(to_coord);
	obj->orient->or_x /= norm;
	obj->orient->or_y /= norm;
	obj->orient->or_z /= norm;
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
		prog->pixel = 1;
	mlx_destroy_image(prog->mlx, prog->img);
	set_render(prog);
	return (1);
}
