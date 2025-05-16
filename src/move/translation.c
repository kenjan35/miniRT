/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:02:52 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/16 15:03:47 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	translate_x(t_object *obj, double distance)
{
	double	x;

	x = obj->coord->x + distance;
	obj->coord->x = x;
}

void	translate_y(t_object *obj, double distance)
{
	double	y;

	y = obj->coord->y + distance;
	obj->coord->y = y;
}

void	translate_z(t_object *obj, double distance)
{
	double	z;

	z = obj->coord->z + distance;
	obj->coord->z = z;
}

t_object	*obj_to_translate(int key, t_prog *prog)
{
	static t_object	*obj = NULL;

	if (key == 'c')
		prog->to_move = find_id(prog, "C");
	if (key == 'x')
		prog->to_move = find_id(prog, "L");
	if (prog->to_move)
		obj = prog->to_move;
	return (obj);
}

int	translate(int key, t_prog *prog)
{
	static t_object	*obj = NULL;

	prog->pixel = 2.5;
	if (!obj_to_translate(key, prog))
		return (0);
	else
		obj = obj_to_translate(key, prog);
	if (key == 'u')
		translate_x(obj, 0.25);
	else if (key == 'o')
		translate_x(obj, -0.25);
	else if (key == 'j')
		translate_y(obj, 0.25);
	else if (key == 'l')
		translate_y(obj, -0.25);
	else if (key == 'i')
		translate_z(obj, 0.25);
	else if (key == 'k')
		translate_z(obj, -0.25);
	else
		return (rotate(key, prog));
	mlx_destroy_image(prog->mlx, prog->img);
	set_render(prog);
	return (1);
}
