/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 12:15:23 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_cylinders(t_obj *cylinder, char **line, t_vars *vars)
{
	cylinder = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!cylinder)
		return (1);
	if (set_cylinder(line, cylinder))
		return (1);
	vars->scene.obj = cylinder;
	return (0);
}

int     set_cylinder(char **line, t_obj *cylinder)
{
    char    **coord;
    char    **vector;
	char	**color;

	cylinder->type = CYLINDER;
	
    coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
    cylinder->data.cylinder.center = (t_point3){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
    free_lists(coord);
	
    vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
    cylinder->data.cylinder.vector = (t_vec3){ft_atoi(vector[0]), ft_atoi(vector[1]), ft_atoi(vector[2])};
    free_lists(vector);
	
	if ((check_float_string(line[3])) || check_float_string(line[4]) || check_float_string(line[5]))
		return (1);
    cylinder->data.cylinder.radius = ft_atoi(line[3]) / 2;
    cylinder->data.cylinder.height = ft_atoi(line[4]);
	cylinder->specular = ft_atof(line[5]);

	color = ft_split(line[6], ',');
	if (check_color(color))
		return (1);
	cylinder->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	
	cylinder->next = NULL;
	return (0);
}

int	parse_cylinders(char **line, t_vars *vars)
{
	t_obj	*curr;
	
	vars->scene.num_of_obj++;
	curr = vars->scene.obj;
	if (curr == NULL)
	{
		if (init_cylinders(curr, line, vars))
			return (1);
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = (t_obj *)ft_calloc(1, sizeof(t_obj));
		if (!curr->next)
            return (1);
		if (set_cylinder(line, curr->next))
            return (1);
	}
	return (0);
}
