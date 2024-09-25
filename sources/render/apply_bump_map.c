/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_bump_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:13:56 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/25 19:26:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define X 0
#define Y 1
#define U 0
#define V 1
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

t_vec3	apply_bump_map_texture(t_img *bumpmap, t_point2 texture_point, \
t_vec3 *geo_normal)
{
	float	height[4];
	int		point[2];
	float	offset[2];
	t_vec3	vec[2];
	t_vec3	component[2];

	point[X] = (int)(texture_point.x * bumpmap->width - 1);
	point[Y] = (int)(texture_point.y * bumpmap->height - 1);
	get_surrounding_pixel_height(bumpmap, point[X], point[Y], height);
	offset[X] = (height[RIGHT] - height[LEFT]) / 200;
	offset[Y] = (height[UP] - height[DOWN]) / 200;
	vec[U] = unit_vector(cross((t_vec3){0, 1, 0}, *geo_normal));
	vec[V] = cross(*geo_normal, vec[U]);
	component[U] = scale_vector(vec[U], offset[X]);
	component[V] = scale_vector(vec[V], offset[Y]);
	return (unit_vector(add_3dvectors(*geo_normal, \
	add_3dvectors(component[U], component[V]))));
}

void	get_surrounding_pixel_height(t_img *bumpmap, \
int x, int y, float height[4])
{
	if (x == 0)
		height[LEFT] = get_bump_map_height(bumpmap, bumpmap->width - 1, y);
	else
		height[LEFT] = get_bump_map_height(bumpmap, x - 1, y);
	if (x == bumpmap->width - 1)
		height[RIGHT] = get_bump_map_height(bumpmap, 0, y);
	else
		height[RIGHT] = get_bump_map_height(bumpmap, x + 1, y);
	if (y == 0)
		height[UP] = get_bump_map_height(bumpmap, x, y);
	else
		height[UP] = get_bump_map_height(bumpmap, x, y - 1);
	if (y == bumpmap->height - 1)
		height[DOWN] = get_bump_map_height(bumpmap, x, y);
	else
		height[DOWN] = get_bump_map_height(bumpmap, x, y + 1);
}

float	get_bump_map_height(t_img *bumpmap, float x, float y)
{
	return (my_mlx_get_pixel_color(bumpmap, x, y) & 0xFF);
}
