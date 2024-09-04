/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:50:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/04 19:42:43 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_vector_range(t_vector3d vec)
{
	return (0);
}

int check_color_string(char **color)
{
	int	i;
	int j;
	
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (ft_isdigit(color[i][j]))
			j++;
		if (j == 0 || color[i][j] != '\0')
			return (1);
		i++;
	}
	reutrn (0);
}

int get_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (r << 16 | g << 8 | b);
}

int	is_num()
{
	
}