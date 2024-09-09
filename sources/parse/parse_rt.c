/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:41:44 by damin             #+#    #+#             */
/*   Updated: 2024/09/09 20:54:59 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*truncate_end_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
	return (str);
}

int	parse_line(char **line, t_vars *vars, int *parse_err_flag)
{
	if (ft_strncmp(line[0], "A", 2) == 0)
		*parse_err_flag = parse_amb_light(line, vars);
	else if (ft_strncmp(line[0], "C", 2) == 0)
		*parse_err_flag = parse_camera(line ,vars);
	else if (ft_strncmp(line[0], "L", 2) == 0)
		*parse_err_flag = parse_point_light(line, vars);
	else if (ft_strncmp(line[0], "pl", 3) == 0)
		*parse_err_flag = parse_plane(line, vars);
	else if (ft_strncmp(line[0], "sp", 3) == 0)
		*parse_err_flag = parse_spheres(line, vars);
	else if (ft_strncmp(line[0], "cy", 3) == 0)
		*parse_err_flag = parse_cylinders(line, vars);
	else
	{
		ft_putstr_fd("Error: No such identifier",STDERR_FILENO);
		ft_putendl_fd(line[0], 2);
		*parse_err_flag = 1;
	}
	if (*parse_err_flag)
		return (1);
	return (0);
}

int	get_line(int fd, t_vars *vars)
{
    int		parse_err_flag;
    char    *temp;
    char    **line;

    parse_err_flag = 0;
    while (!parse_err_flag)
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
			parse_err_flag = 1;
		if (!parse_err_flag && parse_line(line, vars, &parse_err_flag))
			parse_err_flag = 1;

		free(temp);
		free_lists(line);
	}
	return (parse_err_flag);
}

void	clear_vars(t_vars *vars)
{
	t_light		*lights;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;

	lights = vars->scene.lights;
	spheres = vars->scene.spheres;
	cylinders = vars->scene.cylinders;
	planes = vars->scene.planes;
	while (lights)
	{
		vars->scene.lights = lights->next;
		free(lights);
		lights = vars->scene.lights;
	}
	while (spheres)
	{
		vars->scene.spheres = spheres->next;
		free(spheres);
		spheres = vars->scene.spheres;
	}
	while (cylinders)
	{
		vars->scene.cylinders = cylinders->next;
		free(cylinders);
		cylinders = vars->scene.cylinders;
	}
	while (planes)
	{
		vars->scene.planes = planes->next;
		free(planes);
		planes = vars->scene.planes;
	}
}

int	parse_rt(char *argv, t_vars *vars)
{
	char	*file;
	int		fd;

	file = ft_strjoin("scenes/", argv);
	if (!file)
		error_exit("malloc failed", PERROR_ON);
	fd = open(file, O_RDWR);;
	if (fd == -1)
		error_exit("open failed", PERROR_ON);
    if (get_line(fd, vars))
	{
		clear_vars(vars);
		free(file);
		close(fd);
		return (1);
	}
	free(file);
	if (close(fd))
		error_exit("close failed", PERROR_ON);
	return (0);
}
