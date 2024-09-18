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
	if (ft_strslen(line) != 4)
		return (1);
	if (parse_3dpoint(line[1], &vars->scene.camera.pos))
		return (1);
	if (parse_3dvector(line[2], &vars->scene.camera.dir))
		return (1);
	if (check_float_str(line[3]))
		return (1);
	vars->scene.camera.fov = ft_atof(line[3]);
	if (vars->scene.camera.fov < 0 || vars->scene.camera.fov > 180)
		return (1);
	return (0);
}
