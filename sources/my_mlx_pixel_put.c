/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:33 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/22 17:12:47 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	convert_point(int point[2], t_img *img);

void	my_mlx_pixel_put(int x, int y, int color, t_img *img)
{
	char		*dst;
	int			point[2];

	point[0] = x;
	point[1] = y;
	convert_point(point, img);
	if (0 <= point[0] && point[0] < img->width \
	&& 0 <= point[1] && point[1] < img->height)
	{
		dst = img->data + \
		(point[1] * img->size_line) + (point[0] * (img->bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

static void convert_point(int point[2], t_img *img)
{
	point[0] = (img->width / 2) + point[0];
	point[1] = (img->height / 2) - point[1];
}

void	my_mlx_clear_window(t_vars *vars)
{
	ft_memset(vars->img.data, 0, vars->img.size_line * vars->img.height);
}

int	my_mlx_get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		dst = img->data + \
		(y * img->size_line) + (x * (img->bits_per_pixel / 8));
		return (*(int *)dst);
	}
	return (0);
}
