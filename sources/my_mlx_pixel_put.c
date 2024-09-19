/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:33 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/19 20:17:39 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_point2 convert_point(t_point2 point, t_img *img);

void	my_mlx_pixel_put(int x, int y, int color, t_img *img)
{
	char		*dst;
	t_point2	point;

	point = convert_point((t_point2){x, y}, img);
	if (0 <= point.x && point.x < img->width \
	&& 0 <= point.y && point.y < img->height)
	{
		dst = img->data + \
		(point.y * img->size_line) + (point.x * (img->bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

static t_point2 convert_point(t_point2 point, t_img *img)
{
	point.x = (img->width / 2) + point.x;
	point.y = (img->height / 2) - point.y;
	return (point);
}

void	my_mlx_clear_window(t_vars *vars)
{
	ft_memset(vars->img.data, 0, vars->img.size_line * vars->img.height);
}
