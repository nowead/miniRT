/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:24:39 by damin             #+#    #+#             */
/*   Updated: 2024/09/10 21:11:50 by seonseo          ###   ########.fr       */
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
	t_sphere *spheres;
	t_cylinder *cylinders;
	t_plane *planes;
	t_camera *camera;

	lights = vars->scene.lights;
	camera = &vars->scene.camera;
	spheres = vars->scene.spheres;
	cylinders = vars->scene.cylinders;
	planes = vars->scene.planes;
	
	printf("\n\n");
	printf("camera pos: %f %f %f\n", camera->pos.x, camera->pos.y, camera->pos.z);
	printf("camera dir: %f %f %f\n", camera->dir.x, camera->dir.y, camera->dir.z);
	printf("camera fov: %f\n\n", camera->fov);
	
	printf("num_of_lights: %d\n", vars->scene.num_of_lights);
	printf("num_of_planes: %d\n", vars->scene.num_of_planes);
	printf("num_of_spheres: %d\n", vars->scene.num_of_spheres);
	printf("num_of_cylinders: %d\n\n", vars->scene.num_of_cylinders);
	
	while (lights)
	{
		printf("type of light: %d\n", lights->type);
		if (lights->type == POINT_LIGHT)
			printf("light pos: %f %f %f\n", lights->pos.x, lights->pos.y, lights->pos.z);
		printf("light ratio: %f\n", lights->ratio);
		printf("light color: %d %d %d\n", (lights->color >> 16) & 0xFF, (lights->color >> 8) & 0xFF, lights->color & 0xFF);		
		printf("\n");
		lights = lights->next;
	}
	
	while (planes)
	{
		printf("plane pos: %f %f %f\n", planes->coord.x, planes->coord.y, planes->coord.z);
		printf("plane dir: %f %f %f\n", planes->vector.x, planes->vector.y, planes->vector.z);
		printf("plane color: %d %d %d\n", (planes->color >> 16) & 0xFF, (planes->color >> 8) & 0xFF, planes->color & 0xFF);
		printf("\n");
		planes = planes->next;
	}
	
	while (spheres)
	{
		printf("sphere pos: %f %f %f\n", spheres->center.x, spheres->center.y, spheres->center.z);
		printf("sphere rad: %f\n", spheres->radius);
		printf("sphere color: %d %d %d\n", (spheres->color >> 16) & 0xFF, (spheres->color >> 8) & 0xFF, spheres->color & 0xFF);
		printf("\n");
		spheres = spheres->next;
	}
	
	while (cylinders)
	{
		printf("cylinder pos: %f %f %f\n", cylinders->center.x, cylinders->center.y, cylinders->center.z);
		printf("cylinder dir: %f %f %f\n", cylinders->vector.x, cylinders->vector.y, cylinders->vector.z);
		printf("cylinder rad: %f\n", cylinders->diameter / 2);
		printf("cylinder height: %f\n", cylinders->height);
		printf("cylinder color: %d %d %d\n", (cylinders->color >> 16) & 0xFF, (cylinders->color >> 8) & 0xFF, cylinders->color & 0xFF);
		printf("\n");
		cylinders = cylinders->next;
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