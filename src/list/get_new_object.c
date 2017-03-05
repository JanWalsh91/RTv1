/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 15:19:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new object.
*/

static void	set_non_values(t_object *new_object);
static void set_function_pointers(t_object *new_object);

t_object 	*get_new_object(t_parse_tools *t)
{
	// printf("GET_NEW_OBJECT\n");
	t_object 	*new_object;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	if (!(new_object = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_error_exit("Malloc error");
	set_non_values(new_object);
	if (!t->input->value)
	{
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name)) //if on new scene
			i = 1;
		new_object->name = ft_strdup(ft_strsjoin(3, TOKENS[t->input->token], " ", ft_itoa(i)));
		++i;
	}
	else
		new_object->name = ft_strdup(t->input->value);
	new_object->type = t->input->token;
	set_function_pointers(new_object);
	return (new_object);
}

static void	set_non_values(t_object *new_object)
{
	ft_bzero(new_object, sizeof(t_object));
	new_object->next = NULL;
	new_object->pos = v_new(NAN, NAN, NAN);
	new_object->dir = v_new(NAN, NAN, NAN);
	new_object->rot = v_new(NAN, NAN, NAN);
	new_object->look_at = v_new(NAN, NAN, NAN);
	new_object->col = v_new(NAN, NAN, NAN);
	new_object->rad = -1;
	new_object->height = -1;
	new_object->refraction = -1;
	new_object->reflection = -1;
	new_object->specular = -1;
	new_object->transparency = -1;
}

static void set_function_pointers(t_object *new_object)
{
	//
}