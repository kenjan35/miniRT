/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:52:01 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/14 14:56:38 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_ambient(t_color *ambient)
{
	ambient->red *= 255;
	ambient->green *= 255;
	ambient->blue *= 255;
	if (ambient->red > 255)
		ambient->red = 255;
	if (ambient->green > 255)
		ambient->green = 255;
	if (ambient->blue > 255)
		ambient->blue = 255;
}

double	get_time_caps(t_prog *prog, t_coord *rt, t_ray *ray, double *time)
{
	double	time_caps;

	(void) rt;
	(void) time;
	time_caps = INFINITY;
	time_caps = inter_cy_caps(prog->current_obj, ray);
	if (get_extremity(&(ray->ro), rt, prog->current_obj) == 0)
		*time = 0;
	return (time_caps);
}

void	set_intensity(t_prog *prog, t_coord *rt, double *xy, char *buff)
{
	t_coord	n;
	double	intensity;

	if (prog->current_obj)
	{
		if (prog->current_obj->id[1] == 'y')
			n = set_cylinder_normal(rt, prog->current_obj);
		else if (prog->current_obj->id[1] == 'p')
			n = normalize_sphere(rt, prog->current_obj);
		else if (prog->current_obj->id[1] == 'l')
		{
			n = orient2coord(prog->current_obj->orient);
			n = op_normalize(n);
			n.x *= -1;
			n.y *= -1;
		}
		intensity = get_pixel_color(prog, prog->current_obj, &n, rt);
		*(int *)(buff + (int) xy[1] * prog->line_bytes + \
			(int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
	}
}

void	set_intensity_caps(t_prog *prog, t_coord *rt, double *xy, char *buff)
{
	t_coord	n;
	double	intensity;

	n = orient2coord(prog->current_obj->orient);
	if (prog->current_obj->id[0] == '2')
	{
		n.x *= -1;
		n.y *= -1;
		n.z *= -1;
	}
	n = op_normalize(n);
	prog->current_obj->id[0] = 'c';
	intensity = get_pixel_color(prog, prog->current_obj, &n, rt);
	*(int *)(buff + (int) xy[1] * prog->line_bytes + \
		(int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
}
