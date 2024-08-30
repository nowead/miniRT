/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/30 21:48:48 by seonseo          ###   ########.fr       */
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

# define BACKGROUND_COLOR 0

# define DBL_MAX 1.7976931348623157e+308

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

typedef struct	s_intersection
{
	float	t1;
	float	t2;
}	t_intersection;

typedef struct	s_sphere
{
	t_point3d	center;
	float		radius;
	int			color;
}	t_sphere;

typedef struct s_obj
{
	t_point3d	camera;
	t_sphere	*spheres;
	int			num_of_spheres;
}	t_obj;

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
	t_obj		obj;
}	t_vars;

int	render_scene(t_vars *vars);

#endif