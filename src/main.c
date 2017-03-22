/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 15:46:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Checks arg count, parses and prepares data, and sends data to rtv1.
*/

int	main(int ac, char **av)
{
	t_parse_tools		t;
	t_raytracing_tools	r;
	int					i;

	ac < 2 ? ft_display_usage_exit(USAGE) : 0;
	i = 0;
	init_parse_tools(&t);
	while (++i < ac)
	{
		if (ft_strstr(av[i], ".rt") && *(ft_strstr(av[i], ".rt") + 3) == '\0')
			get_file(av[i], &t);
		else
			rt_file_warning(NULL, "Skipped invalid file.");
	}
	i = 0;
	while (++i < ac)
		parse_input(&t);
	check_scenes(t.scenes);
	r.scenes = t.scenes;
	free_parse_tools(&t);
	rtv1(&r);
	free_scenes(r.scenes);
	return (0);
}
