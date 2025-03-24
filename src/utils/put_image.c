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

void	put_image(t_prog *prog, int color)
{
	char	*buff;

	prog->img = mlx_new_image(prog->mlx, 500, 200);
	buff = mlx_get_data_addr(prog->img, &(prog->pixel_bits), \
		&(prog->line_bytes), &(prog->endian));
	for (int y = 0;y < WIN_WIDTH;y++)
	{
		for (int x = 0;x < WIN_LENGTH;x++)
		{
			*(int *)(buff + y * prog->line_bytes + x * (prog->pixel_bits / 8)) = color;
		}
	}
}
