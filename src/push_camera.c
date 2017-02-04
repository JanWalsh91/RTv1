/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 17:08:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new camera to the list t_cameras.
*/

#include "../inc/rtv1.h"

void	push_camera(t_camera **cameras_head, t_camera *new_camera)
{
	t_camera	*cam_ptr;

	if (new_camera)
	{
		if (!*cameras_head)
			*cameras_head = new_camera;
		else
		{
			cam_ptr = *cameras_head;
			while (cam_ptr->next)
				cam_ptr = cam_ptr->next;
			cam_ptr->next = new_camera;
		}
	}
}