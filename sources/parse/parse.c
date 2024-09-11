/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:24:39 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 12:31:49 by seonseo          ###   ########.fr       */
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
	t_light		*lights;
	t_obj		*obj;
	t_camera	*camera;

	camera = &vars->scene.camera;
	lights = vars->scene.lights;
	obj = vars->scene.obj;
	
	printf("\n\n");
	printf("camera pos: %g %g %g\n", camera->pos.x, camera->pos.y, camera->pos.z);
	printf("camera dir: %g %g %g\n", camera->dir.x, camera->dir.y, camera->dir.z);
	printf("camera fov: %d\n\n", camera->fov);
	
	printf("num_of_lights: %d\n", vars->scene.num_of_lights);
	printf("num_of_planes: %d\n", vars->scene.num_of_obj);
	
	while (lights)
	{
		printf("type of light: %d\n", lights->type);
		if (lights->type == POINT_LIGHT)
			printf("light pos: %g %g %g\n", lights->pos.x, lights->pos.y, lights->pos.z);
		printf("light intens: %g\n", lights->intens);
		printf("light color: %d %d %d\n", (lights->color >> 16) & 0xFF, (lights->color >> 8) & 0xFF, lights->color & 0xFF);		
		printf("\n");
		lights = lights->next;
	}
	
	while (obj)
	{
		if (obj->type == PLANE)
		{
			printf("plane pos: %g %g %g\n", obj->data.plane.pos.x, obj->data.plane.pos.y, obj->data.plane.pos.z);
			printf("plane dir: %g %g %g\n", obj->data.plane.normal.x, obj->data.plane.normal.y, obj->data.plane.normal.z);
			printf("plane color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		else if (obj->type == SPHERE)
		{
			printf("sphere pos: %g %g %g\n", obj->data.sphere.center.x, obj->data.sphere.center.y, obj->data.sphere.center.z);
			printf("sphere rad: %g\n", obj->data.sphere.radius);
			printf("sphere color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		else if (obj->type == CYLINDER)
		{
			printf("cylinder pos: %g %g %g\n", obj->data.cylinder.center.x, obj->data.cylinder.center.y, obj->data.cylinder.center.z);
			printf("cylinder dir: %g %g %g\n", obj->data.cylinder.vector.x, obj->data.cylinder.vector.y, obj->data.cylinder.vector.z);
			printf("cylinder rad: %g\n", obj->data.cylinder.radius);
			printf("cylinder height: %g\n", obj->data.cylinder.height);
			printf("cylinder color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		obj = obj->next;
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
