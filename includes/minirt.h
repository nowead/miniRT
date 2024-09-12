/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/12 20:58:20 by seonseo          ###   ########.fr       */
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

typedef struct	s_point2
{
	int	x;
	int	y;
}	t_point2;

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef t_vec3 t_point3;

typedef struct	s_ray
{
	t_point3	origin;
	t_vec3		dir;
}	t_ray;

typedef struct	s_float_range
{
	float	min;
	float	max;
}	t_float_range;

typedef struct	s_camera
{
	t_point3	pos;
	t_vec3		dir;
	int			fov;
	float		fov_radian;
	float		viewport_w;
	float		viewport_h;
	t_vec3		viewport_c;
	t_vec3		u;
	t_vec3		v;
}	t_camera;

typedef enum e_light_type
{
	AMBIENT_LIGHT,
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
}	t_light_type;

typedef struct	s_light
{
	t_light_type	type;
	float			intens;
	int				color;
	t_vec3			dir;
	t_point3		pos;
	struct s_light	*next;
}	t_light;

typedef struct	s_plane
{
	t_point3	pos;
	t_vec3		normal;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		vector;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_cone
{
	t_point3	vertex;
	t_vec3		axis;
	float		radius;
	float		height;
}	t_cone;

typedef struct	s_sphere
{
	t_point3	center;
	float		radius;
}	t_sphere;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_obj_type;

typedef union u_obj_data
{
    t_sphere	sphere;
    t_plane		plane;
    t_cylinder	cylinder;
	t_cone		cone;
} t_obj_data;

typedef struct s_obj
{
	t_obj_type		type;
	t_obj_data		data;
	int				color;
	int				specular;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	t_camera	camera;
	t_light		*lights;
	int			num_of_lights;
	t_obj		*obj;
	int			num_of_obj;
}	t_scene;

typedef	struct	s_closest_hit
{
	t_obj	*obj;
	float	t;
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
	void		*mlx;
	t_win		win;
	t_img		img;
	t_scene		scene;
}	t_vars;

// minirt.c
void			error_exit(char *err_msg, int perror_flag);
void			init_vars(t_vars *vars);
// void			init_scene(t_scene *scene);

// render_scene.c
void			render_scene(t_vars *vars);
void			init_camera_and_viewport(t_camera *camera, t_img *img);
t_vec3			canvas_to_viewport(int x, int y, t_img *img, t_camera *camera);
int				trace_ray(t_scene *scene, t_vec3 ray_dir);
t_closest_hit	closest_intersection(t_ray ray, t_float_range t_range, t_scene *scene);

// intersect_ray_obj.c
void			intersect_ray_sphere(t_ray *ray, t_obj *obj, t_float_range t_range, t_closest_hit *closest_hit);
void			intersect_ray_plane(t_ray *ray, t_obj *obj, t_float_range t_range, t_closest_hit *closest_hit);
void			intersect_ray_cylinder(t_ray *ray, t_obj *obj, t_float_range t_range, t_closest_hit *closest_hit);

// compute_lighting.c
float			compute_lighting(t_point3 p, t_vec3 v, t_obj *obj, t_scene *scene);
int				apply_lighting(int color, float lighting);

// my_mlx_pixel_put.c
void			my_mlx_pixel_put(int x, int y, int color, t_img *img);

// setup_event_hooks.c
void			setup_event_hooks(t_vars *vars);
int				key_hook(int keycode, void *param);
int				exit_no_error(void);

// vector_operations.c
t_vec3			subtract_3dpoints(t_point3 p1, t_point3 p2);
float			dot(t_vec3 v1, t_vec3 v2);
t_vec3			cross(t_vec3 v1, t_vec3 v2);
t_vec3			scale_vector(t_vec3 v, float s);
t_point3		add_vector_to_point(t_point3 p, t_vec3 v);
float			length(t_vec3 v);
t_vec3			subtract_3dvectors(t_vec3 v1, t_vec3 v2);
t_vec3			add_3dvectors(t_vec3 v1, t_vec3 v2);
float			cosine_between_vectors(t_vec3 v1, t_vec3 v2);
t_vec3			unit_vector(t_vec3 v);

//parse.c
int				parse_argv(int argc, char **argv);
void			parse_scene(int argc, char **argv, t_vars *vars);
int				parse_rt_file(char *argv, t_vars *vars);
int				parse_lines_from_rt_file(int fd, t_vars *vars);
void			clear_scene(t_vars *vars);

//parse_rt_file.c
int				parse_scene_element(char **line, t_vars *vars);
int				parse_light(char **line, t_vars *vars, int (*set_light)(char **line, t_light *light));
int				parse_object(char **line,t_vars *vars, int (*set_obj)(char **line, t_obj *obj));

// parse_camera.c
int				parse_camera(char **line, t_vars *vars);

// parse_light.c
int				set_amb_light(char **line, t_light *lights);
int				set_point_light(char **line, t_light *lights);

// parse_object.c
int				set_sphere(char **line, t_obj *sphere);
int				set_plane(char **line, t_obj *plane);
int				set_cylinder(char **line, t_obj *cylinder);
int				set_cone(char **line, t_obj *cone);

// parse_types.c
int				parse_3dpoint(char *str, t_point3 *point);
int				parse_3dvector(char *str, t_vec3 *vector);
int				parse_color(char *str, int *color);

// parse_utils.c
int				get_color(int r, int g, int b);
void			free_lists(char **lists);
float			ft_atof(char *str);
int				ft_strslen(char **strs);
char			*truncate_end_nl(char *str);

// parse_error_check.c
int				check_coord(char **coord);
int				check_vector(char **vector);
int				check_color(char **color);
int				check_decimal_str(char *str);
int				check_float_str(char *str);

#endif
