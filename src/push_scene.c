/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/03 12:56:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new scene to the end of list t_scene.
** If the list of scenes is empty, makes scene_head point to the first scene.
** Else, iterates to the end of the list and adds new scene there.
*/

#include "../inc/rtv1.h"

void	push_scene(t_scene **scenes_head, t_scene *new_scene)
{
	t_scene	*scene_ptr;

	printf("PUSH_SCENE\n");
	if (new_scene)
	{
		if (!*scenes_head)
		{
			*scenes_head = new_scene;
		}
		else
		{
			scene_ptr = *scenes_head;
			while (scene_ptr->next)
				scene_ptr = scene_ptr->next;
			scene_ptr->next = new_scene;
		}
	}
	printf("\n");
}