/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 15:30:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Checks arg count, parses and prepares data, and send data to rtv1.
*/

int	main(int ac, char **av)
{
	t_list	*input;
	t_scene	*scenes;
	int		i;

	printf("main\n");
	input = NULL;
	scenes = NULL;
	ac < 2 ? ft_display_usage_exit("usage") : 0;
	i = 0;
	while (++i < ac)
		if (!get_file(av[i], &input) || !parse_input(&scenes, &input))
			return (0);
	//free input.
	print_scenes(scenes);
	rtv1(&scenes);
	return (0);
}