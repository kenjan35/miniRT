/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:41 by maandria          #+#    #+#             */
/*   Updated: 2025/05/17 19:28:54 by atolojan         ###   ########.fr       */
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

t_quadric	op_values_polynome_cy(t_coord *px, t_coord *axis_cy, \
	t_coord *dir, t_object *cy)
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
	result.a = tmp - (op_dot_prod(*dir, *axis_cy) * \
		op_dot_prod(*dir, *axis_cy));
	tmp = op_dot_prod(*dir, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.b = 2 * (op_dot_prod(*dir, x) - tmp);
	tmp = op_dot_prod(x, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.c = op_dot_prod(x, x) - tmp - ray * ray;
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

double	inter_cy(t_ray *ray, t_object *cy)
{
	double		t;
	t_coord		axis_cy;
	t_quadric	value;

	t = INFINITY;
	axis_cy = orient2coord(cy->orient);
	value = op_values_polynome_cy(&(ray->ro), &axis_cy, &(ray->v), cy);
	t = op_solution_quad(value.a, value.b, value.c);
	return (t);
}
