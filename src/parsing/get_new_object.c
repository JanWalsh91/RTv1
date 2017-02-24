/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 14:24:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Creates a new object.
*/

static int	get_type(char *type);

t_object	*get_new_object(char *scene_name, char *name, char *type)
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
	if (!name)
	{
		// printf("no name given\n");
		if (!current_scene_name) //if first scene ...
		{
			// printf("update current_scene_name\n");
			current_scene_name = scene_name;
		}
		else if (ft_strcmp(current_scene_name, scene_name)) //if on new scene
			i = 1;
		new_object->name = ft_strdup(ft_strjoin("Object ", ft_itoa(i)));
		++i;
	}
	else
		new_object->name = ft_strdup(name);
	new_object->type = get_type(type);
	//printf("end get_new_object\n");
	// printf("current_scene_name: [%s]", current_scene_name);
	// printf("	scene_name: [%s]\n", scene_name);
	// printf("end get_new_object: object name: [%s]\n", new_object->name);
	// printf("\n");
	return (new_object);
}

static int	get_type(char *type)
{
	char	**list;
	int		i;

	printf("GET_TYPE\n");
	i = 0;	
	list = ft_strsplit(OBJECTS, ',');
	while (i < OBJECT_COUNT && ft_strcmp(list[i], type))
		++i;
	if (i < OBJECT_COUNT)
	{
		//free list.
		return (i + 1);
	}
	//free list.
	ft_error_exit("Formatting error in .rt file: invalid object type");
	return (0); //ERROR: INVALID OBJECT TYPE
}