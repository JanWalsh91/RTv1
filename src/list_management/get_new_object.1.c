/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:38:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new object.
*/

t_object 	*get_new_object(t_parse_tools *t)
{
	// printf("GET_NEW_OBJECT: [%s]\n", name);
	t_object 	*new_object;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	//printf("current_scene_name: [%s]", current_scene_name);
	//printf("	scene_name: [%s]", scene_name);
	//printf("	object_name: [%s]\n", name);
	if (!(new_object = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_error_exit("Malloc error");
	new_object->next = NULL;
	ft_bzero(new_object, sizeof(t_object));
	if (!t->input->value)
	{
		// printf("no name given\n");
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name)) //if on new scene
			i = 1;
		new_object->name = ft_strdup(ft_strsjoin(3, TOKENS[t->input->token], " ", ft_itoa(i)));
		++i;
	}
	else
		new_object->name = ft_strdup(t->input->value);
	//printf("end get_new_object\n");
	// printf("current_scene_name: [%s]", current_scene_name);
	// printf("	scene_name: [%s]\n", scene_name);
	// printf("end get_new_object: object name: [%s]\n", new_object->name);
	// printf("\n");
	return (new_object);
}