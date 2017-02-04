/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 17:06:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int parse_scene(t_scene **scenes, char **s, t_list **input, t_attributes **att);
static int parse_object(t_scene *current_scene, char **s, t_list **input, t_attributes **att);
static int parse_attribute(char **s, t_attributes *att);

/*
** Parses input (combination of all files read).
** Updates the t_list scenes.
*/

int parse_input(t_scene **scenes_head, t_list **input)
{
    t_attributes	*att;
	char			**s1;
	
	printf("PARSE_INPUT\n");
	//print_input(input);
	att = NULL;
	if (!(init_attributes(&att)))
		return (0);
	while (*input && (*input)->content)
	{
		if (ft_strchr((*input)->content, ':'))
		{
			printf("found ':': [%s]\n", (*input)->content);
			s1 = split_trim((*input)->content, ':');
			if (!ft_strcmp(s1[0], "scene") && !parse_scene(scenes_head, s1, input, &att))
				return (0);
			else if (ft_strcmp(s1[0], "scene") && !parse_attribute(s1, &(att[0])))
				return (0);
			//print_attributes((att[0]));
		}
		*input = (*input)->next; //if no ':' is found, ignore the line.
	}
	printf("\n");
	return (1);
}

static int parse_scene(t_scene **scenes_head, char **s1, t_list **input, t_attributes **att)
{
	printf("\nPARSE_SCENE\n");
	char	**s2;
	t_scene	*new_scene;

	new_scene = get_new_scene(s1[1]);
	push_scene(scenes_head, new_scene);
	*input = (*input)->next;
	printf("next_line: [%s]\n", (*input)->content);
	if (!ft_strchr((*input)->content, '{'))
        return (0); //ERROR INVALID FORMAT MISSING BRACKET
	while (*input && !ft_strchr(((*input)->content), '}'))
	{
		if (ft_strchr(((*input)->content), ':'))
		{
			printf("found ':': [%s]\n", (*input)->content);			
			s2 = split_trim((*input)->content, ':');
			//*input = (*input)->next;
			//printf("next_line: [%s]\n", (*input)->content);
			if (ft_strstr(OBJECTS, s2[0]) && !parse_object(new_scene, s2, input, att))
				return (0);
			else if (!parse_attribute(s2, &((*att)[1])))
				return (0);
		}
		*input = (*input)->next; //if no ':' is found, ignore the line.
		printf("next_line: [%s]\n", (*input)->content);
	}
	if (!ft_strchr(((*input)->content), '}'))
		return (0); //ERROR NO CLOSING BRACKET
	set_attributes_scene(*att, new_scene); 
	reset_attributes(&((*att)[1]));
	printf("\n");
    return (1);
}

/*
** Parses the file for objects.
** If an object is found, adds it to the t_list in scenes
*/

static int parse_object(t_scene *scene, char **s2, t_list **input, t_attributes **att)
{
	printf("\nPARSE_OBJECT\n");

	char		**s3;
	t_object	*new_object;

	//printf("Anew_scene name: [%s]\n", scene->name);
	//printf("%p\n", scene);
	// printf("att->name: [%s]\n", (((*att)[2]).name));

	new_object = get_new_object(scene->name, s2[1], s2[0]);
	push_object(&scene->objects, new_object);
	*input = (*input)->next;
	printf("next_line: [%s]\n", (*input)->content);
	if (!ft_strchr((*input)->content, '{'))
	{
		printf("ERROR did not find {\n");
        return (0); //INVALID FORMAT
	}
    while (*input && !ft_strchr(((*input)->content), '}'))
	{
		printf("found ':': [%s]\n", (*input)->content);			
		if (ft_strchr(((*input)->content), ':'))
		{
			s3 = split_trim((*input)->content, ':');
			if (!parse_attribute(s3, &((*att)[2])))
			{
				printf("parse_attribute error\n");
				return (0);
			}
		}
		*input = (*input)->next;
		printf("next_line: [%s]\n", (*input)->content);
	}
	if (!ft_strchr(((*input)->content), '}'))
	{
		printf("error: no closing bracket\n");
		return (0); //ERROR NO CLOSING BRACKET
	}
	set_attributes_object(*att, new_object);
	reset_attributes(&((*att)[2]));
	printf("END_PARSE_OBJECT\n");
	printf("\n");
    return (1);
}

/*
** Parses attributes and updates att.
*/

static int parse_attribute(char **s, t_attributes *att)
{
	//printf("parse_attribute: s[0]: [%s] s[1]: [%s] \n", s[0], s[1]);

	printf("PARSE_ATTRIBUTE\n");
	if (ft_strcmp_percent(s[0], "ray_depth", 0.3))
		return (parse_ray_depth(&(att->ray_depth), s[1]));
	if (ft_strcmp_percent(s[0], "resolution", 0.3) || ft_strcmp_percent(s[0], "size", 1))
		return (parse_resolution(&(att->res), s[1]));
	else if (ft_strcmp_percent(s[0], "position", 0.3))
		return (parse_position(&(att->pos), s[1]));
	else if (ft_strcmp_percent(s[0], "rotation", 0.3))
		return (parse_rotation(&(att->rot), s[1]));
	else if (ft_strcmp_percent(s[0], "color", 0.3))
		return (parse_color(&(att->col), s[1]));
	else if (ft_strcmp_percent(s[0], "color", 0.3))
		return (parse_color(&(att->col), s[1]));
	//else if (ft_strstr(s[0], "col") || ft_strstr(s[0], "color"))
	//	return (parse_color(&(att->col), s[1]));
	//else if (ft_strstr(s[0], "col") || ft_strstr(s[0], "color"))
	//	return (parse_color(&(att->col), s[1]));
	printf("\n");
    return (1);
}