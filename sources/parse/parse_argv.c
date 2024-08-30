/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:55:30 by damin             #+#    #+#             */
/*   Updated: 2024/08/30 21:15:02 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_argv(char **argv)
{
	if (!argv[1])
		return (1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 3], ".rt", 4) == 0)
		return (0);
	return (1);
}
