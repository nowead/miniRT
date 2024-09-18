/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:45 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/18 18:10:56 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int set_amb_light(char **line, t_light *light)
{
	if (ft_strslen(line) != 3)
        return (1);
    if (check_float_str(line[1]))
        return (1);
    light->intens = ft_atof(line[1]);
    if (light->intens < 0 || light->intens > 1)
        return (1);
    if (parse_color(line[2], &light->color))
		return (1);
	light->color_intens.r = light->color.r / 255.0f;
	light->color_intens.g = light->color.g / 255.0f;
	light->color_intens.b = light->color.b / 255.0f;
    light->type = AMBIENT_LIGHT;
    return (0);
}

int set_point_light(char **line, t_light *light)
{
	if (ft_strslen(line) != 4)
		return (1);
	if (parse_3dpoint(line[1], &light->pos))
		return (1);
	if (check_float_str(line[2]))
		return (1);
	light->intens = ft_atof(line[2]);
	if (light->intens < 0 || light->intens > 1)
		return (1);
	if (parse_color(line[3], &light->color))
		return (1);
	light->color_intens.r = light->color.r / 255.0f;
	light->color_intens.g = light->color.g / 255.0f;
	light->color_intens.b = light->color.b / 255.0f;
	light->type = POINT_LIGHT;
	return (0);
}
