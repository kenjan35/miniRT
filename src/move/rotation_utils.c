/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:46:56 by maandria          #+#    #+#             */
/*   Updated: 2025/05/16 15:06:50 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
