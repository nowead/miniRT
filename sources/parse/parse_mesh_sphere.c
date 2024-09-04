/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:51 by damin             #+#    #+#             */
/*   Updated: 2024/09/04 19:22:34 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_spheres(t_sphere *spheres, char **line)
{
	spheres = (t_sphere *)malloc(sizeof(t_sphere));
	if (!spheres)
		return (1);
	if (set_sphere(line, spheres))
		return (1);
	spheres->next = NULL;
	return (0);
}

int		set_sphere(char **line, t_sphere *spheres)
{
	char	**coord;
	char	**color;

	coord = ft_split(line[1], ",");
	if (!coord)
		return (1);
	spheres->center = (t_point3d){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
	free(coord);
	spheres->radius = ft_atoi(line[2]) / 2;
	color = ft_split(line[3], ",");
	spheres->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	if (spheres->color == -1)
		return (1);
	return (0);
}

int	parse_spheres(char **line,t_vars *vars)
{
	t_sphere	*curr;
	t_sphere	*spheres;

	vars->scene.num_of_spheres++;
	spheres = vars->scene.spheres;
	if (spheres == NULL)
	{
		if (init_spheres(spheres, line))
			return (1);
	}
	else
	{
		curr = spheres;
		while (curr->next)
			curr = curr->next;
		curr->next = (t_sphere *)malloc(sizeof(t_sphere));
		if (set_sphere(line, curr->next))
			return (1);
		curr->next->next = NULL;
	}	
	return (0);
}
