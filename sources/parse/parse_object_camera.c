/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_camera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mindaewon <mindaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:14:56 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/07 15:41:15 by mindaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_camera(char **line, t_vars *vars)
{
    char **coord;
    char **vector;

    if (ft_strslen(line) != 5)
        return (1);
    if (check_coord(&line[1]))
        return (1);
    vars->scene.camera.coord = (t_point3d){ft_atof(line[1]), ft_atof(line[2]), ft_atof(line[3])};
    if (check_vector(&line[4]))
        return (1);
    vars->scene.camera.vector = (t_vector3d){ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6])};
    if (vars->scene.camera.vector.x < -1 || vars->scene.camera.vector.x > 1 || vars->scene.camera.vector.y < -1 || vars->scene.camera.vector.y > 1 || vars->scene.camera.vector.z < -1 || vars->scene.camera.vector.z > 1)
        return (1);
    if (check_float_string(line[7]))
        return (1);
    vars->scene.camera.fov = ft_atof(line[7]);
    return (0);
}