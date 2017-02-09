/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:13:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/06 15:38:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"
#include <stdio.h>



void	print_scenes(t_scene *scenes_head)
{
	t_scene		*s_ptr;
	t_object	*o_ptr;
	t_object	*l_ptr;
	t_object	*c_ptr;

	printf("print_scenes\n");
	s_ptr = scenes_head;
	while (s_ptr)
	{
		printf("scene: %s\n", s_ptr->name);
		printf("	res: [%i, %i]\n", s_ptr->res.x, s_ptr->res.x);
		printf("	ray_depth: [%i]\n", s_ptr->ray_depth);
		o_ptr = s_ptr->objects;
		printf("	objects:\n");
		while (o_ptr)
		{
			printf("		object type: [%i]\n", o_ptr->type);
			printf("		object name: [%s]\n", o_ptr->name);
			printf("		object pos: [%f] [%f] [%f]\n", o_ptr->pos.x, o_ptr->pos.y, o_ptr->pos.z);
			printf("		object col: [%i] [%i] [%i]\n", o_ptr->col.r, o_ptr->col.g, o_ptr->col.b);
			if (o_ptr->type == SPHERE)
				printf("		object rad: [%f]\n", o_ptr->rad);
			o_ptr = o_ptr->next;
		}
		c_ptr = s_ptr->cameras;
		printf("	cameras:\n");
		while (c_ptr)
		{
			printf("		object type: [%i]\n", c_ptr->type);
			printf("		camera name: [%s]\n", c_ptr->name);
			printf("		camera pos: [%f] [%f] [%f]\n", c_ptr->pos.x, c_ptr->pos.y, c_ptr->pos.z);
			printf("		camera scale: [%f]\n", c_ptr->scale);
			c_ptr = c_ptr->next;
		}
		printf("	lights:\n");
		l_ptr = s_ptr->lights;
		while (l_ptr)
		{
			printf("		object type: [%i]\n", l_ptr->type);
			printf("		light name: [%s]\n", l_ptr->name);
			printf("		light pos: [%f] [%f] [%f]\n", l_ptr->pos.x, l_ptr->pos.y, l_ptr->pos.z);
			l_ptr = l_ptr->next;
		}
		s_ptr = s_ptr->next;
	}
}

void	print_input(t_list **list_head)
{
	t_list *l_ptr;
	int		i;

	printf("print_input\n");
	l_ptr = *list_head;
	i = 0;
	while (l_ptr)
	{
		printf("line: [%i]: [%s]\n", i, (char *)(l_ptr)->content);
		l_ptr = l_ptr->next;
		++i;
	}
	printf("end print_input\n");
}

void	print_attributes(t_attributes att)
{
	printf("print_attributes\n");
	printf("res:		[%i][%i]\n", att.res.x, att.res.y);
	printf("ray_depth:	[%i]\n", att.ray_depth);
	printf("pos:		[%f][%f][%f]\n", att.pos.x, att.pos.y, att.pos.z);
}

void	print_vec(t_vec3 vec)
{
	printf("print_vec: [%f][%f][%f]\n", vec.x, vec.y, vec.z);
}