/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:40:04 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:40:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new object.
*/

t_light 	*get_new_light(t_parse_tools *t)
{
	// printf("GET_new_light: [%s]\n", name);
	t_light 	*new_light;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	//printf("current_scene_name: [%s]", current_scene_name);
	//printf("	scene_name: [%s]", scene_name);
	//printf("	object_name: [%s]\n", name);
	if (!(new_light = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_error_exit("Malloc error");
	new_light->next = NULL;
	ft_bzero(new_light, sizeof(t_light));
	if (!t->input->value)
	{
		// printf("no name given\n");
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name)) //if on new scene
			i = 1;
		new_light->name = ft_strdup(ft_strsjoin(3, TOKENS[t->input->token], " ", ft_itoa(i)));
		++i;
	}
	else
		new_light->name = ft_strdup(t->input->value);
	//printf("end get_new_light\n");
	// printf("current_scene_name: [%s]", current_scene_name);
	// printf("	scene_name: [%s]\n", scene_name);
	// printf("end get_new_light: object name: [%s]\n", new_light->name);
	// printf("\n");
	return (new_light);
}