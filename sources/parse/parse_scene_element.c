/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_scene_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:41:44 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 11:46:21 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_scene_element(char **line, t_vars *vars)
{
	int	err_flag;

	err_flag = 0;
	if (ft_strncmp(line[0], "C", 2) == 0)
		err_flag = parse_camera(line ,vars);
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
	else
	{
		ft_putstr_fd("Error: No such identifier", STDERR_FILENO);
		ft_putendl_fd(line[0], STDERR_FILENO);
		err_flag = 1;
	}
	if (err_flag)
		return (1);
	return (0);
}

int	parse_light(char **line, t_vars *vars, int (*set_light)(char **line, t_light *light))
{
	t_light *curr;
	t_light *light;

	vars->scene.num_of_lights++;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (1);
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

int	parse_object(char **line,t_vars *vars, int (*set_obj)(char **line, t_obj *obj))
{
	t_obj	*obj;
	t_obj	*curr;

	vars->scene.num_of_obj++;

	obj = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!obj)
		return (1);
	if (set_obj(line, obj))
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
