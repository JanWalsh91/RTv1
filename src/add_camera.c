/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 12:13:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new camera to the list t_cameras.
*/

#include "../inc/rtv1.h"

void	add_camera(t_camera **cameras, t_camera *new_camera)
{
	if (new_camera)
	{
		if (!*cameras)
			*cameras = new_camera;
		else
		{
			while ((*cameras)->next)
				*cameras = (*cameras)->next;
			(*cameras)->next = new_camera;
		}
	}
}