/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:05:36 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/26 11:24:40 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	get_ambient_intensity(t_prog *prog, t_object *sp)
{
	t_object	*obj;
	t_color		ambient;

	obj = find_id(prog, "A");
	ambient.red = sp->color->red * (obj->color->red * obj->size[0]);
	ambient.green = sp->color->green * (obj->color->green * obj->size[0]);
	ambient.blue = sp->color->blue * (obj->color->blue * obj->size[0]);
	return (ambient);
}

double	get_scalar(t_coord *n, t_prog *prog, t_coord *rray)
{
	double		scalar;
	t_object	*light;
	t_coord		light_dir;
	double		norm;

	light = find_id(prog, "L");
	light_dir.x = light->coord->x - rray->x;
	light_dir.y = light->coord->y - rray->y;
	light_dir.z = light->coord->z - rray->z;
	norm = op_norm(light_dir);
	light_dir.x /= norm;
	light_dir.y /= norm;
	light_dir.z /= norm;
	scalar = op_dot_prod(*n, light_dir);
	if (scalar <= 0)
		scalar = 0;
	return (scalar);
}

t_coord	normalize_sphere(t_coord *ro, t_ray *ray, double *time)
{
	t_coord	n;
	double	n_norm;

	(void) time;
	n.x = ro->x - ray->rso.x;
	n.y = ro->y - ray->rso.y;
	n.z = ro->z - ray->rso.z;
	n_norm = op_norm(n);
	n.x /= n_norm;
	n.y /= n_norm;
	n.z /= n_norm;
	return (n);
}

double	get_diffuse_color(t_color *ambient, t_prog *prog, double *scalar)
{
	t_color		diffuse;
	t_object	*sp;
	t_object	*light;
	double		diff;

	sp = find_id(prog, "sp");
	light = find_id(prog, "L");
	diffuse.red = sp->color->red;
	diffuse.green = sp->color->green;
	diffuse.blue = sp->color->blue;
	/*diffuse.red *= (light->size[0] * (*scalar));
	diffuse.green *= (light->size[0] * (*scalar));
	diffuse.blue *= (light->size[0] * (*scalar));
	diffuse.red += ambient->red;
	printf("bas ambient red %lf\n", ambient->red);
	diffuse.green += ambient->green;
	diffuse.blue += ambient->blue;*/
	(void)scalar;
	(void)ambient;
	diffuse.red *= 255;
	diffuse.green *= 255;
	diffuse.blue *= 255;
	if (diffuse.red > 255)
		diffuse.red = 255;
	if (diffuse.green > 255)
		diffuse.green = 255;
	if (diffuse.blue > 255)
		diffuse.blue = 255;
	diff = ((int)diffuse.red << 16) | ((int)diffuse.green << 8) | ((int)diffuse.blue);
	return (diff);
}


