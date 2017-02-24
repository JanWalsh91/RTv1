/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 12:20:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static void parse_scene(t_scene **scenes, char **s, t_list **input, t_attributes **att);
static void parse_object(t_scene *current_scene, char **s, t_list **input, t_attributes **att);
static void parse_attribute(char **s, t_attributes *att, size_t line);

/*
** Parses input (combination of all files read).
** Updates the t_list scenes.
*/

int	parse_input(t_scene **scenes_head, t_list **input)
{
    t_attributes	*att;
	char			**s1;
	
	// printf("PARSE_INPUT\n");
	att = NULL;
	if (!(init_attributes(&att)))
		ft_error_exit("Malloc error");
	while (*input && (*input)->content)
	{
		if (ft_strchr((*input)->content, ':'))
		{
			// printf("found ':': [%s]\n", (*input)->content);
			s1 = split_trim((*input)->content, ':');
			(!ft_strcmp(s1[0], "scene")) ? 
			parse_scene(scenes_head, s1, input, &att) :
			parse_attribute(s1, &(att[0]), (*input)->content_size);
			// print_scenes(*scenes_head);
		}
		*input = (*input)->next;
	}
	return (1);
}

static void parse_scene(t_scene **scenes_head, char **s1, t_list **input, t_attributes **att)
{
	// printf("\nPARSE_SCENE\n");
	char	**s2;
	t_scene	*new_scene;

	new_scene = get_new_scene(s1[1]);
	push_scene(scenes_head, new_scene);
	*input = (*input)->next;
	if (!ft_strchr((*input)->content, '{'))
		error_line_exit("Formatting error: missing '{'", (*input)->content_size);
	while (*input && (*input)->content && !ft_strchr(((*input)->content), '}'))
	{
		if (ft_strchr(((*input)->content), ':'))
		{
			// printf("found ':': [%s]\n", (*input)->content);			
			s2 = split_trim((*input)->content, ':');
			ft_strstr(OBJECTS, s2[0]) ? 
			parse_object(new_scene, s2, input, att) :
			parse_attribute(s2, &((*att)[1]), (*input)->content_size);
		}
		*input = (*input)->next;
	}
	if (!*input || !ft_strchr((*input)->content, '}'))
			error_line_exit("Formatting error: missing '{'", (*input)->content_size);
	set_attributes_scene(*att, new_scene); 
	reset_attributes(&((*att)[1]));
	// printf("\n");
}

/*
** Parses the file for objects.
** If an object is found, adds it to the t_list in scenes
*/

static void parse_object(t_scene *scene, char **s2, t_list **input, t_attributes **att)
{
	printf("\nPARSE_OBJECT\n");

	char		**s3;
	t_object	*new_object;

	new_object = get_new_object(scene->name, s2[1], s2[0]);
	//printf("name of new object: [%s]\n", new_object->name);
	push_object(&scene->objects, new_object);
	*input = (*input)->next;
	// (*input)->content ? printf("next_line: [%s]\n", (*input)->content) : 0;
	if (!ft_strchr((*input)->content, '{'))
			error_line_exit("Formatting error: missing '{'", (*input)->content_size);
    while (*input && !ft_strchr(((*input)->content), '}'))
	{
		// printf("found ':': [%s]\n", (*input)->content);			
		if (ft_strchr(((*input)->content), ':'))
		{
			s3 = split_trim((*input)->content, ':');
			parse_attribute(s3, &((*att)[2]), (*input)->content_size);
		}
		*input = (*input)->next;
		// (*input)->content ? printf("next_line: [%s]\n", (*input)->content) : 0;
	}
	if (!*input || !ft_strchr(((*input)->content), '}'))
		error_line_exit("Formatting error: missing '}'", (*input)->content_size);
	set_attributes_object(*att, new_object);
	reset_attributes(&((*att)[2]));
	// printf("END_PARSE_OBJECT\n");
	// printf("\n");
}

/*
** Parses attributes and updates att.
*/

static void parse_attribute(char **s, t_attributes *att, size_t line)
{
	//printf("parse_attribute: s[0]: [%s] s[1]: [%s] \n", s[0], s[1]);

	printf("PARSE_ATTRIBUTE\n");
	if (ft_strcmp_percent(s[0], "ray_depth", 1))
		parse_ray_depth(&(att->ray_depth), s[1], line);
	else if (ft_strcmp_percent(s[0], "resolution", 0.3) || ft_strcmp_percent(s[0], "size", 1))
		parse_resolution(&(att->res), s[1], line);
	else if (ft_strcmp_percent(s[0], "position", 0.3))
		parse_position(&(att->pos), s[1], line);
	else if (ft_strcmp_percent(s[0], "direction", 0.3))
		parse_direction(&(att->dir), s[1], line);
	else if (ft_strcmp_percent(s[0], "color", 0.5))
		parse_color(&(att->col), s[1], line);
	else if (ft_strcmp_percent(s[0], "radius", 1))
		parse_radius(&(att->rad), s[1], line);
	else if (ft_strcmp_percent(s[0], "angle", 1))
		parse_angle(&(att->angle), s[1], line);
	else if (ft_strcmp_percent(s[0], "height", 1))
		parse_height(&(att->height), s[1], line);
	else if (ft_strcmp_percent(s[0], "look at", 0.5))
		parse_look_at(&(att->look_at), s[1], line);
	else if (ft_strcmp_percent(s[0], "intensity", 0.5))
		parse_intensity(&(att->intensity), s[1], line);
	else
		error_line_exit("Formatting error: invalid attribute name", line);
	printf("\n");
}