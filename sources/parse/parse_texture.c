/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:57:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/21 21:30:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_color_or_texture(char *line, t_obj *obj, void *mlx)
{
	if (!line)
		return (1);
	if (line[0] == 'c')
	{
		if (parse_checkerboard(line, obj))
			return (1);
	}
	else if (line[0] == 't')
	{
		if (parse_image_texture(line, obj, mlx))
			return (1);
	}
	else
	{
		obj->texture_type = COLOR;
		if (parse_color(line, &obj->color))
			return (1);
	}
	return (0);
}

int	parse_image_texture(char *line, t_obj *obj, void *mlx)
{
	t_img	**img;
	char	*filename;
	char	**texture_info;

	if (!line)
		error_return("Error\nInvalid texture", PERROR_ON);

	obj->texture_type = IMAGE;
	img = &obj->image;

	texture_info = ft_split(line, "/");
	if (!texture_info || ft_strslen(texture_info) != 2)
	{
		free_lists(texture_info);
		return (error_return("Error\nInvalid texture format", PERROR_OFF));
	}

	filename = ft_strjoin("./scenes/", texture_info[1]);
	if (!filename)
	{
		free_lists(texture_info);
		return (error_return("Error\nft_strjoin error", PERROR_ON));
	}
	(*img)->ptr = mlx_xpm_file_to_image(mlx, filename, &(*img)->width, &(*img)->height);
	free(filename);
	if (!(*img)->ptr)
	{
		free_lists(texture_info);
		return (error_return("Error\nFailed to load texture image", PERROR_OFF));
	}
	(*img)->data = mlx_get_data_addr((*img)->ptr, &(*img)->bits_per_pixel, &(*img)->size_line, &(*img)->endian);
	if (!(*img)->data)
	{
		free_lists(texture_info);
		mlx_destroy_image(mlx, (*img)->ptr);
		return (error_return("Error\nFailed to get image data", PERROR_OFF));
	}
	free_lists(texture_info);
	return (0);
}

int parse_checkerboard(char *line, t_obj *obj)
{
	char			**uv;
	char			**checkerboard;
	t_checkerboard	*obj_checkerboard;

	if (!line)
		error_return("Error\nInvalid checkerboard", PERROR_ON);
	obj->texture_type = CHECKERBOARD;
	obj_checkerboard = &obj->checkerboard;
	checkerboard = ft_split(line, "/");
	if (!checkerboard || ft_strslen(checkerboard) != 4)
		return (error_return("Error\nInvalid checkerboard", PERROR_OFF));

	if (parse_color(checkerboard[1], &obj->checkerboard.color1) \
	|| parse_color(checkerboard[2], &obj->checkerboard.color2))
	{
		free_lists(checkerboard);
		return (1);
	}

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

// int	parse_bumpmap(char *line, t_bumpmap *obj_bumpmap)
// {
// 	char	**color;
// 	char	**uv;
// 	char	**bumpmap;

// 	obj_bumpmap->bumpmap_on = 1;

// 	bumpmap = ft_split(line, "/");
// 	if (ft_strslen(bumpmap) != 4)
// 		return (1);
	
// 	color = ft_split(bumpmap[1], ",");
// 	if (check_color(color))
// 	{
// 		free_lists(bumpmap);
// 		return (1);
// 	}
// 	obj_bumpmap->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
// 	free_lists(color);

// 	uv = ft_split(bumpmap[2], ",");
// 	if (!uv)
// 	{
// 		free_lists(bumpmap);
// 		return (error_return("Error\nInvalid bumpmap size", PERROR_ON));
// 	}
// 	if (ft_strslen(uv) != 2 || check_decimal_str(uv[0]) || check_decimal_str(uv[1]))
// 	{
// 		free_lists(uv);
// 		free_lists(bumpmap);
// 		if (ft_strslen(uv) != 2)
// 			ft_putendl_fd("Error\nInvalid bumpmap size", STDERR_FILENO);
// 		return (1);
// 	}
// 	obj_bumpmap->width = ft_atoi(uv[0]);
// 	obj_bumpmap->height = ft_atoi(uv[1]);
// 	free_lists(uv);
// 	free_lists(bumpmap);
// 	return (0);
// }
