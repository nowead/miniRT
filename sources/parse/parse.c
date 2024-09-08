/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:24:39 by damin             #+#    #+#             */
/*   Updated: 2024/09/08 16:32:42 by damin            ###   ########.fr       */
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

int	parse_rt(char *argv, t_vars *vars)
{
	char	*file;
	int		fd;
	char 	**line;
	int		parse_err_flag;

	parse_err_flag = 0;
	file = ft_strjoin("scenes/", argv);
	if (!file)
		error_exit("malloc failed", PERROR_ON);
	fd = open(file, O_RDWR);;
	if (fd == -1)
		error_exit("open failed", PERROR_ON);
	while (!parse_err_flag)
	{
		line = ft_split(get_next_line(fd), ' ');
		if (!line)
			break ;
		parse_line(line, vars, &parse_err_flag);
		free_lists(line);
	}
	free(file);
	if (close(fd))
		error_exit("close failed", PERROR_ON);
	return (0);
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

void	parse(int argc, char **argv, t_vars *vars)
{
	if (parse_argv(argc, argv))
		error_exit("Usage: ./minirt [file.rt]", PERROR_OFF);
	if (parse_rt(argv[1], vars))
		error_exit("Error", PERROR_OFF);
}