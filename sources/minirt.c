/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:06:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/26 16:16:01 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	parse_scene(argc, argv, &vars);
	setup_event_hooks(&vars);
	draw_next_frame(&vars);
	mlx_loop(vars.mlx);
	return (EXIT_SUCCESS);
}

void	init_vars(t_vars *vars)
{
	*vars = (t_vars){};
	vars->mlx = mlx_init();
	if (!vars->mlx)
		error_exit("mlx_init error", PERROR_OFF);
	vars->win.width = 1080;
	vars->win.height = 1080;
	vars->win.ptr = mlx_new_window(vars->mlx, \
	vars->win.width, vars->win.height, "miniRT");
	if (!vars->win.ptr)
		error_exit("mlx_new_window error", PERROR_OFF);
	vars->img.width = vars->win.width;
	vars->img.height = vars->win.height;
	vars->img.ptr = mlx_new_image(vars->mlx, vars->img.width, vars->img.height);
	if (!vars->img.ptr)
		error_exit("mlx_new_image error", PERROR_OFF);
	vars->img.data = mlx_get_data_addr(vars->img.ptr, \
	&vars->img.bits_per_pixel, &vars->img.size_line, &vars->img.endian);
	if (!vars->img.data)
		error_exit("mlx_get_data_addr error", PERROR_OFF);
}

void	draw_next_frame(t_vars *vars)
{
	my_mlx_clear_window(vars);
	render_scene(vars);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars->img.ptr);
	mlx_put_image_to_window(vars->mlx, vars->win.ptr, vars->img.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, vars->win.ptr);
}

int	error_return(char *err_msg, int perror_flag)
{
	if (perror_flag)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
	return (1);
}

void	error_exit(char *err_msg, int perror_flag)
{
	if (perror_flag)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
