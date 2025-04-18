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
	printf("FOV radian : %f\n", angle);
	printf(CYAN "Camera viewport : " RESET);
	printf("length = %f\twidth = %f\n", view.length, view.width);
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

t_coord	set_cam_haut(t_coord c_avant)
{
	t_coord	result;

	result = (t_coord){0, 0, 0};
	if (c_avant.x && !c_avant.y && !c_avant.z)
		result = (t_coord){0, 0, 1};
	else if (c_avant.y && !c_avant.x && !c_avant.z)
		result = (t_coord){0, 0, 1};
	else if (c_avant.z < 0 && !c_avant.y && !c_avant.x)
		result = (t_coord){-1, 0, 0};
	else if (c_avant.z > 0 && !c_avant.y && !c_avant.x)
		result = (t_coord){1, 0, 0};
	else if (c_avant.x && c_avant.y && !c_avant.z)
		result = (t_coord){0, 0, 1};
	return (result);
}

t_coord	mr_pixel_position(t_prog *prog, t_viewport view, double *xy)
{
	t_coord		p_cam;
	t_coord		orient_cam;
	t_object	*position_cam;
	t_coord		result;
	t_camunit	cam;

	position_cam = find_id(prog, "C");
	cam.c_avant = orient2coord(position_cam->orient);
	p_cam = take_coord_id(prog, "C");
	if (cam.c_avant.z && cam.c_avant.x && !cam.c_avant.y)
	{
		orient_cam = (t_coord){0, 1, 0};
		cam.c_haut = op_cross_prod(cam.c_avant, orient_cam);
	}
	else if (cam.c_avant.z && cam.c_avant.y && !cam.c_avant.x)
	{
		orient_cam = (t_coord){1, 0, 0};
		cam.c_haut = op_cross_prod(cam.c_avant, orient_cam);
	}
	else
		cam.c_haut = set_cam_haut(cam.c_avant);
	result = op_position_px(p_cam, view, cam, xy);
	return (result);
}
