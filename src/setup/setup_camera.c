/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:58:32 by maandria          #+#    #+#             */
/*   Updated: 2025/03/24 13:11:36 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_viewport	mr_camera_init(double n, t_prog *prog)
{
	t_list		*p_tmp;
	t_object	*tmp;
	t_viewport	view;
	double		ratio_px;
	double		angle;

	p_tmp = prog->obj;
	tmp = find_id(prog, "C");
	if ((double)tmp->size[0] == 180)
		angle = (179 * PI) / 180.00;
	else
		angle = ((double)tmp->size[0] * 0.5 * PI) / 180.00;
	ratio_px = WIN_LENGTH / WIN_WIDTH;
	view.width = (2 * n) * tan(angle / 2);
	view.length = ratio_px * view.width;
	prog->obj = p_tmp;
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

t_coord	take_coord_id(t_prog *prog, char *str)
{
	t_object	*position;
	t_coord		position_px;
	t_list		*tmp;

	tmp = prog->obj;
	position = find_id(prog, str);
	if (!position)
	{
		position_px.x = INFINITY;
		position_px.y = INFINITY;
		position_px.z = INFINITY;
		prog->obj = tmp;
		return (position_px);
	}
	position_px.x = position->coord->x;
	position_px.y = position->coord->y;
	position_px.z = position->coord->z;
	prog->obj = tmp;
	return (position_px);
}

t_coord	set_cam_up(t_coord c_forward)
{/*
	t_coord	result;

	result = (t_coord){0, 0, 0};
	if (c_forward.x && !c_forward.y && !c_forward.z)
		result = (t_coord){0, 0, 1};
	else if (c_forward.y && !c_forward.x && !c_forward.z)
		result = (t_coord){0, 0, 1};
	else if (c_forward.z < 0 && !c_forward.y && !c_forward.x)
		result = (t_coord){-1, 0, 0};
	else if (c_forward.z > 0 && !c_forward.y && !c_forward.x)
		result = (t_coord){1, 0, 0};
	else if (c_forward.x && c_forward.y && !c_forward.z)
		result = (t_coord){0, 0, 1};
	return (result);*/

	t_coord	world_up;
	t_coord	right;
	t_coord	result;
	double	norm;

	world_up = (t_coord){0, 0, 1};
	if (fabs(c_forward.y) < pow(10, -6) && fabs(c_forward.x) < pow(10, -6))
		world_up = (t_coord){1, 0, 0};
	right = op_cross_prod(world_up, c_forward);
	norm = op_norm(right);
	right.x /= norm;
	right.y /= norm;
	right.z /= norm;
	result = op_cross_prod(c_forward, right);
	norm = op_norm(result);
	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	return (result);
}

t_coord	mr_pixel_position(t_prog *prog, t_viewport view, double *xy)
{
	t_coord		p_cam;
	t_coord		orient_cam;
	t_object	*position_cam;
	t_coord		result;
	t_camunit	cam;

	xy[0] += prog->pixel;
	position_cam = find_id(prog, "C");
	cam.c_forward = orient2coord(position_cam->orient);
	p_cam = take_coord_id(prog, "C");
	if (cam.c_forward.z && cam.c_forward.x && !cam.c_forward.y)
	{
		orient_cam = (t_coord){0, 1, 0};
		cam.c_up = op_cross_prod(cam.c_forward, orient_cam);
	}
	else if (cam.c_forward.z && cam.c_forward.y && !cam.c_forward.x)
	{
		orient_cam = (t_coord){1, 0, 0};
		cam.c_up = op_cross_prod(cam.c_forward, orient_cam);
	}
	else
		cam.c_up = set_cam_up(cam.c_forward);
	result = op_position_px(p_cam, view, cam, xy);
	return (result);
}
