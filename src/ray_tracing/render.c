/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 12:39:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Updates the image
*/

void	render(t_raytracing_tools *r)
{
	t_ray	cam_ray;

	printf("RENDER\n");
    r->pix.y = -1;
    while (++r->pix.y < r->scenes->res.y)
	{
		r->pix.x = -1;
		while (++r->pix.x < r->scenes->res.x)
		{
			// printf("pix: [%i][%i]\n", r->pix.y, r->pix.x);
			cam_ray = init_camera_ray(r->pix, r->scenes);
			// cam_ray.cast(r, &cam_ray);
			r->scenes->cameras->pixel_map[r->pix.y][r->pix.x] = cast_primary_ray(r, &cam_ray);
		}
	}
}