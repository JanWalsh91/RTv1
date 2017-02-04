/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:39:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 16:21:17 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** There is a way of simplifying calculations by calculate one vector before hand
** and using it for each pixel (multiplied by more sstuff).
*/

int rtv1(t_scene *scene)
{
	t_pt2	i;

	i.y = -1;
	(void)scene;
    //initialize image.
	//initiliaze pixel_map (when moving cameras to their own list)
    while (++i.y < scene->res.y)
	{
		i.x = -1;
		while (++i.x < scene->res.x)
		{
			init_camera_ray(i, );
			trace_camera_ray();
		}
	}
	
    //draw_image(t_list *scene);
    //initialize window
    //put image to window
    //sdl functions
    return(1);
}