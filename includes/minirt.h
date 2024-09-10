/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 21:06:11 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define PERROR_ON 1
# define PERROR_OFF 0

# define CLOSE_WINDOW 17
# define PRESS_KEY 2
# define ESC_KEY 53

# define BACKGROUND_COLOR 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

# define FLT_MAX 3.402823466e+38F

typedef struct	s_point2d
{
	int	x;
	int	y;
}	t_point2d;

typedef struct	s_point3d
{
	float	x;
	float	y;
	float	z;
}	t_point3d;

typedef struct	s_vector3d
{
	float	x;
	float	y;
	float	z;
}	t_vector3d;

typedef struct	s_ray_hit
{
	float	t1;
	float	t2;
}	t_ray_hit;

typedef enum e_light_type
{
    AMBIENT_LIGHT,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT
}   t_light_type;

typedef struct  s_light
{
    t_light_type    type;
	float			ratio;
    int             color;
    t_vector3d      dir;
    t_point3d       pos;
	struct s_light	*next;
}   t_light;

typedef struct	s_camera
{
	t_point3d	pos;
	t_vector3d	dir;
	float		fov;
}	t_camera;

typedef struct	s_plane
{
	t_point3d		coord;
	t_vector3d		vector;
	int				color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_point3d			center;
	t_vector3d			vector;
	float				diameter;
	float				height;
	int					color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct	s_sphere
{
	t_point3d		center;
	float			radius;
	int				color;
	int				specular;
	struct s_sphere	*next;
}	t_sphere;

typedef struct	s_float_range
{
	float	min;
	float	max;
}	t_float_range;


typedef struct s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			num_of_lights;
	int			num_of_spheres;
	int			num_of_planes;
	int			num_of_cylinders;
}	t_scene;

typedef	struct	s_closest_hit
{
	t_sphere	*sphere;
	float		t;
}	t_closest_hit;

typedef struct s_win
{
	void	*ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	t_win	win;
	t_img	img;
	t_scene	scene;
}	t_vars;

//parse.c
int			parse_argv(int argc, char **argv);
void		parse(int argc, char **argv, t_vars *vars);


//parse_rt.c
char		*truncate_end_nl(char *str);
int			parse_line(char **line, t_vars *vars, int *parse_err_flag);
int			get_line(int fd, t_vars *vars);
int			parse_rt(char *argv, t_vars *vars);



//parse_object_camera.c
int			parse_camera(char **line, t_vars *vars);

//parse_object_amb_light.c
int			init_amb_light(t_light *lights, char **line, t_vars *vars);
int			set_amb_light(char **line, t_light *lights);
int			parse_amb_light(char **line, t_vars *vars);

//parse_object_point_light.c
int			init_point_light(t_light *lights, char **line, t_vars *vars);
int			set_point_light(char **line, t_light *lights);
int			parse_point_light(char **line, t_vars *vars);

// parse_mesh_plane.c
int			parse_plane(char **line, t_vars *vars);
int			set_plane(char **line, t_plane *planes);
int			init_planes(t_plane *planes, char **line, t_vars *vars);

// parse_mesh_sphere.c
int			parse_spheres(char **line, t_vars *vars);
int			set_sphere(char **line, t_sphere *spheres);
int			init_spheres(t_sphere *spheres, char **line, t_vars *vars);

// parse_mesh_cylinder.c
int			parse_cylinders(char **line, t_vars *vars);
int			set_cylinder(char **line, t_cylinder *cylinders);
int			init_cylinders(t_cylinder *cylinders, char **line, t_vars *vars);

//parse_utils.c
int			get_color(int r, int g, int b);
void		free_lists(char **lists);
float		ft_atof(char *str);
int			ft_strslen(char **strs);

//parse_check.c
int			check_coord(char **coord);
int			check_vector(char **vector);
int			check_color(char **color);
int			check_num_string(char *str);
int			check_float_string(char *str);

// minirt.c
void		error_exit(char *err_msg, int perror_flag);
void		init_vars(t_vars *vars);
void		clear_vars(t_vars *vars);

// render_scene.c
void		render_scene(t_vars *vars);
t_vector3d	canvas_to_viewport(int x, int y, t_img *img, int fov);
t_vector3d	rotate_camera(t_vector3d camera_dir, t_vector3d d);
int			trace_ray(t_scene *scene, t_vector3d D, float t_min, float t_max);
t_closest_hit		closest_intersection(t_point3d O, t_vector3d D, t_float_range t_range, t_scene *scene);
int			apply_lighting(int color, float lighting);

// intersect_ray_sphere.c
t_ray_hit	intersect_ray_sphere(t_point3d O, t_vector3d D, \
t_sphere *sphere);

// compute_lighting.c
float		compute_lighting(t_point3d p, t_vector3d v, t_sphere *sphere, t_scene *scene);

// my_mlx_pixel_put.c
void		my_mlx_pixel_put(int x, int y, int color, t_img *img);

// setup_event_hooks.c
void		setup_event_hooks(t_vars *vars);
int			key_hook(int keycode, void *param);
int			exit_no_error(void *param);

// vector_operations.c
t_vector3d	subtract_3dpoints(t_point3d p1, t_point3d p2);
float		dot(t_vector3d v1, t_vector3d v2);
t_vector3d	cross(t_vector3d v1, t_vector3d v2);
t_vector3d	scale_vector(t_vector3d v, float s);
t_point3d	add_vector_to_point(t_point3d p, t_vector3d v);
float		length(t_vector3d v);
t_vector3d	subtract_3dvectors(t_vector3d v1, t_vector3d v2);
t_vector3d	add_3dvectors(t_vector3d v1, t_vector3d v2);
float		cosine_between_vectors(t_vector3d v1, t_vector3d v2);
t_vector3d	normalize_vector(t_vector3d v);

#endif
