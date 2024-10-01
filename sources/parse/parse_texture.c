/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:57:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/10/01 14:35:01 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_color_or_texture(char *line, t_obj *obj, void *mlx)
{
	if (!line)
		return (error_return("Error\nInvalid color or texture", PERROR_ON));
	if (ft_strncmp(line, "c/", 2) == 0)
	{
		obj->texture_type = CHECKERBOARD;
		if (parse_checkerboard(line, &obj->checkerboard))
			return (1);
	}
	else if (ft_strncmp(line, "t/", 2) == 0)
	{
		obj->texture_type = IMAGE;
		if (parse_texture_image(line, &obj->image, mlx))
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

int	parse_texture_image(char *line, t_img *img, void *mlx)
{
	char	**texture_info;

	texture_info = ft_split(line, "/");
	if (!texture_info || ft_strslen(texture_info) != 2)
	{
		free_lists(texture_info);
		return (error_return("Error\nInvalid image", PERROR_OFF));
	}
	if (parse_xpm_file_to_image(texture_info[1], img, mlx))
	{
		free_lists(texture_info);
		return (1);
	}
	free_lists(texture_info);
	return (0);
}

int	parse_xpm_file_to_image(char *line, t_img *img, void *mlx)
{
	char	*filename;

	filename = ft_strjoin("./textures/", line);
	if (!filename)
		return (error_return("Error\nft_strjoin error", PERROR_ON));
	img->ptr = mlx_xpm_file_to_image(mlx, filename, &img->width, &img->height);
	free(filename);
	if (!img->ptr)
		return (error_return("Error\nFailed to load image", PERROR_OFF));
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, \
	&img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(mlx, img->ptr);
		return (error_return("Error\nFailed to get image data", PERROR_OFF));
	}
	return (0);
}

int	parse_uv(char **checkerboard, t_checkerboard *obj_checkerboard)
{
	char	**uv;

	uv = ft_split(checkerboard[3], ",");
	if (!uv)
	{
		free_lists(checkerboard);
		return (error_return("Error\nInvalid checkerboard size", PERROR_ON));
	}
	if (ft_strslen(uv) != 2 || check_decimal_str(uv[0]) || \
	check_decimal_str(uv[1]) || ft_strlen(uv[0]) > 5 || ft_strlen(uv[1]) > 5)
	{
		free_lists(uv);
		free_lists(checkerboard);
		if (ft_strslen(uv) != 2)
			ft_putendl_fd("Error\nInvalid checkerboard size", STDERR_FILENO);
		return (1);
	}
	obj_checkerboard->columns = ft_atoi(uv[0]);
	obj_checkerboard->rows = ft_atoi(uv[1]);
	free_lists(uv);
	return (0);
}

int	parse_checkerboard(char *line, t_checkerboard *obj_checkerboard)
{
	char			**checkerboard;

	if (!line)
		error_return("Error\nInvalid checkerboard", PERROR_ON);
	checkerboard = ft_split(line, "/");
	if (!checkerboard || ft_strslen(checkerboard) != 4)
		return (error_return("Error\nInvalid checkerboard", PERROR_OFF));
	if (parse_color(checkerboard[1], &obj_checkerboard->color1) \
	|| parse_color(checkerboard[2], &obj_checkerboard->color2))
	{
		free_lists(checkerboard);
		return (1);
	}
	if (parse_uv(checkerboard, obj_checkerboard))
		return (1);
	free_lists(checkerboard);
	return (0);
}
