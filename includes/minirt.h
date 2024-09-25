/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/25 13:41:23 by seonseo          ###   ########.fr       */
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

# define BACKGROUND_COLOR 0xFFFFFF

# define FLT_MAX 3.402823466e+38F

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

typedef struct	s_point2
{
	float	x;
	float	y;
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

typedef struct	s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

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
	POINT_LIGHT
}	t_light_type;

typedef struct	s_light
{
	t_light_type	type;
	float			intens;
	t_color			color;
	t_color			color_intens;
	t_point3		pos;
	struct s_light	*next;
}	t_light;

typedef struct	s_sphere
{
	t_point3	center;
	float		radius;
}	t_sphere;

typedef struct	s_plane
{
	t_point3	pos;
	t_vec3		normal;
}	t_plane;

typedef struct s_circle
{
	t_point3	center;
	t_vec3		normal;
	float		radius;
}	t_circle;

typedef struct s_cy_side
{
	t_point3	center;
	t_vec3		axis;
	float		radius;
	float		height;
}	t_cy_side;

typedef struct s_cylinder
{
	t_cy_side	side;
	t_circle	top_cap;
	t_circle	bottom_cap;
}	t_cylinder;

typedef struct s_co_side
{
	t_point3	vertex;
	t_vec3		axis;
	float		radius;
	float		height;
}	t_co_side;

typedef struct s_cone
{
	t_co_side	side;
	t_circle	bottom_cap;
}	t_cone;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_obj_type;

typedef enum e_sub_obj
{
	TOP_CAP,
	BOTTOM_CAP,
	SIDE,
}	t_sub_obj;

typedef union u_obj_data
{
    t_sphere	sphere;
    t_plane		plane;
    t_cylinder	cylinder;
	t_cone		cone;
} t_obj_data;

typedef enum s_texture_type
{
	COLOR,
	CHECKERBOARD,
	IMAGE
}	t_texture_type;

typedef struct s_checkerboard
{
	t_color	color1;
	t_color	color2;
	int		columns;
	int		rows;
}	t_checkerboard;

typedef struct s_obj
{
	t_obj_type		type;
	t_obj_data		data;
	int				specular;
	t_texture_type	texture_type;
	t_color			color;
	t_checkerboard	checkerboard;
	t_img			image;
	t_img			bumpmap;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_obj		*obj;
}	t_scene;

typedef	struct	s_closest_hit
{
	t_obj		*obj;
	t_sub_obj	sub_obj;
	float		t;
}	t_closest_hit;

typedef struct s_inter_vars
{
	t_ray			*ray;
	t_obj			*obj;
	t_float_range	*t_range;
	t_closest_hit	*closest_hit;
}	t_inter_vars;

typedef struct s_vars
{
	void		*mlx;
	t_win		win;
	t_img		img;
	t_scene		scene;
}	t_vars;

// minirt.c
int				error_return(char *err_msg, int perror_flag);
void			error_exit(char *err_msg, int perror_flag);
void			init_vars(t_vars *vars);

// render_scene.c
void			render_scene(t_vars *vars);
void			init_camera_and_viewport(t_camera *camera, t_img *img);
t_vec3			canvas_to_viewport(int x, int y, t_img *img, t_camera *camera);
int				trace_ray(t_scene *scene, t_vec3 ray_dir);
t_color			int_to_t_color(int int_color);

// get_surface_color.c
t_color			get_surface_color(t_point3 p, t_closest_hit *closest_hit);
t_point2		convert_to_texture_space(t_point3 p, t_obj *obj, t_sub_obj sub_obj);
t_vec3			world_to_local(t_vec3 p, t_vec3 axis, t_point3 center);
t_color			get_checkerboard_color(t_checkerboard *checkerboard, t_point2 texture_point);
t_color			get_image_color(t_img *img, t_point2 texture_point);
t_color			int_to_t_color(int int_color);

// closest_intersection.c
t_closest_hit	closest_intersection(t_ray ray, t_float_range t_range, t_scene *scene);
int				solve_quadratic_equation(float coeff[3], float t[2]);
void			update_closest_hit(float t, t_sub_obj sub_obj, t_inter_vars *vars);

// intersect_ray_sphere.c
void			intersect_ray_sphere(t_inter_vars vars);
void			compute_sphere_quadratic_coefficients(t_ray *ray, t_sphere *sphere, float coeff[3]);

// intersect_ray_plane.c
void			intersect_ray_plane(t_inter_vars vars);
int				compute_plane_intersection(t_ray *ray, t_plane *plane, float *t);

// intersect_ray_cylinder.c
void			intersect_ray_cylinder(t_inter_vars vars);
void			intersect_ray_cylinder_side(t_inter_vars *vars);
void			compute_cylinder_side_quadratic_coefficients(t_inter_vars *vars, float coeff[3], t_vec3 *co, float term[2]);
int				is_p_within_cylinder_height(float co_dot_axis, float d_dot_axis, float t, float h);
void			intersect_ray_cylinder_cap(t_inter_vars *vars, t_sub_obj sub_obj);

// intersect_ray_cone.c
void			intersect_ray_cone(t_inter_vars vars);
void			intersect_ray_cone_side(t_inter_vars *vars);
void			compute_cone_side_quadratic_coefficients(t_inter_vars *vars, float coeff[3], t_vec3 vo, float term[2]);
int				is_p_within_cone_height(float vo_dot_axis, float d_dot_axis, float t, float cone_height);
void			intersect_ray_cone_cap(t_inter_vars *vars);

// compute_circle_intersection.c
int				compute_circle_intersection(t_ray *ray, t_circle *circle, float *t);

// compute_lighting.c
t_color			compute_lighting(t_point3 p, t_vec3 v, t_closest_hit *hit, t_scene *scene);
void			add_light_intensity(t_color *intens, float factor, t_color *light_color);
int				apply_lighting(t_color color, t_color *lighting);

// get_normal_vector.c
t_vec3			get_normal_vector(t_point3 p, t_closest_hit *hit);
t_vec3			get_sphere_normal(t_point3 p, t_closest_hit *hit);
t_vec3			get_plane_normal(t_point3 p, t_closest_hit *hit);
t_vec3			get_cylinder_normal(t_point3 p, t_closest_hit *hit);
t_vec3			get_cone_normal(t_point3 p, t_closest_hit *hit);

// apply_bump_map.c
t_vec3			apply_bump_map_texture(t_img *bumpmap, t_point2 texture_point, \
t_vec3 *geo_normal);
void			get_surrounding_pixel_height(t_img *bumpmap, int x, int y, float height[4]);
float			get_bump_map_height(t_img *bumpmap, float x, float y);

// my_mlx_pixel_put.c
void			my_mlx_pixel_put(int x, int y, int color, t_img *img);
void			my_mlx_clear_window(t_vars *vars);
int				my_mlx_get_pixel_color(t_img *img, int x, int y);

// setup_event_hooks.c
void			setup_event_hooks(t_vars *vars);
int				key_hook(int keycode, void *param);
int				exit_no_error(void);
void			key_hook_rotate_camera(int keycode, t_vars *vars);
void			key_hook_translate_camera(int keycode, t_vars *vars);
void			draw_next_frame(t_vars *vars);
void			rotate_vector(t_vec3 *v, t_vec3 axis, float angle);
void			move_camera(t_camera *camera, int direction, float distance);

// vector_operations.c
t_vec3			subtract_3dpoints(t_point3 p1, t_point3 p2);
float			dot(t_vec3 v1, t_vec3 v2);
t_vec3			cross(t_vec3 v1, t_vec3 v2);
t_vec3			scale_vector(t_vec3 v, float s);
t_point3		add_vector_to_point(t_point3 p, t_vec3 v);
float			length(t_vec3 v);
t_vec3			subtract_vectors(t_vec3 v1, t_vec3 v2);
t_vec3			add_3dvectors(t_vec3 v1, t_vec3 v2);
float			cosine_between_vectors(t_vec3 v1, t_vec3 v2);
t_vec3			unit_vector(t_vec3 v);

//parse.c
int				parse_argv(int argc, char **argv);
void			parse_scene(int argc, char **argv, t_vars *vars);
int				parse_rt_file(char *argv, t_vars *vars);
int				parse_lines_from_rt_file(int fd, t_vars *vars);
void			clear_scene(t_vars *vars);

//parse_scene_element.c
int				parse_scene_element(char **line, t_vars *vars);
int				parse_camera(char **line, t_vars *vars);;
int				parse_light(char **line, t_vars *vars, int (*set_light)(char **line, t_light *light));
int				parse_object(char **line,t_vars *vars, int (*set_obj)(char **line, t_obj *obj, void *mlx));

// parse_light.c
int				set_amb_light(char **line, t_light *lights);
int				set_point_light(char **line, t_light *lights);

// parse_object.c
int				set_sphere(char **line, t_obj *sphere, void *mlx);
int				set_plane(char **line, t_obj *plane, void *mlx);
int				set_cylinder(char **line, t_obj *cylinder, void *mlx);
int				set_cone(char **line, t_obj *cone, void *mlx);

// parse_object_cap.c
void			set_cylinder_cap(t_cylinder *cylinder);
void			set_cone_cap(t_cone *cone);

// parse_types.c
int				parse_3dpoint(char *line, t_point3 *point);
int				parse_3dvector(char *line, t_vec3 *vector);
int				parse_color(char *line, t_color *obj_color);

// parse_texture.c
int				parse_color_or_texture(char *line, t_obj *obj, void *mlx);
int				parse_uv(char **checkerboard, t_checkerboard *obj_checkerboard);
int				parse_checkerboard(char *line, \
t_checkerboard *obj_checkerboard);
int				parse_texture_image(char *line, t_img *img, void *mlx);
int				parse_xpm_file_to_image(char *line, t_img *img, void *mlx);

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
