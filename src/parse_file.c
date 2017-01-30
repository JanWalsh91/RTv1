/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 16:52:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Parses input (combination of all files read).
** Updates the t_list scenes.
*/

static int parse_scene(t_scene ***scenes, char **s, t_list ***input, t_attributes *att);
static int parse_object(t_scene ***scenes, char **s, t_list ***input, t_attributes *att);
static int parse_attribute(char **s, t_attributes *att);
static int update_attribute(char **s, t_attributes *att);

int parse_input(t_scene **scenes, t_list **input)
{
    t_attributes	*att;
	char			**s1;

	if (!(init_attributes(att)))
		return (0);
	while(*input && (*input)->content)
	{
		if (ft_strchr((*input)->content, ':'))
		{
			s1 = split_trim((*input)->content);
			*input = (*input)->next;
			if (ft_strcmp(s1[0], "scene") && !parse_scene(&scenes, s1, &input, att))
				return (0);
			else if (!ft_strcmp(s1[0], "scene") && !update_attribute(s1, &(att[0])))
				return (0);
		}
		*input = (*input)->next;
	}
	return (1);
}

static int parse_scene(t_scene ***scenes, char **s1, t_list ***input, t_attributes *att)
{
	char **s2;

	add_scene(*scenes, get_new_scene(s1[1]));
	//set attribtues
	if (!ft_strchr((**input)->content, '{'))
        return (0); //INVALID FORMAT
	**input = (**input)->next;
	while (**input && !ft_strchr(((**input)->content), '}'))
	{
		if (ft_strchr(((**input)->content), ':'))
		{		
			s2 = split_trim((**input)->content);
			//**input = (**input)->next;
			if (!ft_strcmp(s2[0], "camera") ||
				!ft_strcmp(s2[0], "light") ||
				!ft_strcmp(s2[0], "object")) // add multiple compare
				parse_object(scenes, s2, input, att);
			else if (!update_attribute(s2, &(att[1])))
				return (0);
		}
	}
	//reset scene attribtues
    return (1);
}

/*
** Parses the file for objects.
** If an object is found, adds it to the t_list in scenes
*/

static int parse_object(t_scene ***scenes, char **s2, t_list ***input, t_attributes *att)
{
    int ret;
	char **s3;

	add_object((**scenes)->objects, get_new_object(s2[1], s2[0]));
	if (!ft_strchr((**input)->content, '{'))
        return (0); //INVALID FORMAT
	**input = (**input)->next;
    while (**input && !ft_strchr(((**input)->content), '}'))
	{
		if (ft_strchr(((**input)->content), ':'))
		{
			s3 = split_trim((**input)->content);
			//**input = (**input)->next;
			if (!update_attribute(s3, &(att[2])))
				return (0);
		}
		//set attirbutes.
		//reset object attributes
	}
    return (1);
}

/*
** Updates global or scene attributes.
*/

static int update_attribute(char **s, t_attributes *att)
{
	if (ft_strstr(s[0], "res") || ft_strstr(s[0], "resolution"))
		return (parse_resolution(&(att->res), s[1]));
	else if (ft_strstr(s[0], "pos") || ft_strstr(s[0], "position"))
		return (parse_position(&(att->pos), s[1]));
	else if (ft_strstr(s[0], "rot") || ft_strstr(s[0], "rotation"))
		return (parse_rotation(&(att->rot), s[1]));
	else if (ft_strstr(s[0], "col") || ft_strstr(s[0], "color"))
		return (parse_color(&(att->col), s[1]));
    //if (i == 1)
      //updated corresponding attribute.  
    return (1);
}