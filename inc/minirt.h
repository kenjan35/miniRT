/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:40:52 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/24 13:50:37 by maandria         ###   ########.fr       */
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
	double	red;
	double	green;
	double	blue;
}	t_color;

typedef struct s_orient
{
	double	or_x;
	double	or_y;
	double	or_z;
}	t_orient;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_object
{
	char		id[3];
	t_coord		*coord;
	t_color		*color;
	t_orient	*orient;
	double		size[2];
}	t_object;

typedef struct s_prog
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	t_list		*obj;
}	t_prog;

typedef struct	s_viewport
{
	double		length;
	double		width;
}	t_viewport;

typedef struct s_camunit
{
	t_coord		c_avant;
	t_coord		c_haut;
}	t_camunit;

typedef struct s_ray
{
	t_coord	ro;
	t_coord	v;
	t_coord	rso;
}	t_ray;

typedef struct s_quadric
{
	double	A;
	double	B;
	double	C;
}	t_quadric;


/************ tools *************/

int			open_fd(char *file);
char		**get_line(int fd);
int			get_size(char *other, double max);
double		arc_atof(const char *nptr);
void		free_array(char **split);
void		free_object(t_object *obj);
void		print_error(int cipher, void *ptr);
t_object	*find_id(t_prog *prog, char *id);
t_object	**create_object(t_prog *prog);
t_coord		take_coord_id(t_prog *prog, char *str);

/************ config *************/

t_viewport	mr_camera_init(double n, t_prog *prog);
t_coord		mr_pixel_position(t_prog *prog, t_viewport view, double *xy);

/************ data *************/

void		set_data(char *file, t_list **list, t_prog *prog);
void		init_nbr_element(int nbr[]);
int			check_element(t_list **list);
void		set_nbr_element(int nbr[], t_object *obj);
int			init_prog(t_prog *prog);

/************ color *************/

void		set_color(t_object *obj, char **str);
int			get_color(char *color, t_object *obj);

/************ orient *************/

void		set_orient(t_object *obj, char **str);
int			get_orient(char *orient, t_object *obj);

/************ coord *************/

void		set_coord(t_object *obj, char **str);
int			get_coord(char *coord, t_object *obj);

/************ check_obj *************/

int			check_ambient(char **split, t_object *obj);
int			check_camera(char **split, t_object *obj);
int			check_light(char **split, t_object *obj);
int			check_sphere(char **split, t_object *obj);
int			check_plane(char **split, t_object *obj);
int			check_cylinder(char **split, t_object *obj);

/************ window *************/

int			quit_window(t_prog *obj);
int			key_close(int key, t_prog *prog);
void		put_sp(t_prog *prog, double *xy, t_viewport view, t_object **allob);

/************ Operation ************/

double		op_norm(t_coord u);
double		inter_sp(t_prog	*prog, t_ray ray);
double		inter_cy(t_prog	*prog, t_ray ray);
double		op_dot_prod(t_coord u, t_coord v);
double		op_solution_quad(double A, double B, double C);
double		op_norm_pv(t_coord u, t_coord v, double teta);
t_coord		orient2coord(t_orient *orient);
t_coord		op_cross_prod(t_coord u, t_coord v);
t_coord		op_vector_use(t_coord u, t_coord v);
t_coord		op_vect_n_lamda(double x, t_coord u);
t_coord		orientation_ray(t_coord u, t_prog *prog);
t_coord		op_vector_addition(t_coord u, t_coord v);
t_coord		op_ortgl_projec_prll(t_coord u, t_coord v);
t_coord		ray_launch(t_coord u, t_coord v, double t);
t_coord		op_vpixel_unit(t_viewport view, t_coord u, t_coord v, int index);
t_coord		op_position_px(t_coord pos_cam,t_viewport view, t_camunit cam, double *xy);
t_ray		op_quadrique_value_sp(t_coord px,t_prog *prog);
t_ray		op_quadrique_value_cy(t_coord px, t_prog *prog);
t_quadric	op_values_polynome(t_ray ray, double rayon);

/************** Operation Plane *****************/

t_ray		op_quadrique_value_pl(t_coord px,t_prog *prog);
t_orient	take_orient_id(t_prog *prog, char *str);
double		vector_numer(t_coord n, t_coord rp, t_coord px);
double		vector_denom(t_coord n, t_coord v);
double		time_inter_pl(t_coord px, t_prog *prog);
void		put_image(t_prog *prog);

/************** Light *****************/

t_color		get_ambient_intensity(t_prog *prog, t_object *sp);
double		get_scalar(t_coord *n, t_prog *prog, t_coord *rray);
double		get_diffuse_color(t_color *ambient, t_prog *prog, double *scalar);
t_coord		normalize_sphere(t_coord *ro, t_object *obj);

void		check_list(t_prog *prog);
double		light_sphere(t_color *colors, double intensity);
int			gradient(int y, t_color *colors);

#endif
