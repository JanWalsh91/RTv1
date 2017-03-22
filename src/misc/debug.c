/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:13:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 15:28:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"
#include <stdio.h>

void	print_scenes(t_scene *scenes_head)
{
	t_scene		*s_ptr;
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_camera	*c_ptr;

	ft_printf("%{u}%{red}print_scenes%{}\n");
	s_ptr = scenes_head;
	while (s_ptr)
	{
		printf("scene: %s\n", s_ptr->name);
		printf("	res: [%i, %i]\n", s_ptr->res.x, s_ptr->res.y);
		printf("	ray_depth: [%i]\n", s_ptr->ray_depth);
		printf("	ambient coef: [%f]\n", s_ptr->ka);
		printf("	ambient col: [%f] [%f] [%f]\n", s_ptr->ambient_light_color.x, s_ptr->ambient_light_color.y, s_ptr->ambient_light_color.z);
		printf("	image aspect ratio: [%f]\n", s_ptr->image_aspect_ratio);
		o_ptr = s_ptr->objects;
		printf("	objects:\n");
		while (o_ptr)
		{
			printf("	object name: [%s]\n", o_ptr->name);
			printf("		object type: [%i]\n", o_ptr->type);
			printf("		object pos: [%f] [%f] [%f]\n", o_ptr->pos.x, o_ptr->pos.y, o_ptr->pos.z);
			printf("		object col: [%f] [%f] [%f]\n", o_ptr->col.x, o_ptr->col.y, o_ptr->col.z);
			printf("		object lookat: [%f] [%f] [%f]\n", o_ptr->look_at.x, o_ptr->look_at.y, o_ptr->look_at.z);
			printf("		object dir: [%f] [%f] [%f]\n", o_ptr->dir.x, o_ptr->dir.y, o_ptr->dir.z);
			printf("		object rad: [%f]\n", o_ptr->rad);
			printf("		object height: [%f]\n", o_ptr->height);
			printf("		object kd: [%f]\n", o_ptr->kd);
			printf("		object ks: [%f]\n", o_ptr->ks);
			printf("		object specular exponent: [%f]\n", o_ptr->specular_exp);
			o_ptr = o_ptr->next;
		}
		c_ptr = s_ptr->cameras;
		printf("	cameras:\n");
		while (c_ptr)
		{
			printf("	camera name: [%s]\n", c_ptr->name);
			printf("		camera pos: [%f] [%f] [%f]\n", c_ptr->pos.x, c_ptr->pos.y, c_ptr->pos.z);
			printf("		camera dir: [%f] [%f] [%f]\n", c_ptr->dir.x, c_ptr->dir.y, c_ptr->dir.z);
			printf("		camera rot: [%f] [%f] [%f]\n", c_ptr->rot.x, c_ptr->rot.y, c_ptr->rot.z);
			printf("		camera look at: [%f] [%f] [%f]\n", c_ptr->look_at.x, c_ptr->look_at.y, c_ptr->look_at.z);
			printf("		camera scale: [%f]\n", c_ptr->scale);
			printf("		camera fov: [%f]\n", c_ptr->fov);
			c_ptr = c_ptr->next;
		}
		printf("	lights:\n");
		l_ptr = s_ptr->lights;
		while (l_ptr)
		{
			printf("	light name: [%s]\n", l_ptr->name);
			printf("		light pos: [%f] [%f] [%f]\n", l_ptr->pos.x, l_ptr->pos.y, l_ptr->pos.z);
			printf("		light dir: [%f] [%f] [%f]\n", l_ptr->dir.x, l_ptr->dir.y, l_ptr->dir.z);			
			printf("		light col: [%f] [%f] [%f]\n", l_ptr->col.x, l_ptr->col.y, l_ptr->col.z);
			printf("		light intensity: [%f]\n", l_ptr->intensity);
			l_ptr = l_ptr->next;
		}
		s_ptr = s_ptr->next;
	}
	printf("\n");
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

void	print_matrix(t_matrix m)
{
	int i;
	int	y;

	y = -1;
	while (++y < 4)
	{
		i = -1;
		while (++i < 4)
			printf("[%f]", m[y][i]);
		printf("\n");
	}
}
