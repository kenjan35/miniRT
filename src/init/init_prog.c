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
	mlx_destroy_window(prog->mlx, prog->mlx_win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
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
	prog->obj = NULL;
	prog->shapes = NULL;
	prog->current_cy = NULL;
	prog->current_sp = NULL;
	prog->current_pl = NULL;
	return (1);
}

int	key_close(int key, t_prog *prog)
{
	if (key == 65307)
	{
		mlx_destroy_window(prog->mlx, prog->mlx_win);
		mlx_destroy_display(prog->mlx);
		free(prog->mlx);
		exit(0);
	}
	return (0);
}
