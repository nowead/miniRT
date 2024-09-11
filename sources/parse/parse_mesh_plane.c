/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:38 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 12:12:10 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_planes(t_obj *plane, char **line, t_vars *vars)
{
	plane = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!plane)
		return (1);
	set_plane(line, plane);
	vars->scene.obj = plane;
	return (0);
}

int	set_plane(char **line, t_obj *plane)
{
	char	**coord;
	char	**vector;
	char	**color;

	plane->type = PLANE;
	
	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	plane->data.plane.pos = (t_point3){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
	free_lists(coord);
	
	vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
	plane->data.plane.normal = (t_vec3){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])};
	free_lists(vector);
	
	if (check_float_string(line[3]))
		return (1);
	plane->specular = ft_atof(line[3]);
	
	color = ft_split(line[4], ',');
	if (check_color(color))
		return (1);
	plane->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	
	plane->next = NULL;
	return (0);
}

int	parse_plane(char **line, t_vars *vars)
{
	t_obj	*curr;

	vars->scene.num_of_obj++;
	curr = vars->scene.obj;
	if (curr == NULL)
	{
		if (init_planes(curr, line, vars))
			return (1);
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = (t_obj *)ft_calloc(1, sizeof(t_obj));
		if (!curr->next)
			return (1);
		if (set_plane(line, curr->next))
			return (1);
	}
	return (0);
}
