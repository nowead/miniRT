/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_ambient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:45 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/11 15:41:56 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int set_amb_light(char **line, t_light *lights)
{
    char    **color;

    if (ft_strslen(line) != 3)
        return (1);
    if (check_float_str(line[1]))
        return (1);
    lights->intens = ft_atof(line[1]);
    if (lights->intens < 0 || lights->intens > 1)
        return (1);
    color = ft_split(line[2], ',');
    if (check_color(color))
        return (1);
    lights->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_lists(color);
    lights->type = AMBIENT_LIGHT;
    return (0);
}

int set_point_light(char **line, t_light *lights)
{
	char	**coord;
	char	**color;

	if (ft_strslen(line) != 4)
		return (1);
	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	lights->pos = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	if (check_float_str(line[2]))
		return (1);
	lights->intens = ft_atof(line[2]);
	if (lights->intens < 0 || lights->intens > 1)
		return (1);
	color = ft_split(line[3], ',');
	if (check_color(color))
		return (1);
	lights->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	lights->type = POINT_LIGHT;
	return (0);
}
