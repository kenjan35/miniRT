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

t_ray	op_quadrique_value_sp(t_coord px, t_prog *prog)
{
	t_ray	result;
	t_coord	v;
	t_coord	rso;
	t_coord	rs;
	t_prog	*tmp;

	tmp = prog;
	rs = take_coord_id(tmp, "sp");
	v = orientation_ray(px, tmp);
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

double	inter_sp(t_prog *prog, t_ray ray)
{
	double		t;
	double		rayon;
	t_object	*sp;
	t_prog		*tmp;
	t_quadric	value;

	tmp = prog;
	t = 0.0;
	sp = find_id(tmp, "sp");
	rayon = (sp->size[0] / 2);
	value = op_values_polynome(ray, rayon);
	t = op_solution_quad(value.A, value.B, value.C);
	return (t);
}

void	put_sp(t_prog *prog, double *xy, t_viewport view, t_object **allob)
{
	t_coord		px;
	t_coord		rt;
	t_ray		ray;
	double		time;
	int			i;

	i = 0;
	px = mr_pixel_position(prog, view, xy);
	while (!ft_memcmp((char *)*allob[i]->id, "sp", 2))
	{
		printf("tonga put_sp\n");
		// color = *allob[i]->color;
		ray = op_quadrique_value_sp(px, prog);
		time = inter_sp(prog, ray);
		rt = ray_launch(px, ray.v, time);
		printf("main ray : x = %f, y = %f, z = %f\n", ray.v.x, ray.v.y, ray.v.z);
		if (time > 0)
			mlx_pixel_put(prog->mlx, prog->mlx_win, xy[0], xy[1], 0xff0000);
		i++;
	}
}
