/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 14:15:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new object to the list t_objects.
*/

#include "../inc/rtv1.h"

void	add_object(t_object **objects, t_object *new_object)
{
	if (new_object)
	{
		if (!*objects)
			*objects = new_object;
		else
		{
			while ((*objects)->next)
				*objects = (*objects)->next;
			(*objects)->next = new_object;
		}
	}
}