/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:38:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/16 15:30:48 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_3dpoint(char *line, t_point3 *obj_point)
{
	char	**coord;

	coord = ft_split(line, ',');
	if (check_coord(coord))
		return (1);
	*obj_point = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	return (0);
}

int	parse_3dvector(char *line, t_vec3 *obj_vec)
{
	char	**vector;

	vector = ft_split(line, ',');
	if (check_vector(vector))
		return (1);
	*obj_vec = (t_vec3){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])};
	free_lists(vector);
	return (0);
}

int	parse_color(char *line, int *obj_color)
{
	char	**color;

	color = ft_split(line, ',');
	if (check_color(color))
		return (1);
	*obj_color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	return (0);
}

int parse_checkerboard(char *line, t_checkerboard *obj_checkerboard)
{
	char	**color1;
	char	**color2;
	char	**uv;
	char	**checkerboard;

	obj_checkerboard->checkerboard_on = 1;
	checkerboard = ft_split(line, '/');
	if (ft_strslen(checkerboard) != 4)
		return (1);
	color1 = ft_split(checkerboard[1], ',');
	color2 = ft_split(checkerboard[2], ',');
	if (check_color(color1) || check_color(color2))
		return (1);
	obj_checkerboard->color1 = get_color(ft_atoi(color1[0]), ft_atoi(color1[1]), ft_atoi(color1[2]));
	obj_checkerboard->color2 = get_color(ft_atoi(color2[0]), ft_atoi(color2[1]), ft_atoi(color2[2]));
	free_lists(color1);
	free_lists(color2);
	uv = ft_split(checkerboard[3], ',');
	if (!uv || ft_strslen(uv) != 2 || check_decimal_str(uv[0]) || check_decimal_str(uv[1]))
		return (1);
	obj_checkerboard->width = ft_atoi(uv[0]);
	obj_checkerboard->height = ft_atoi(uv[1]);
	free_lists(uv);
	free_lists(checkerboard);
	return (0);
}
