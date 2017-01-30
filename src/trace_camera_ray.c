/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_camera_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:57:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 11:05:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Updates the color of a pixel.
*/

int	trace_camera_ray(t_pt2 p, t_scene *scene)
{
	t_object **current_object;

	current_object = &(scene->objects);
	while (current_object->next)
		//check intersection
		//store color
	return (1);
}
