/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cameras_lights.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:55:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 16:42:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Extracts cameras and lights from the list of objects and puts them in their
** own list.
*/

int	extract_cameras_lights(t_scene *scene)
{
	printf("EXTRACT_CAMERAS_LIGHTS\n");
	t_object	*to_move;
	t_object	*o_ptr;
		
	o_ptr = scene->objects;
	printf("current obj name: [%s]\n", o_ptr->name);
	while (o_ptr->type == CAMERA || o_ptr->type == LIGHT)
	{
		to_move = o_ptr;
		scene->objects = to_move->next;
		to_move->next = NULL;
		to_move->type == CAMERA ? push_object(&scene->cameras, to_move) : 0;
		to_move->type == LIGHT ? push_object(&scene->lights, to_move) : 0;
		o_ptr = scene->objects;
	}
	printf("current obj name: [%s]\n", o_ptr->next->name);
	while (o_ptr->next)
	{
		printf("current obj name: [%s]\n", o_ptr->next->name);
		if (o_ptr->next->type == CAMERA || o_ptr->next->type == LIGHT)
		{
			to_move = o_ptr->next;
			o_ptr->next = to_move->next;
			to_move->next = NULL;
			to_move->type == CAMERA ? push_object(&scene->cameras, to_move) : 0;
			to_move->type == LIGHT ? push_object(&scene->lights, to_move) : 0;
		}
		else
			o_ptr = o_ptr->next;
	}
	printf("END_EXTRACT_CAMERAS_LIGHTS\n");
	return (1);
}