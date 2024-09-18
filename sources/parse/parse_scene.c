/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:24:39 by damin             #+#    #+#             */
/*   Updated: 2024/09/18 14:20:57 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_checkerboard(t_obj *obj);
void	print_parsed_vars(t_vars *vars);

void	parse_scene(int argc, char **argv, t_vars *vars)
{
	if (parse_argv(argc, argv))
		error_exit("Usage: ./minirt [file.rt]", PERROR_OFF);
	if (parse_rt_file(argv[1], vars))
		error_exit("Error", PERROR_OFF);
	print_parsed_vars(vars);
}

int	parse_argv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!argv[1])
		return (1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 3], ".rt", 4) == 0)
		return (0);
	return (1);
}

int	parse_rt_file(char *argv, t_vars *vars)
{
	char	*file;
	int		fd;

	file = ft_strjoin("scenes/", argv);
	if (!file)
		error_exit("malloc failed", PERROR_ON);
	fd = open(file, O_RDWR);;
	if (fd == -1)
		error_exit("open failed", PERROR_ON);
	free(file);
    if (parse_lines_from_rt_file(fd, vars))
	{
		clear_scene(vars);
		close(fd);
		return (1);
	}
	if (close(fd))
		error_exit("close failed", PERROR_ON);
	return (0);
}

int	parse_lines_from_rt_file(int fd, t_vars *vars)
{
    int		err_flag;
    char    *temp;
    char    **line;

    err_flag = 0;
    while (!err_flag)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		printf("%s", temp);	// for debugging
		if (temp[0] == '\n')
		{
			free(temp);
			continue ;
		}
		line = ft_split(truncate_end_nl(temp), ' ');
		if (!line)
			err_flag = 1;
		if (!err_flag)
			err_flag = parse_scene_element(line, vars);
		free(temp);
		free_lists(line);
	}
	return (err_flag);
}

void	clear_scene(t_vars *vars)
{
	t_light		*lights;
	t_obj		*obj;

	lights = vars->scene.lights;
	obj = vars->scene.obj;
	while (lights)
	{
		vars->scene.lights = lights->next;
		free(lights);
		lights = vars->scene.lights;
	}
	while (obj)
	{
		vars->scene.obj = obj->next;
		free(obj);
		obj = vars->scene.obj;
	}
}

void	print_checkerboard(t_obj *obj)
{
	printf("checkerboard color1: %d %d %d\n", (obj->checkerboard.color1 >> 16) & 0xFF, (obj->checkerboard.color1 >> 8) & 0xFF, obj->checkerboard.color1 & 0xFF);
	printf("checkerboard color2: %d %d %d\n", (obj->checkerboard.color2 >> 16) & 0xFF, (obj->checkerboard.color2 >> 8) & 0xFF, obj->checkerboard.color2 & 0xFF);
	printf("checkerboard width: %d\n", obj->checkerboard.width);
	printf("checkerboard height: %d\n", obj->checkerboard.height);
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
	printf("num_of_obj: %d\n\n", vars->scene.num_of_obj);
	
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
			if (obj->checkerboard.checkerboard_on)
				print_checkerboard(obj);
			else
				printf("plane color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		else if (obj->type == SPHERE)
		{
			printf("sphere pos: %g %g %g\n", obj->data.sphere.center.x, obj->data.sphere.center.y, obj->data.sphere.center.z);
			printf("sphere rad: %g\n", obj->data.sphere.radius);
			printf("sphere specular: %d\n", obj->specular);
			if (obj->checkerboard.checkerboard_on)
				print_checkerboard(obj);
			else
				printf("sphere color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		else if (obj->type == CYLINDER)
		{
			printf("cylinder pos: %g %g %g\n", obj->data.cylinder.center.x, obj->data.cylinder.center.y, obj->data.cylinder.center.z);
			printf("cylinder dir: %g %g %g\n", obj->data.cylinder.axis.x, obj->data.cylinder.axis.y, obj->data.cylinder.axis.z);
			printf("cylinder rad: %g\n", obj->data.cylinder.radius);
			printf("cylinder height: %g\n", obj->data.cylinder.height);
			if (obj->checkerboard.checkerboard_on)
				print_checkerboard(obj);
			else
				printf("cylinder color: %d %d %d\n", (obj->color >> 16) & 0xFF, (obj->color >> 8) & 0xFF, obj->color & 0xFF);
			printf("\n");
		}
		obj = obj->next;
	}
}
