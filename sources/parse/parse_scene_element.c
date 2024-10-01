/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:14:10 by seonseo           #+#    #+#             */
/*   Updated: 2024/10/01 15:21:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_scene_element(char **line, t_vars *vars)
{
	t_scene	*scene;
	int		err_flag;

	scene = &vars->scene;
	err_flag = 0;
	if (!scene->camera.camera_flag && ft_strncmp(line[0], "C", 2) == 0)
		err_flag = parse_camera(line, vars);
	else if (!is_there_amb(scene->lights) && ft_strncmp(line[0], "A", 2) == 0)
		err_flag = parse_light(line, vars, set_amb_light);
	else if (ft_strncmp(line[0], "L", 2) == 0)
		err_flag = parse_light(line, vars, set_point_light);
	else if (ft_strncmp(line[0], "pl", 3) == 0)
		err_flag = parse_object(line, vars, set_plane);
	else if (ft_strncmp(line[0], "sp", 3) == 0)
		err_flag = parse_object(line, vars, set_sphere);
	else if (ft_strncmp(line[0], "cy", 3) == 0)
		err_flag = parse_object(line, vars, set_cylinder);
	else if (ft_strncmp(line[0], "co", 3) == 0)
		err_flag = parse_object(line, vars, set_cone);
	else
		return (error_return("Error: Invalid identifier", PERROR_OFF));
	return (err_flag);
}

int	parse_camera(char **line, t_vars *vars)
{
	if (ft_strslen(line) != 4)
		return (error_return("Error\nCamera format: C [pos] [dir] [fov]", \
		PERROR_OFF));
	vars->scene.camera.camera_flag = 1;
	if (parse_3dpoint(line[1], &vars->scene.camera.pos))
		return (1);
	if (parse_3dvector(line[2], &vars->scene.camera.dir))
		return (1);
	if (check_decimal_str(line[3]))
		return (1);
	vars->scene.camera.fov = ft_atoi(line[3]);
	if (vars->scene.camera.fov == 180)
		vars->scene.camera.fov = 179;
	if (ft_strlen(line[3]) > 3 || \
	vars->scene.camera.fov < 0 || vars->scene.camera.fov > 180)
		return (error_return("Error\nFOV must be between 0 and 180", \
		PERROR_OFF));
	return (0);
}

int	is_there_amb(t_light *lights)
{
	t_light	*curr;

	if (!lights)
		return (0);
	curr = lights;
	while (curr)
	{
		if (curr->type == AMBIENT_LIGHT)
			return (1);
		curr = curr -> next;
	}
	return (0);
}

int	parse_light(char **line, t_vars *vars, \
int (*set_light)(char **line, t_light *light))
{
	t_light	*curr;
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (error_return("Error\nMalloc failed", PERROR_ON));
	if (set_light(line, light))
		return (1);
	curr = vars->scene.lights;
	if (curr == NULL)
		vars->scene.lights = light;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = light;
	}
	return (0);
}

int	parse_object(char **line, t_vars *vars, \
int (*set_obj)(char **line, t_obj *obj, void *mlx))
{
	t_obj	*obj;
	t_obj	*curr;

	obj = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!obj)
		return (error_return("Error\nMalloc failed", PERROR_ON));
	if (set_obj(line, obj, vars->mlx))
		return (1);
	curr = vars->scene.obj;
	if (curr == NULL)
		vars->scene.obj = obj;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = obj;
	}
	return (0);
}
