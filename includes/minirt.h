/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/02 22:03:35 by seonseo          ###   ########.fr       */
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

typedef struct	s_camera
{
	t_point3d	pos;
	t_vector3d	dir;
	int			fov;
}	t_camera;

typedef struct	s_amb_light
{
	float	intens;
	int		color;
}	t_amb_light;

typedef struct	s_dir_light
{
	t_vector3d	dir;
	float		intens;
	int			color;
}	t_dir_light;

typedef struct	s_point_light
{
	t_point3d	pos;
	float		intens;
	int			color;
}	t_point_light;

typedef struct	s_plane
{
	t_point3d	pos;
	t_vector3d	dir;
	int			color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3d	center;
	t_vector3d	vector;
	float		diameter;
	float		height;
	int			color;
}	t_cylinder;

typedef struct	s_sphere
{
	t_point3d	center;
	float		radius;
	int			color;
}	t_sphere;

typedef struct s_scene
{
	t_camera		camera;
	t_dir_light		dir_light;
	t_point_light	point_light;
	t_amb_light		amb_light;
	t_sphere		*spheres;
	int				num_of_spheres;
	t_cylinder		cylinder;
	t_plane			plane;
}	t_scene;

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
void		error_exit(char *err_msg, int perror_flag);
void		init_vars(t_vars *vars);
void		init_scene(t_scene *scene);

// render_scene.c
void		render_scene(t_vars *vars);
t_vector3d	canvas_to_viewport(int x, int y, t_img *img);
int			trace_ray(t_scene *scene, t_vector3d D, float t_min, float t_max);
t_ray_hit	intersect_ray_sphere(t_point3d O, t_vector3d D, \
t_sphere *sphere);
t_vector3d	subtract_3dpoints(t_point3d p1, t_point3d p2);
float		dot(t_vector3d v1, t_vector3d v2);

// my_mlx_pixel_put.c
void		my_mlx_pixel_put(int x, int y, int color, t_img *img);

// setup_event_hooks.c
void		setup_event_hooks(t_vars *vars);
int			key_hook(int keycode, void *param);
int			exit_no_error(void);

#endif
