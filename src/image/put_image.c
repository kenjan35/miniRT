/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:01:11 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/18 10:40:02 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	get_pixel_color(t_prog *prog, t_object *obj, \
	t_coord *norm, t_coord *rray)
{
	t_color		ambient;
	t_object	*light;
	double		scalar;
	double		diffuse_color;

	light = find_id(prog, "L");
	ambient = get_ambient_intensity(prog, obj);
	scalar = get_scalar(norm, rray, light);
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
			obj = (t_object *) (tmp->content);
			time = (*inter)(prog, ray);
			if (time < min)
			{
				min = time;
				if (obj->id[1] == 'y')
					prog->current_cy = obj;
				else if (obj->id[1] == 'p')
					prog->current_sp = obj;
				else if (obj->id[1] == 'l')
					prog->current_pl = obj;
			}
			tmp = tmp->next;
		}
	}
	return (min);
}

double	get_time_caps(t_prog *prog, t_coord *rt, t_ray *ray, double *time)
{
	double	time_caps;

	(void) rt;
	(void) time;
	time_caps = INFINITY;
	time_caps = inter_cy_caps(prog->current_cy, ray);
	//if (get_extremity(&(ray->ro), rt, prog->current_cy) == 0)
	//	*time = 0;
	return (time_caps);
}

void	set_intensity(t_prog *prog, t_coord *rt, double *xy, char *buff)
{
	t_coord	n;
	double	norm;
	double	intensity;

	if (prog->current_cy)
	{
		if (prog->current_cy->id[1] == 'y')
			n = set_cylinder_normal(rt, prog->current_cy);
		else if (prog->current_cy->id[1] == 'p')
			n = normalize_sphere(rt, prog->current_cy);
		else if (prog->current_cy->id[1] == 'l')
		{
			n = orient2coord(prog->current_cy->orient);
			norm = op_norm(n);
			n.x /= norm;
			n.y /= norm;
			n.z /= norm;
		}
		intensity = get_pixel_color(prog, prog->current_cy, &n, rt);
		*(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
	}
}

void	set_intensity_caps(t_prog *prog, t_coord *rt, double *xy, char *buff)
{
	t_coord	n;
	double	norm;
	double	intensity;

	n = orient2coord(prog->current_cy->orient);
	norm = op_norm(n);
	n.x /= norm;
	n.y /= norm;
	n.z /= norm;
	intensity = get_pixel_color(prog, prog->current_cy, &n, rt);
	*(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
}

void	put_image(t_prog *prog, t_viewport *view, char *buff)
{
	t_ray		ray;
	t_coord		rt;
	double		xy[2];
	t_object	*obj;
	double		time_caps;

	xy[1] = -1;
	time_caps = INFINITY;
	while (++xy[1] < (WIN_WIDTH))
	{
		xy[0] = -1;
		while (++xy[0] < (WIN_LENGTH))
		{
			obj = get_closest(prog, view, xy);
			if (!obj)
				continue ;
			ray = op_quadrique_value_sp(prog->px_pos, prog, obj);
			rt = ray_launch(ray.ro, ray.v, obj->time);
			if (obj->id[1] == 'y')
				time_caps = get_time_caps(prog, &rt, &ray, &(obj->time));
			if (time_caps < INFINITY && time_caps > 0)
				set_intensity_caps(prog, &rt, xy, buff);
			if (obj->time > 0)
				set_intensity(prog, &rt, xy, buff);
		}
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, 0, 0);
}

void	set_render(t_prog *prog)
{
	t_viewport	view;
	char		*buff;

	view = mr_camera_init(1, prog);
	prog->img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	prog->shapes = all_shape(prog);
	if (prog->shapes == NULL)
		return ;
	put_image(prog, &view, buff);
}

// Cylinder
/*void	old_put_image(t_prog *prog)
{
	char		*buff;
	t_viewport	view;
//	t_coord		px_position;
	t_coord		rt;
	t_ray		ray;
	double		time;
	double		xy[2];
	double		time_caps;
	//t_coord		n;
	//t_coord		n2;
	//double		intensity;

	view = mr_camera_init(1, prog);
	time_caps = INFINITY;
	xy[1] = 0;
	prog->img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	while (xy[1] < (WIN_WIDTH))
	{
		xy[0] = 0;
		while (xy[0] < (WIN_LENGTH))
		{
			//px_position = mr_pixel_position(prog, view, xy);
			//ray = op_quadrique_value_cy(px_position, prog);
			//time = inter_cy(prog, &ray);
			//rt = ray_launch(px_position, ray.v, time);
			time = get_real_time(prog, &view, xy, &ray);
			rt = ray_launch(ray.ro, ray.v, time);
			if (prog->current_cy && prog->current_cy->id[1] == 'y')
				time_caps = get_time_caps(prog, &rt, &ray, &time);
			if (time_caps < INFINITY)
			{
				//n2 = orient2coord(obj->orient);
				//intensity = get_pixel_color(prog, obj, &n2, &rt);
				//(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
				set_intensity_caps(prog, &rt, xy, buff);
			}
			if (time < INFINITY)
			{
				//n = set_cylinder_normal(&rt, obj);
				//intensity = get_pixel_color(prog, obj, &n, &rt);
				//(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
				set_intensity(prog, &rt, xy, buff);
			}
			xy[0]++;
		}
		xy[1]++;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, 0, 0);
}*/

// Sphere
/*
void	old_put_image(t_prog *prog)
{
	char		*buff;
	t_viewport	view;
	//t_coord		px_position;
	t_coord		rt;
	t_ray		ray;
	double		time;
	double		xy[2];
	//t_coord		n;
	//double		intensity;

	view = mr_camera_init(1, prog);
	xy[1] = 0;
	prog->img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	while (xy[1] < (WIN_WIDTH))
	{
		xy[0] = 0;
		while (xy[0] < (WIN_LENGTH))
		{
			px_position = mr_pixel_position(prog, view, xy);
			ray = op_quadrique_value_sp(px_position, prog);
			time = inter_sp(prog, &ray);
			rt = ray_launch(px_position, ray.v, time);
			time = get_real_time(prog, &view, xy, &ray);
			rt = ray_launch(ray.ro, ray.v, time);
			if (time > 0)
			{
				n = normalize_sphere(&rt, obj);
				intensity = get_pixel_color(prog, obj, &n, &rt);
				*(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
				set_intensity(prog, &rt, xy, buff);
			}
			xy[0]++;
		}
		xy[1]++;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, 0, 0);
}*/

//Plane
/*void	put_image(t_prog *prog)
{
	char		*buff;
	t_viewport	view;
	t_coord		px_position;
	t_coord		rt;
	t_ray		ray;
	double		time;
	t_object	*obj;
	t_color		*color;
	double		xy[2];
	t_coord		n;
	double		intensity;

	check_list(prog);
	view = mr_camera_init(1, prog);
	obj = find_id(prog, "pl");
	color = obj->color;
	xy[1] = 0;
	prog->img = mlx_new_image(prog->mlx, WIN_LENGTH, WIN_WIDTH);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	while (xy[1] < (WIN_WIDTH))
	{
		xy[0] = 0;
		while (xy[0] < (WIN_LENGTH))
		{
			px_position = mr_pixel_position(prog, view, xy);
			ray = op_quadrique_value_pl(px_position, prog);
			time = time_inter_pl(px_position, prog);
			rt = ray_launch(px_position, ray.v, time);
			if (time > 0)
			{
				n = orient2coord(obj->orient);
				n.x /= op_norm(n);
				n.y /= op_norm(n);
				n.z /= op_norm(n);
				intensity = get_pixel_color(prog, obj, &n, &rt);
				*(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int) intensity;
			}
			xy[0]++;
		}
		xy[1]++;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, 0, 0);
}*/
