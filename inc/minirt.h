/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:40:52 by atolojan          #+#    #+#             */
/*   Updated: 2025/02/05 14:56:37 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUFFER_SIZE 42
# define WIN_LENGTH 1600
# define WIN_WIDTH 800
# define PI 3.1415
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;96m"
# define RESET "\033[0m"

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_orient
{
	float	or_x;
	float	or_y;
	float	or_z;
}	t_orient;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;


typedef struct s_object
{
	char		id[3];
	t_coord		*coord;
	t_color		*color;
	t_orient	*orient;
	float		size[2];
}	t_object;

typedef struct s_prog
{
	void		*mlx;
	void		*mlx_win;
	t_list		*obj;
}	t_prog;


typedef struct	s_viewpoint
{
	float	length;
	float	width;
}	t_viewpoint;

typedef struct s_pixelco
{
	float	u;
	float	v;
}	t_pixelco;

/************ tools *************/

int			open_fd(char *file);
char		**get_line(int fd);
int			get_size(char *other, float max);
float		arc_atof(const char *nptr);
void		free_array(char **split);
void		free_object(t_object *obj);
void		print_error(int cipher, void *ptr);
t_object	*find_id(t_prog *prog, char *id);

/************ config *************/

t_viewpoint	mr_camera_init(float n, t_prog *prog);

/************ data *************/

void	set_data(char *file, t_list **list);
void	init_nbr_element(int nbr[]);
int		check_element(t_list **list);
void	set_nbr_element(int nbr[], t_object *obj);
int		init_prog(t_prog *prog);

/************ color *************/

void	set_color(t_object *obj, char **str);
int		get_color(char *color, t_object *obj);

/************ orient *************/

void	set_orient(t_object *obj, char **str);
int		get_orient(char *orient, t_object *obj);

/************ coord *************/

void	set_coord(t_object *obj, char **str);
int		get_coord(char *coord, t_object *obj);

/************ check_obj *************/

int		check_ambient(char **split, t_object *obj);
int		check_camera(char **split, t_object *obj);
int		check_light(char **split, t_object *obj);
int		check_sphere(char **split, t_object *obj);
int		check_plane(char **split, t_object *obj);
int		check_cylinder(char **split, t_object *obj);

/************ window *************/

int		quit_window(t_prog *obj);

#endif
