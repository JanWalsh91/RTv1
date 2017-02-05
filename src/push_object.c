/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 16:41:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new object to the end of list t_objects.
*/

#include "../inc/rtv1.h"

void	push_object(t_object **objects_head, t_object *new_object)
{
	t_object	*obj_ptr;

	printf("push_object: [%s] type: [%i]\n", new_object->name, new_object->type);
	if (new_object)
	{
		if (!*objects_head)
		{
			*objects_head = new_object;
		}
		else
		{
			// C(12)
			obj_ptr = *objects_head;
			// C(13)
			//printf("obj_ptr next: [%i]\n", obj_ptr->next->type);
			while (obj_ptr->next)
				obj_ptr = obj_ptr->next;
			// C(14)
			obj_ptr->next = new_object;
			// C(15)
		}
	}
}