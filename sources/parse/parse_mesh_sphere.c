/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:51 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 12:13:19 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_spheres(t_obj *sphere, char **line, t_vars *vars)
{
	sphere = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!sphere)
		return (1);
	if (set_sphere(line, sphere))
		return (1);
	vars->scene.obj = sphere;
	return (0);
}

int		set_sphere(char **line, t_obj *sphere)
{
	char	**coord;
	char	**color;

	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	sphere->data.sphere.center = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	
	sphere->data.sphere.radius = ft_atoi(line[2]) / 2;
	
	if (check_float_string(line[3]))
		return (1);
	sphere->specular = ft_atof(line[3]);
	
	color = ft_split(line[4], ',');
	if (check_color(color))
		return (1);
	sphere->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	
	sphere->next = NULL;
	return (0);
}

int	parse_spheres(char **line,t_vars *vars)
{
	t_obj	*curr;

	vars->scene.num_of_obj++;
	curr = vars->scene.obj;
	if (curr == NULL)
	{
		if (init_spheres(curr, line, vars))
			return (1);
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = (t_obj *)ft_calloc(1, sizeof(t_obj));
		if (!curr->next)
            return (1);
		if (set_sphere(line, curr->next))
			return (1);
	}	
	return (0);
}
