/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 16:20:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Creates a new object and sets default values.
*/

static int	get_type(char *type);

t_object	*get_new_object(char *name, char *type)
{
	t_object *new_object;

	if (!(new_object = (t_object *)ft_memalloc(sizeof(t_object))))
		return (0);
	new_object->next = NULL;
	if (name)
		new_object->name = ft_strdup(name);
	new_object->type = get_type(type);
	//set default values for object.
	return (new_object);
}

static int	get_type(char *type)
{
	if 
	return (0);
}