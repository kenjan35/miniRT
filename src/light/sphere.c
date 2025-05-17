/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:05:36 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 09:25:04 by maandria         ###   ########.fr       */
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

double	get_scalar(t_object *obj, t_coord *n, t_coord *rray, t_object *light)
{
	double		scalar;
	t_coord		light_dir;
	double		norm;

	(void) obj;
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

t_coord	normalize_sphere(t_coord *ro, t_object *sp)
{
	t_coord	n;
	double	n_norm;

	n.x = ro->x - sp->coord->x;
	n.y = ro->y - sp->coord->y;
	n.z = ro->z - sp->coord->z;
	n_norm = op_norm(n);
	n.x /= n_norm;
	n.y /= n_norm;
	n.z /= n_norm;
	return (n);
}

double	get_diffuse_color(t_color *ambient, double *scalar, t_object *obj,
	t_object *light)
{
	t_color		diffuse;
	double		diff;

	diffuse.red = obj->color->red;
	diffuse.green = obj->color->green;
	diffuse.blue = obj->color->blue;
	diffuse.red *= (light->size[0] * (*scalar));
	diffuse.green *= (light->size[0] * (*scalar));
	diffuse.blue *= (light->size[0] * (*scalar));
	diffuse.red += ambient->red;
	diffuse.green += ambient->green;
	diffuse.blue += ambient->blue;
	diffuse.red *= 255;
	diffuse.green *= 255;
	diffuse.blue *= 255;
	if (diffuse.red > 255)
		diffuse.red = 255;
	if (diffuse.green > 255)
		diffuse.green = 255;
	if (diffuse.blue > 255)
		diffuse.blue = 255;
	diff = ((int)diffuse.red << 16) | ((int)diffuse.green << 8)
		| ((int)diffuse.blue);
	return (diff);
}
