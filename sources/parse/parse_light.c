/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:45 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/19 14:20:22 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int set_amb_light(char **line, t_light *light)
{
	if (ft_strslen(line) != 3)
        return (error_return("Error\nAmbient light format: A [intensity] [color]", PERROR_OFF));
    if (check_float_str(line[1]))
        return (1);
    light->intens = ft_atof(line[1]);
    if (light->intens < 0 || light->intens > 1)
        return (error_return("Error\nAmbient light intensity must be between 0 and 1", PERROR_OFF));
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
		return (error_return("Error\nPoint light format: L [pos] [intensity] [color]", PERROR_OFF));
	if (parse_3dpoint(line[1], &light->pos))
		return (1);
	if (check_float_str(line[2]))
		return (1);
	light->intens = ft_atof(line[2]);
	if (light->intens < 0 || light->intens > 1)
		return (error_return("Error\nPoint light intensity must be between 0 and 1", PERROR_OFF));
	if (parse_color(line[3], &light->color))
		return (1);
	light->color_intens.r = light->color.r / 255.0f;
	light->color_intens.g = light->color.g / 255.0f;
	light->color_intens.b = light->color.b / 255.0f;
	light->type = POINT_LIGHT;
	return (0);
}
