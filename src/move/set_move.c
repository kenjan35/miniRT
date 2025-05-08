/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:37:23 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/01 11:45:23 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_object	*get_object_with_num(t_prog *prog, int num)
{
	t_object	*obj;
	t_list		*tmp;

	tmp = prog->obj;
	while (tmp)
	{
		obj = (t_object *) tmp->content;
		if (obj->num == num)
			return (obj);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_object(int key, int x, int y, t_prog *prog)
{
	t_object	*obj;
	t_coord		px_pos;
	double		xy[2];

	obj = NULL;
	px_pos = (t_coord){0, 0, 0};
	if (key == 1 || key == 3)
	{
		mlx_mouse_get_pos(prog->mlx, prog->mlx_win, &x, &y);
		xy[0] = x;
		xy[1] = y;
		px_pos = mr_pixel_position(prog, prog->view, xy);
		obj = get_closest(prog, &(prog->view), xy);
		prog->to_move = obj;
		return (1);
	}
	return (0);
}
