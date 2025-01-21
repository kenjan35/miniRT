/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:32:08 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:22:51 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	open_fd(char *file)
{
	int	fd;

	if (!file)
	{
		print_error(3, NULL);
		exit(1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(3, NULL);
		exit(1);
	}
	return (fd);
}

char	**get_line(int fd)
{
	char	*line;
	char	**line_splitted;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (NULL);
	}
	line_splitted = arc_split(line);
	if (!line_splitted)
	{
		free(line);
		close(fd);
		return (NULL);
	}
	free(line);
	return (line_splitted);
}
