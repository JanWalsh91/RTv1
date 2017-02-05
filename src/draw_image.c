/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 16:45:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Updates the image
*/

int draw_image(t_scene *scene)
{
    t_pt2   i;

	(void)scene;
    i.x = 0;
    i.y = 0;
    while (++i.y < scene->res.y)
	{
		i.x = -1;
		while (++i.x < scene->res.x)
		{
			init_camera_ray(i, scene);
			trace_camera_ray(i, scene);
		}
	}
    return(1);
}