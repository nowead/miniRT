/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mesh_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:38 by damin             #+#    #+#             */
/*   Updated: 2024/09/08 16:36:04 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_planes(t_plane *planes, char **line)
{
	planes = (t_plane *)malloc(sizeof(t_plane));
	if (!planes)
		return (1);
	set_plane(line, planes);
	planes->next = NULL;
	return (0);
}

int	set_plane(char **line, t_plane *planes)
{
	char	**coord;
	char	**vector;
	char	**color;

	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	planes->coord = (t_point3d){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
	free(coord);
	vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
	planes->vector = (t_vector3d){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])};
	free(vector);
	color = ft_split(line[3], ',');
	if (check_color(color))
		return (1);
	planes->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free(color);
	return (0);
}

int	parse_plane(char **line, t_vars *vars)
{
	t_plane *planes;
	t_plane	*curr;

	vars->scene.num_of_planes++;
	planes = vars->scene.planes;
	if (planes == NULL)
	{
		if (init_planes(planes, line))
			return (1);
	}
	else
	{
		curr = planes;
		while (curr->next)
			curr = curr->next;
		curr->next = (t_plane *)malloc(sizeof(t_plane));
		if (!curr->next)
			return (1);
		if (set_plane(line, curr->next))
			return (1);
		curr->next->next = NULL;
	}
	return (0);
}
