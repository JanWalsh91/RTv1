/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:44:59 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:45:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Adds a new camera to the end of list t_cameras.
*/

void	push_camera(t_camera **cameras_head, t_camera *new_camera)
{
	t_camera	*cam_ptr;

	printf("push_camera: [%s]\n", new_camera->name);
	if (new_camera)
	{
		if (!(*cameras_head))
			*cameras_head = new_camera;
		else
		{
			cam_ptr = *cameras_head;
			while (cam_ptr->next)
				cam_ptr = cam_ptr->next;
			cam_ptr->next = new_camera;
		}
		new_camera->next = NULL;
	}
}