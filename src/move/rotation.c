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

void	rotate_x(t_object *obj, double angle)
{
	double	y;
	double	z;

	y = obj->orient->or_y * cos(angle) - obj->orient->or_z * sin(angle);
	z = obj->orient->or_y * sin(angle) + obj->orient->or_z * cos(angle);
	obj->orient->or_y = y;
	obj->orient->or_z = z;
}

void	rotate_y(t_object *obj, double angle)
{
	double	x;
	double	z;

	x = obj->orient->or_x * cos(angle) + obj->orient->or_z * sin(angle);
	z = -(obj->orient->or_x * sin(angle)) + obj->orient->or_z * cos(angle);
	obj->orient->or_x = x;
	obj->orient->or_z = z;
}

void	rotate_z(t_object *obj, double angle)
{
	double	x;
	double	y;

	x = obj->orient->or_x * cos(angle) - obj->orient->or_y * sin(angle);
	y = obj->orient->or_x * sin(angle) + obj->orient->or_y * cos(angle);
	obj->orient->or_x = x;
	obj->orient->or_y = y;
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
