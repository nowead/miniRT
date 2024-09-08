/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_point_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mindaewon <mindaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:51:31 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/07 15:48:02 by mindaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int init_point_light(t_light *lights, char **line)
{
    lights = (t_light *)malloc(sizeof(t_light));
    if (!lights)
        return (1);
    if (set_point_light(line, lights))
        return (1);
    lights->next = NULL;
    return (0);
}

int set_point_light(char **line, t_light *lights)
{
    if (ft_strslen(line) != 6)
        return (1);
    if (check_coord(&line[1]))
        return (1);
    lights->pos = (t_point3d){ft_atof(line[1]), ft_atof(line[2]), ft_atof(line[3])};
    if (check_float_string(line[4]))
        return (1);
    lights->intens = ft_atof(line[4]);
    if (check_color(&line[5]))
        return (1);
    lights->color = get_color(ft_atoi(line[5]), ft_atoi(line[6]), ft_atoi(line[7]));
    lights->type = POINT_LIGHT;
    return (0);
}

int parse_point_light(char **line, t_vars *vars)
{
    t_light *curr;
    t_light *lights;

    vars->scene.num_of_lights++;
    lights = vars->scene.lights;
    if (lights == NULL)
    {
        if (init_point_light(lights, line))
            return (1);
    }
    else
    {
        curr = lights;
        while (curr->next)
            curr = curr->next;
        curr->next = (t_light *)malloc(sizeof(t_light));
        if (!curr->next)
            return (1);
        if (set_point_light(line, curr->next))
            return (1);
        curr->next->next = NULL;
    }
    return (0);
}