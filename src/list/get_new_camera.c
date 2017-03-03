/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:42:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/03 15:53:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new object.
*/

t_camera 	*get_new_camera(t_parse_tools *t)
{
	// printf("GET_new_camera: [%s]\n", name);
	t_camera 	*new_camera;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	//printf("current_scene_name: [%s]", current_scene_name);
	//printf("	scene_name: [%s]", scene_name);
	//printf("	object_name: [%s]\n", name);
	if (!(new_camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		ft_error_exit("Malloc error");
	new_camera->next = NULL;
	ft_bzero(new_camera, sizeof(t_camera));
	new_camera->pos = v_new(NAN, NAN, NAN);
	new_camera->dir = v_new(NAN, NAN, NAN);
	new_camera->rot = v_new(NAN, NAN, NAN);
	new_camera->look_at = v_new(NAN, NAN, NAN);
	new_camera->fov = NAN;
	if (!t->input->value)
	{
		// printf("no name given\n");
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name)) //if on new scene
			i = 1;
		new_camera->name = ft_strdup(ft_strsjoin(3, TOKENS[t->input->token], " ", ft_itoa(i)));
		++i;
	}
	else
		new_camera->name = ft_strdup(t->input->value);
	//printf("end get_new_camera\n");
	// printf("current_scene_name: [%s]", current_scene_name);
	// printf("	scene_name: [%s]\n", scene_name);
	// printf("end get_new_camera: object name: [%s]\n", new_camera->name);
	// printf("\n");
	return (new_camera);
}