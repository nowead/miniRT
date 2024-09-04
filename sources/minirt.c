/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:06:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/02 16:26:08 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

int main(int argc, char **argv)
{
    t_vars  vars;

	parse(argc, argv);
    init_vars(&vars);
	init_objects(&vars.obj);
	render_scene(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win.ptr, vars.img.ptr, 0, 0);
	setup_event_hooks(&vars);
	mlx_loop(vars.mlx);
    return (EXIT_SUCCESS);
}

void	error_exit(char *err_msg, int perror_flag)
{
	if (perror_flag)
        perror(err_msg);
	else
        ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	init_vars(t_vars *vars)
{
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

void	init_objects(t_obj *obj)
{
	obj->camera = (t_point3d){0, 0, 0};
	obj->num_of_spheres = 3;
	obj->spheres = (t_sphere *)malloc(sizeof(t_sphere) * obj->num_of_spheres);
	if (!obj->spheres)
		error_exit("malloc spheres error", PERROR_ON);
	obj->spheres[0].center = (t_point3d){-5, 0, 15};
	obj->spheres[0].radius = 3;
	obj->spheres[0].color = 0x00FF00;
	
	obj->spheres[1].center = (t_point3d){0, -3, 10};
	obj->spheres[1].radius = 3;
	obj->spheres[1].color = 0xFF0000;
	
	obj->spheres[2].center = (t_point3d){5, 0, 15};
	obj->spheres[2].radius = 3;
	obj->spheres[2].color = 0x0000FF;
}
