/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:17:35 by damin             #+#    #+#             */
/*   Updated: 2024/09/04 16:53:21 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_lists(char **lists)
{
    char **temp = lists;

    if (lists == NULL)
        return;
    while (*temp)
        free(*temp++);
    free(lists);
}


int	parse_identifier(char **line, t_vars *vars, int *parse_err_flag)
{	
	if (ft_strncmp(line[0], "A", 2) == 0)
		*parse_err_flag = parse_amb_light(vars->obj.amb_light);
	else if (ft_strncmp(line[0], "C", 2) == 0)
		*parse_err_flag = parse_camera(vars->obj.camera);
	else if (ft_strncmp(line[0], "L", 2) == 0)
		*parse_err_flag = parse_light(vars->obj.light);
	else if (ft_strncmp(line[0], "pl", 3) == 0)
		*parse_err_flag = parse_plane(vars);
	else if (ft_strncmp(line[0], "sp", 3) == 0)
		*parse_err_flag = parse_spheres(vars);
	else if (ft_strncmp(line[0], "cy", 3) == 0)
		*parse_err_flag = parse_cylinders(vars);
	else
	{
		ft_putstr_fd("No such identifier",STDERR_FILENO);
		ft_putendl_fd(line[0], 2);
		*parse_err_flag = 1;
	}
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
		line = ft_split(get_next_line(fd), " ");
		if (!line)
			break ;
		parse_identifier(line, vars, &parse_err_flag);
		free_lists(line);
	}
	free(file);
	if (close(fd))
		err_exit("close failed", PERROR_ON);
	return (0);
}
