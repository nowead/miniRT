/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_point_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:51:31 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/10 18:53:29 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int init_point_light(t_light *lights, char **line, t_vars *vars)
{
	lights = (t_light *)malloc(sizeof(t_light));
	if (!lights)
		return (1);
	if (set_point_light(line, lights))
		return (1);
	lights->next = NULL;
	vars->scene.lights = lights;
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
	lights->pos = (t_point3d){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	if (check_float_string(line[2]))
		return (1);
	lights->ratio = ft_atof(line[2]);
	if (lights->ratio < 0 || lights->ratio > 1)
		return (1);
	color = ft_split(line[3], ',');
	if (check_color(color))
		return (1);
	lights->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	lights->type = POINT_LIGHT;
	return (0);
}

int parse_point_light(char **line, t_vars *vars)
{
	t_light *curr;
	t_light *lights;

	vars->scene.num_of_lights++;
	lights = vars->scene.lights;
	if (lights == NULL)
	{
		if (init_point_light(lights, line, vars))
			return (1);
	}
	else
	{
		curr = lights;
		while (curr->next)
			curr = curr->next;
		curr->next = (t_light *)malloc(sizeof(t_light));
		if (!curr->next)
			return (1);
		if (set_point_light(line, curr->next))
			return (1);
		curr->next->next = NULL;
	}
	return (0);
}