/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:54:57 by maandria          #+#    #+#             */
/*   Updated: 2025/03/24 14:52:46 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_ray	op_quadrique_value_sp(t_coord px, t_prog *prog, t_object *sp)
{
	t_ray		result;
	t_coord		v;
	t_coord		rso;
	t_coord		rs;

	rs = *(sp->coord);
	v = orientation_ray(px, prog);
	rso = op_vector_addition(px, op_vect_n_lamda(-1, rs));
	result.ro = px;
	result.rso = rso;
	result.v = v;
	return (result);
}

t_quadric	op_values_polynome(t_ray ray, double rayon)
{
	t_quadric	result;

	result.A = op_dot_prod(ray.v, ray.v);
	result.B = 2 * op_dot_prod(ray.rso, ray.v);
	result.C = op_dot_prod(ray.rso, ray.rso) - (rayon * rayon);
	return (result);
}

double	inter_sp(t_ray *ray, t_object *sp)
{
	double		t;
	double		radius;
	t_quadric	value;

	t = INFINITY;
	if (!sp)
		return (t);
	radius = (sp->size[0] / 2);
	value = op_values_polynome(*ray, radius);
	t = op_solution_quad(value.A, value.B, value.C);
	return (t);
}
