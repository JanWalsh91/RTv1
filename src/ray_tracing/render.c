/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:14:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Updates a camera's pixel_map (color of image pixels).
*/

void	render(t_raytracing_tools *r)
{
	t_ray	cam_ray;

    r->pix.y = -1;
    while (++r->pix.y < r->scenes->res.y)
	{
		r->pix.x = -1;
		while (++r->pix.x < r->scenes->res.x)
		{
			cam_ray = init_camera_ray(r->pix, r->scenes);
			r->scenes->cameras->pixel_map[r->pix.y][r->pix.x] = cast_primary_ray(r, &cam_ray);
		}
	}
}