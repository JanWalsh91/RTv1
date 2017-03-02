/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/01 16:07:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Adds a new object to the end of list t_objects.
*/

void	push_object(t_object **objects_head, t_object *new_object)
{
	t_object	*obj_ptr;

	// printf("push_object: [%s]\n", new_object->name);
	if (new_object)
	{
		if (!(*objects_head))
			*objects_head = new_object;
		else
		{
			obj_ptr = *objects_head;
			while (obj_ptr->next)
				obj_ptr = obj_ptr->next;
			obj_ptr->next = new_object;
		}
		new_object->next = NULL;
	}
}