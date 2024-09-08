/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:24:39 by damin             #+#    #+#             */
/*   Updated: 2024/09/08 21:34:06 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_argv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!argv[1])
		return (1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 3], ".rt", 4) == 0)
		return (0);
	return (1);
}

void	print_parsed_vars(t_vars *vars)
{
	t_light *lights;
	t_camera *camera;

	lights = vars->scene.lights;
	camera = &vars->scene.camera;
	printf("\n");
	printf("camera pos: %f %f %f\n", camera->pos.x, camera->pos.y, camera->pos.z);
	printf("camera dir: %f %f %f\n", camera->dir.x, camera->dir.y, camera->dir.z);
	printf("camera fov: %f\n", camera->fov);
	while (lights)
	{
		printf("num_of_lights: %d\n", vars->scene.num_of_lights);
		printf("type of light: %d\n", lights->type);
		printf("light intens: %f\n", lights->intens);
		printf("light color: %d %d %d\n", (lights->color >> 16) & 0xFF, (lights->color >> 8) & 0xFF, lights->color & 0xFF);
		lights = lights->next;
	}
}

void	parse(int argc, char **argv, t_vars *vars)
{
	if (parse_argv(argc, argv))
		error_exit("Usage: ./minirt [file.rt]", PERROR_OFF);
	if (parse_rt(argv[1], vars))
		error_exit("Error", PERROR_OFF);
	print_parsed_vars(vars);
}