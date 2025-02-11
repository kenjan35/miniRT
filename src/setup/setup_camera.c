/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:58:32 by maandria          #+#    #+#             */
/*   Updated: 2025/02/10 17:23:13 by maandria         ###   ########.fr       */
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

t_coord	mr_pixel_position(t_prog *prog, t_viewport view, int x, int y)
{
	t_coord		orient_cam;
	t_coord		position_px;
	t_object	position_cam;

	position_cam = find_id(prog, "C");
	orient_cam = position_cam.coord;
}