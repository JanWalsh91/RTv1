/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/06 17:16:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Updates the image
*/

int draw_image(t_scene *scene)
{
    t_pt2   i;
	t_ray	cam_ray;

	printf("DRAW_IMAGE\n");
    i.y = -1;
    while (++i.y < scene->res.y)
	{
		i.x = -1;
		while (++i.x < scene->res.x)
		{
			//printf("pix: [%i][%i]\n", i.y, i.x);
			cam_ray = init_camera_ray(i, scene);
			scene->cameras->pixel_map[i.y][i.x] = cast_camera_ray(&cam_ray, scene);
		}
	}
    return(1);
}