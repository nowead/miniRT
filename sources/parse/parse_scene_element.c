/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:14:10 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 14:38:08 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_scene_element(char **line, t_vars *vars)
{
	int	err_flag;

	err_flag = 0;
	if (ft_strncmp(line[0], "C", 2) == 0)
		err_flag = parse_camera(line, vars);
	else if (ft_strncmp(line[0], "A", 2) == 0)
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
	{
		ft_putstr_fd("Error: No such identifier", STDERR_FILENO);
		ft_putendl_fd(line[0], STDERR_FILENO);
		err_flag = 1;
	}
	return (err_flag);
}

int	parse_camera(char **line, t_vars *vars)
{
	if (ft_strslen(line) != 4)
		return (error_return("Error\nCamera format: C [pos] [dir] [fov]", \
		PERROR_OFF));
	if (parse_3dpoint(line[1], &vars->scene.camera.pos))
		return (1);
	if (parse_3dvector(line[2], &vars->scene.camera.dir))
		return (1);
	if (check_float_str(line[3]))
		return (1);
	vars->scene.camera.fov = ft_atof(line[3]);
	if (vars->scene.camera.fov < 0 || vars->scene.camera.fov > 180)
		error_return("Error\nFOV must be between 0 and 180", PERROR_OFF);
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
