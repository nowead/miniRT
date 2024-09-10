/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_camera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     *//*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:14:56 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/08 15:47:31 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_camera(char **line, t_vars *vars)
{
	char **coord;
	char **vector;

	if (ft_strslen(line) != 4 )
		return (1);
	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	vars->scene.camera.pos = (t_point3d){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
	vars->scene.camera.dir = (t_vector3d){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])};
	free_lists(vector);
	if (check_float_string(line[3]))
		return (1);
	vars->scene.camera.fov = ft_atof(line[3]);
	if (vars->scene.camera.fov < 0 || vars->scene.camera.fov > 180)
		return (1);
	return (0);
}
