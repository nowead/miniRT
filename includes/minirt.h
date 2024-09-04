/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/04 19:22:27 by damin            ###   ########.fr       */
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

typedef struct	s_hit
{
	float	t1;
	float	t2;
}	t_hit;

typedef struct	s_camera
{
	t_point3d	coord;
	t_vector3d	vector;
	float		fov;
}	t_camera;

typedef enum e_light_type
{
    AMBIENT_LIGHT,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT
}   t_light_type;

typedef struct  s_light
{
    t_light_type    type;
    float           intens;
    int             color;
    t_vector3d      dir;
    t_point3d       pos;
}   t_light;

typedef struct	s_plane
{
	t_point3d		coord;
	t_vector3d		vector;
	int				color;
	struct s_plane	*next;
}	t_plane;

typedef struct	s_sphere
{
	t_point3d		center;
	float			radius;
	int				color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct	s_cylinder
{
	t_point3d			center;
	t_vector3d			vector;
	float				diameter;
	float				height;
	int					color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	int			num_of_spheres;
	int			num_of_planes;
	int			num_of_cylinders;
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
void		init_objects(t_obj *obj);

// render_scene.c
void		render_scene(t_vars *vars);
t_vector3d	canvas_to_viewport(int x, int y, t_img *img);
int			trace_ray(t_obj *obj, t_vector3d D, float t_min, float t_max);
t_hit		intersect_ray_sphere(t_point3d O, t_vector3d D, \
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