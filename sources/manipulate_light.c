/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:52:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/26 15:52:49 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook_translate_light(int keycode, t_vars *vars)
{
	t_point3	*light_pos;
	float		distance;

	light_pos = &vars->select.curr_light->pos;
	distance = 0.2;
	if (W_KEY == keycode)
		translate_point(light_pos, (t_vec3){0, 0, 1}, distance);
	else if (S_KEY == keycode)
		translate_point(light_pos, (t_vec3){0, 0, -1}, distance);
	else if (A_KEY == keycode)
		translate_point(light_pos, (t_vec3){-1, 0, 0}, distance);
	else if (D_KEY == keycode)
		translate_point(light_pos, (t_vec3){1, 0, 0}, distance);
	else if (E_KEY == keycode)
		translate_point(light_pos, (t_vec3){0, 1, 0}, distance);
	else if (Q_KEY == keycode)
		translate_point(light_pos, (t_vec3){0, -1, 0}, distance);
}
