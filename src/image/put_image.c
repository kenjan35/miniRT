/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:01:11 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/14 14:59:51 by atolojan         ###   ########.fr       */
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

double	get_pixel_color(t_prog *prog, t_object *obj, \
	t_coord *norm, t_coord *rray)
{
	t_color		ambient;
	t_object	*light;
	double		scalar;
	double		diffuse_color;

	diffuse_color = 0;
	light = find_id(prog, "L");
	ambient = get_ambient_intensity(prog, obj);
	scalar = get_scalar(obj, norm, rray, light);
	if (in_shadow(prog, light, rray, norm) == 1)
	{
		set_ambient(&ambient);
		diffuse_color = ((int)ambient.red << 16) | ((int)ambient.green << 8) | \
			((int)ambient.blue);
	}
	else
		diffuse_color = get_diffuse_color(&ambient, &scalar, obj, light);
	return (diffuse_color);
}

double	get_nearest_time(t_prog *prog, t_ray *ray, t_list *s, \
	double (*inter)(t_prog *prog, t_ray *ray))
{
	t_list		*tmp;
	t_object	*obj;
	double		min;
	double		time;

	min = INFINITY;
	if (s)
	{
		tmp = s;
		while (tmp)
		{
			obj = (t_object *)(tmp->content);
			time = (*inter)(prog, ray);
			if (time < min)
				min = time;
			tmp = tmp->next;
		}
	}
	return (min);
}

void	put_image(t_prog *prog, t_viewport *view, char *buff, double *time_caps)
{
	t_ray		ray;
	t_coord		rt;
	t_object	*obj;

	while (time_caps[2] < (WIN_WIDTH))
	{
		time_caps[1] = 0;
		while (time_caps[1] < (WIN_LENGTH))
		{
			obj = get_closest(prog, view, &time_caps[1]);
			if (!obj)
				continue ;
			ray = op_quadrique_value_sp(prog->px_pos, prog, obj);
			rt = ray_launch(ray.ro, ray.v, obj->time);
			if (obj->id[1] == 'y')
				time_caps[0] = get_time_caps(prog, &rt, &ray, &(obj->time));
			if (time_caps[0] < INFINITY && time_caps[0] > 0)
				set_intensity_caps(prog, &rt, &time_caps[1], buff);
			else if (obj->time > 0 && obj->time < INFINITY)
				set_intensity(prog, &rt, &time_caps[1], buff);
		}
		time_caps[2] += prog->pixel;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, -1, 0);
}

void	set_render(t_prog *prog)
{
	char		*buff;
	double		time_caps[3];

	prog->view = mr_camera_init(1, prog);
	prog->img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	time_caps[0] = INFINITY;
	time_caps[2] = 0;
	put_image(prog, &(prog->view), buff, &time_caps[0]);
}
