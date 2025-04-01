/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:01:11 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/24 11:28:16 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	get_pixel_color(t_prog *prog, t_object *sp, t_coord *norm_sphere, t_coord *rray)
{
	t_color		ambient;
	double		scalar;
	double		diffuse_color;

	ambient = get_ambient_intensity(prog, sp);
	scalar = get_scalar(norm_sphere, prog, rray);
	diffuse_color = get_diffuse_color(&ambient, prog, &scalar);
	return (diffuse_color);
}

void	put_image(t_prog *prog)
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
	obj = find_id(prog, "sp");
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
			ray = op_quadrique_value_sp(px_position, prog);
			//printf("main ray : x = %f, y = %f, z = %f\n", ray.v.x, ray.v.y, ray.v.z);
			time = inter_sp(prog, ray);
			rt = ray_launch(px_position, ray.v, time);
			n = normalize_sphere(&rt, &ray, &time);
			if (time > 0)
			{
				intensity = get_pixel_color(prog, obj, &n, &rt);
				*(int *)(buff + (int) xy[1] * prog->line_bytes + (int) xy[0] * (prog->pixel_bits / 8)) = (int)(intensity);
			}
			xy[0]++;
		}
		xy[1]++;
	}
	mlx_put_image_to_window(prog->mlx, prog->mlx_win, prog->img, 0, 0);
}
