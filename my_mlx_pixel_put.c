/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:33 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/30 20:10:52 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.c"

void	my_mlx_pixel_put(int x, int y, int color, t_img *img)
{
	char		*dst;
	t_point2d	point;

	point = convert_point((t_point2d){x, y}, img);
	dst = img->data + \
	(point.y * img->size_line) + (point.x * (img->bits_per_pixel / 8));
	*(int *)dst = color;
}

t_point2d convert_point(t_point2d point, t_img *img)
{
	point.x = (img->width / 2) + point.x;
	point.y = (img->height / 2) - point.y;
	return (point);
}
