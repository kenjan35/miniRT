/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:41 by maandria          #+#    #+#             */
/*   Updated: 2025/03/19 16:27:31 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	op_vector_substraction(t_coord u, t_coord v)
{
	t_coord	result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return (result);
}

t_coord	get_extremity_upper(t_object *obj)
{
	t_coord	x;
	double	height;

	height = obj->size[1];
	x.x = obj->coord->x + height / 2 * obj->orient->or_x;
	x.y = obj->coord->y + height / 2 * obj->orient->or_y;
	x.z = obj->coord->z + height / 2 * obj->orient->or_z;
	return (x);
}

int	get_extremity(t_coord *px, t_coord *rt, t_object *cy)
{
	t_coord	x;
	t_coord	axis;
	double	norm;
	double	height;
	t_coord	*center;

	(void) px;
	center = cy->coord;
	height = cy->size[1];
	axis = orient2coord(cy->orient);
	axis.x /= op_norm(axis);
	axis.y /= op_norm(axis);
	axis.z /= op_norm(axis);
	x = op_vector_substraction(*rt, *center);
	norm = op_dot_prod(x, axis);
	if (-(height / 2) <= norm && norm <= (height / 2))
		return (1);
	return (0);
}

t_quadric	op_values_polynome_cy(t_coord *px, t_coord *axis_cy, t_coord *dir, t_object *cy)
{
	t_quadric	result;
	t_coord		c;
	t_coord		x;
	double		ray;
	double		tmp;

	tmp = 0;
	ray = cy->size[0] / 2;
	c = get_extremity_upper(cy);
	x = op_vector_substraction(*px, c);
	tmp = op_dot_prod(*dir, *dir);
	result.A = tmp - (op_dot_prod(*dir, *axis_cy) * op_dot_prod(*dir, *axis_cy));
	tmp = op_dot_prod(*dir, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.B = 2 * (op_dot_prod(*dir, x) - tmp);
	tmp = op_dot_prod(x, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.C = op_dot_prod(x, x) - tmp - ray * ray;
	return (result);
}

t_ray	op_quadrique_value_cy(t_coord px, t_prog *prog, t_object *cy)
{
	t_ray		result;
	t_coord		rs;
	t_coord		coord;
	t_coord		vector;

	coord = *(cy->coord);
	vector = orientation_ray(px, prog);
	rs = orient2coord(cy->orient);
	result.v = vector;
	result.ro = px;
	result.rso = op_vector_addition(px, op_vect_n_lamda(-1, rs));
	return (result);
}

double	inter_caps_up(t_coord *c_caps, t_object *cy, t_ray *ray)
{
	t_coord	cy_axis;
	double	height;
	double	t;

	t = 0;
	cy_axis = orient2coord(cy->orient);
	height = cy->size[1] / 2;
	c_caps->x = (cy->coord->x + height * cy_axis.x);
	c_caps->y = (cy->coord->y + height * cy_axis.y);
	c_caps->z = (cy->coord->z + height * cy_axis.z);
	t = vector_numer(cy_axis, *c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	return (t);
}

double	inter_caps_low(t_coord *c_caps, t_object *cy, t_ray *ray)
{
	t_coord	cy_axis;
	double	height;
	double	t;

	t = 0;
	cy_axis = orient2coord(cy->orient);
	height = cy->size[1] / 2;
	c_caps->x = (cy->coord->x - height * cy_axis.x);
	c_caps->y = (cy->coord->y - height * cy_axis.y);
	c_caps->z = (cy->coord->z - height * cy_axis.z);
	t = vector_numer(cy_axis, *c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	return (t);
}

double	inter_cy_caps(t_object *cy, t_ray *ray)
{
	double	t;
	double	t2;
	t_coord	c_caps;
	t_coord	ray_caps;
	t_coord	tmp[2];

	t = inter_caps_up(&c_caps, cy, ray);
	ray_caps = ray_launch(ray->ro, ray->v, t);
	tmp[0] = op_vector_substraction(ray_caps, c_caps);
	t2 = inter_caps_low(&c_caps, cy, ray);
	ray_caps = ray_launch(ray->ro, ray->v, t2);
	tmp[1] = op_vector_substraction(ray_caps, c_caps);
	if (op_norm(tmp[0]) <= (cy->size[0] / 2) + pow(10, -6) && t < t2)
		return (t);
	else if (op_norm(tmp[1]) <= (cy->size[0] / 2) + pow(10, -6) && t2 < t)
		return (t2);
	return (0);
}

double	inter_cy(t_ray *ray, t_object *cy)
{
	double		t;
	t_coord		axis_cy;
	t_quadric	value;

	t = INFINITY;
	axis_cy = orient2coord(cy->orient);
	value = op_values_polynome_cy(&(ray->ro), &axis_cy, &(ray->v), cy);
	t = op_solution_quad(value.A, value.B, value.C);
	return (t);
}
