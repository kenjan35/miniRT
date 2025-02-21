/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:58:32 by maandria          #+#    #+#             */
/*   Updated: 2025/02/21 12:31:01 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_viewport	mr_camera_init(float n, t_prog *prog)
{
	t_object	*tmp;
	t_viewport	view;
	float		ratio_px;
	float		angle;

	tmp = find_id(prog, "C");
	angle = ((float)tmp->size[0] * PI) / 180.00;
	ratio_px = WIN_LENGTH / WIN_WIDTH;
	view.width = (2 * n) * tanf(angle / 2);
	view.length = ratio_px * view.width;
	return (view);
}

t_coord	orient2coord(t_orient *orient)
{
	t_coord	result;

	result.x = orient->or_x;
	result.y = orient->or_y;
	result.z = orient->or_z;
	return (result);
}

t_coord	mr_pixel_position(t_prog *prog, t_viewport view, int x, int y)
{
	t_coord		p_cam;
	t_coord		orient_cam;
	t_coord		position_px;
	t_object	*position_cam;
	t_coord		result;
	t_camunit	cam;
	t_coord		tmp;

	position_cam = find_id(prog, "C");
	position_px.x = position_cam->coord->x;
	position_px.y = position_cam->coord->y;
	position_px.z = position_cam->coord->z;
	cam.c_avant = orient2coord(position_cam->orient);
	p_cam = position_px;
	tmp = (t_coord){0, 0, 1};
	if (cam.c_avant.x && !cam.c_avant.y && !cam.c_avant.z)
		cam.c_haut = (t_coord){0, 0, 1};
	else if (cam.c_avant.y && !cam.c_avant.x && !cam.c_avant.z)
		cam.c_haut = (t_coord){0, 0, 1};
	else if (cam.c_avant.z < 0 && !cam.c_avant.y && !cam.c_avant.x)
		cam.c_haut = (t_coord){1, 0, 0};
	else if (cam.c_avant.z > 0 && !cam.c_avant.y && !cam.c_avant.x)
		cam.c_haut = (t_coord){-1, 0, 0};
	else if (cam.c_avant.z && cam.c_avant.x && !cam.c_avant.y)
	{
		orient_cam = (t_coord){0, 1, 0};
		cam.c_haut = op_pro_vect(cam.c_avant, orient_cam);
	}
	else if (cam.c_avant.z && cam.c_avant.y && !cam.c_avant.x)
	{
		orient_cam = (t_coord){1, 0, 0};
		cam.c_haut = op_pro_vect(cam.c_avant, orient_cam);
	}
	result = op_position_px(p_cam, view, cam, x, y);
	return (result);
}
