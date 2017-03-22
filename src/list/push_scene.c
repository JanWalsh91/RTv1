/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:44:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds new_scene to the end of list t_scene.
*/

#include "../../inc/rtv1.h"

void	push_scene(t_scene **scenes_head, t_scene *new_scene)
{
	t_scene	*scene_ptr;

	if (new_scene)
	{
		if (!*scenes_head)
			*scenes_head = new_scene;
		else
		{
			scene_ptr = *scenes_head;
			while (scene_ptr->next)
				scene_ptr = scene_ptr->next;
			scene_ptr->next = new_scene;
			new_scene->prev = scene_ptr;
		}
	}
}
