/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/25 14:42:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Checks arg count, parses and prepares data, and send data to rtv1.
*/

int	main(int ac, char **av)
{
	t_parse_tools	t;
	// t_input	*input;
	t_scene	*scenes;
	int		i;

	// input = NULL;
	// scenes = NULL;
	ac < 2 ? ft_display_usage_exit("usage") : 0;
	i = 0;
	while (++i < ac)
		get_file(av[i], &t.input);
	i = 0;
	while (++i < ac)
	{
		parse_input(&scenes, &t.input);
		//check_data;
	}
	//free input.
	print_scenes(scenes);
	rtv1(&scenes);
	return (0);
}