/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:38:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/21 15:55:02 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_3dpoint(char *line, t_point3 *obj_point)
{
	char	**coord;

	if (!line)
		error_return("Error\nInvalid point", PERROR_ON);
	coord = ft_split(line, ",");
	if (check_coord(coord))
	{
		free_lists(coord);
		return (1);
	}
	*obj_point = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	return (0);
}

int	parse_3dvector(char *line, t_vec3 *obj_vec)
{
	char	**vector;

	if (!line)
		error_return("Error\nInvalid vector", PERROR_ON);
	vector = ft_split(line, ",");
	if (check_vector(vector))
	{
		free_lists(vector);
		return (1);
	}
	*obj_vec = unit_vector((t_vec3){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	free_lists(vector);
	return (0);
}

int	parse_color(char *line, t_color *obj_color)
{
	char	**color;

	if (!line)
		error_return("Error\nInvalid color", PERROR_ON);
	color = ft_split(line, ",");
	if (check_color(color))
	{
		free_lists(color);
		return (1);
	}
	obj_color->r = ft_atoi(color[0]);
	obj_color->g = ft_atoi(color[1]);
	obj_color->b = ft_atoi(color[2]);
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

	checkerboard = ft_split(line, "/");
	if (ft_strslen(checkerboard) != 4)
		return (1);
	
	color1 = ft_split(checkerboard[1], ",");
	if (check_color(color1))
	{
		free_lists(checkerboard);
		return (1);
	}
	color2 = ft_split(checkerboard[2], ",");
	if (check_color(color2))
	{
		free_lists(color1);
		free_lists(checkerboard);
		return (1);
	}
	obj_checkerboard->color1 = get_color(ft_atoi(color1[0]), ft_atoi(color1[1]), ft_atoi(color1[2]));
	obj_checkerboard->color2 = get_color(ft_atoi(color2[0]), ft_atoi(color2[1]), ft_atoi(color2[2]));
	free_lists(color1);
	free_lists(color2);

	uv = ft_split(checkerboard[3], ",");
	if (!uv)
	{
		free_lists(checkerboard);
		return (error_return("Error\nInvalid checkerboard size", PERROR_ON));
	}
	if (ft_strslen(uv) != 2 || check_decimal_str(uv[0]) || check_decimal_str(uv[1]))
	{
		free_lists(uv);
		free_lists(checkerboard);
		if (ft_strslen(uv) != 2)
			ft_putendl_fd("Error\nInvalid checkerboard size", STDERR_FILENO);
		return (1);
	}
	obj_checkerboard->width = ft_atoi(uv[0]);
	obj_checkerboard->height = ft_atoi(uv[1]);
	free_lists(uv);
	free_lists(checkerboard);
	return (0);
}


int	parse_bumpmap(char *line, t_bumpmap *obj_bumpmap)
{
	char	**color;
	char	**uv;
	char	**bumpmap;

	obj_bumpmap->bumpmap_on = 1;

	bumpmap = ft_split(line, "/");
	if (ft_strslen(bumpmap) != 4)
		return (1);
	
	color = ft_split(bumpmap[1], ",");
	if (check_color(color))
	{
		free_lists(bumpmap);
		return (1);
	}
	obj_bumpmap->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);

	uv = ft_split(bumpmap[2], ",");
	if (!uv)
	{
		free_lists(bumpmap);
		return (error_return("Error\nInvalid bumpmap size", PERROR_ON));
	}
	if (ft_strslen(uv) != 2 || check_decimal_str(uv[0]) || check_decimal_str(uv[1]))
	{
		free_lists(uv);
		free_lists(bumpmap);
		if (ft_strslen(uv) != 2)
			ft_putendl_fd("Error\nInvalid bumpmap size", STDERR_FILENO);
		return (1);
	}
	obj_bumpmap->width = ft_atoi(uv[0]);
	obj_bumpmap->height = ft_atoi(uv[1]);
	free_lists(uv);
	free_lists(bumpmap);
	return (0);
}