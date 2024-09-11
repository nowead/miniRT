/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_amb_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:45 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/10 21:36:47 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int init_amb_light(t_light *lights, char **line, t_vars *vars)
{
    lights = (t_light *)ft_calloc(1, sizeof(t_light));
    if (!lights)
        return (1);
    if (set_amb_light(line, lights))
        return (1);
    lights->next = NULL;
    vars->scene.lights = lights;
    return (0);
}

int set_amb_light(char **line, t_light *lights)
{
    char    **color;

    if (ft_strslen(line) != 3)
        return (1);
    if (check_float_string(line[1]))
        return (1);
    lights->intens = ft_atof(line[1]);
    if (lights->intens < 0 || lights->intens > 1)
        return (1);
    color = ft_split(line[2], ',');
    if (check_color(color))
        return (1);
    lights->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_lists(color);
    lights->type = AMBIENT_LIGHT;
    return (0);
}

int parse_amb_light(char **line, t_vars *vars)
{
    t_light *curr;
    t_light *lights;

    vars->scene.num_of_lights++;
    lights = vars->scene.lights;
    if (lights == NULL)
    {
        if (init_amb_light(lights, line, vars))
            return (1);
    }
    else
    {
        curr = lights;
        while (curr->next)
            curr = curr->next;
        curr->next = (t_light *)ft_calloc(1, sizeof(t_light));
        if (!curr->next)
            return (1);
        if (set_amb_light(line, curr->next))
            return (1);
        curr->next->next = NULL;
        vars->scene.lights = lights;
    }
    return (0);
}
