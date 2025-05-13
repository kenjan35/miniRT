/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:49:23 by atolojan          #+#    #+#             */
/*   Updated: 2025/02/26 16:08:42 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	quit_window(t_prog *prog)
{
	if (prog->img)
		mlx_destroy_image(prog->mlx, prog->img);
	mlx_destroy_window(prog->mlx, prog->mlx_win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	if (prog->obj)
		ft_lstclear(&(prog->obj), free_object);
	if (prog->shapes)
		ft_lstclear(&(prog->shapes), free_object);
	exit(0);
}

int	init_prog(t_prog *prog)
{
	prog->mlx = mlx_init();
	if (!prog->mlx)
		return (0);
	prog->mlx_win = mlx_new_window(prog->mlx, WIN_LENGTH, WIN_WIDTH, "miniRT");
	if (!prog->mlx_win)
	{
		mlx_destroy_display(prog->mlx);
		free(prog->mlx);
		return (0);
	}
	prog->pixel = 1;
	prog->obj = NULL;
	prog->shapes = NULL;
	prog->current_obj = NULL;
	prog->to_move = NULL;
	return (1);
}

int	key_close(int key, t_prog *prog)
{
	if (key == 65307)
	{
		if (prog->img)
			mlx_destroy_image(prog->mlx, prog->img);
		mlx_destroy_window(prog->mlx, prog->mlx_win);
		mlx_destroy_display(prog->mlx);
		free(prog->mlx);
		if (prog->shapes)
			ft_lstclear(&(prog->shapes), free_object);
		if (prog->obj)
			ft_lstclear(&(prog->obj), free_object);
		exit(0);
	}
	return (0);
}
