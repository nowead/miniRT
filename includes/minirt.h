/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:25:52 by damin             #+#    #+#             */
/*   Updated: 2024/08/30 21:03:36 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"

// mlx 구조체
typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

// image data 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

//함수 선언부
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int print_image(void);
int exit_hook();
int	key_hook(int keycode, t_vars *vars);

#endif
