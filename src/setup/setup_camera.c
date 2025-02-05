/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:58:32 by maandria          #+#    #+#             */
/*   Updated: 2025/02/05 14:51:38 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_viewpoint	mr_camera_init(float n, t_prog *prog)
{
	t_object	*tmp;
	t_viewpoint	view;
	float		ratio_px;
	float		angle;

	tmp = find_id(prog, "C");
	angle = ((float)tmp->size[0] * PI) / 180.00;
	ratio_px = WIN_LENGTH / WIN_WIDTH;
	view.width = (2 * n) * tanf(angle / 2);
	view.length = ratio_px * view.width;
	return (view);
}

