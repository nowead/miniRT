/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:06:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/09 20:56:09 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	chk(void){
	system("leaks miniRT");
}

int main(int argc, char **argv)
{
    t_vars  vars;

	atexit(chk);
    init_vars(&vars);
	init_scene(&vars.scene);
	parse(argc, argv, &vars);
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

void	init_scene(t_scene *scene)
{
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->num_of_lights = 0;
	scene->num_of_spheres = 0;
	scene->num_of_planes = 0;
	scene->num_of_cylinders = 0;
}

// void	init_scene(t_scene *scene)
// {
// 	scene->camera.pos = (t_point3d){0, 0, 0};

// 	scene->num_of_lights = 3;
// 	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_of_lights);
// 	if (!scene->lights)
// 		error_exit("malloc lights error", PERROR_ON);
// 	scene->lights[0].type = AMBIENT_LIGHT;
// 	scene->lights[0].intens = 0.2;
	
// 	scene->lights[1].type = POINT_LIGHT;
// 	scene->lights[1].pos = (t_point3d){2, 1, 0};
// 	scene->lights[1].intens = 0.6;
	
// 	scene->lights[2].type = DIRECTIONAL_LIGHT;
// 	scene->lights[2].dir = (t_vector3d){1, 4, 4};
// 	scene->lights[2].intens = 0.2;

// 	scene->num_of_spheres = 4;
// 	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * scene->num_of_spheres);
// 	if (!scene->spheres)
// 		error_exit("malloc spheres error", PERROR_ON);
// 	scene->spheres[0].center = (t_point3d){-2, 0, 4};
// 	scene->spheres[0].radius = 1;
// 	scene->spheres[0].color = GREEN;
// 	scene->spheres[0].specular = 10;
	
// 	scene->spheres[1].center = (t_point3d){0, -1, 3};
// 	scene->spheres[1].radius = 1;
// 	scene->spheres[1].color = RED;
// 	scene->spheres[1].specular = 500;
	
// 	scene->spheres[2].center = (t_point3d){2, 0, 4};
// 	scene->spheres[2].radius = 1;
// 	scene->spheres[2].color = BLUE;
// 	scene->spheres[2].specular = 500;

// 	scene->spheres[3].center = (t_point3d){0, -5001, 0};
// 	scene->spheres[3].radius = 5000;
// 	scene->spheres[3].color = YELLOW;
// 	scene->spheres[3].specular = 1000;
// }
