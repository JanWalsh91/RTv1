/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 17:24:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int	main(int ac, char **av)
{
	t_list	*scenes;
	int		i;

	ac < 2 ? ft_display_usage_exit();
	i = 0;
	while (++i < ac)
		if (!parse_file(&scenes, av[i]))
			return (0);
	//send info to raytracer(scenes)
	return (0);
}
