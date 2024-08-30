/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:30:10 by damin             #+#    #+#             */
/*   Updated: 2024/08/30 21:10:38 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// main function!
int main(int argc, char **argv)
{
	if (argc!=2)
		return (1);
	if (parse_argv(argv))
		return (1);
	print_image();
	return (0);
}