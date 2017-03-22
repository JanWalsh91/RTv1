/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:24:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initializes a camera ray.
*/

t_ray	init_camera_ray(t_pt2 i, t_scene *scene)
{
	t_ray		cam_ray;
	t_camera	*cam;
	t_vec3		pix;

	cam = scene->cameras;
	pix.x = (2 * (i.x + 0.5) / (double)scene->res.x - 1) *
			scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (i.y + 0.5) / (double)scene->res.y) * cam->scale;
	pix.z = CAM_IMG_PANE_DIST;
	cam_ray.dir = v_norm(pix);
	cam_ray.origin = cam->pos;
	cam_ray.dir = m_v_mult(cam_ray.dir, cam->ctw);
	cam_ray.dir = v_norm(cam_ray.dir);
	cam_ray.type = R_PRIMARY;
	cam_ray.n_dir = 1;
	return (cam_ray);
}
