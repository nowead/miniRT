/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/10 18:54:08 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_cylinders(t_cylinder *cylinders, char **line, t_vars *vars)
{
	cylinders = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinders)
		return (1);
	if (set_cylinder(line, cylinders))
		return (1);
	cylinders->next = NULL;
	vars->scene.cylinders = cylinders;
	return (0);
}

int     set_cylinder(char **line, t_cylinder *cylinders)
{
    char    **coord;
    char    **vector;
	char	**color;

    coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
    cylinders->center = (t_point3d){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
    free_lists(coord);
    vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
    cylinders->vector = (t_vector3d){ft_atoi(vector[0]), ft_atoi(vector[1]), ft_atoi(vector[2])};
    free_lists(vector);
	if ((check_float_string(line[3])) || check_float_string(line[4]))
		return (1);
    cylinders->diameter = ft_atoi(line[3]);
    cylinders->height = ft_atoi(line[4]);
	color = ft_split(line[5], ',');
	if (check_color(color))
		return (1);
	cylinders->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	return (0);
}

int	parse_cylinders(char **line, t_vars *vars)
{
	t_cylinder	*curr;
	t_cylinder	*cylinders;
	
	vars->scene.num_of_cylinders++;
	cylinders = vars->scene.cylinders;
	if (cylinders == NULL)
	{
		if (init_cylinders(cylinders, line, vars))
			return (1);
	}
	else
	{
		curr = cylinders;
		while (curr->next)
			curr = curr->next;
		curr->next = (t_cylinder *)malloc(sizeof(t_cylinder));
		if (!curr->next)
            return (1);
		if (set_cylinder(line, curr->next))
            return (1);
		curr->next->next = NULL;
	}
	return (0);
}
