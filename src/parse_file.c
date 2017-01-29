/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 18:02:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Parses a file. 
** Updates the t_list scenes.
*/

int parse_file(t_list **scenes, char *file)
{
    int                 fd;
    char                *line;
    int                 ret;
    t_shared_attributes global_att;


    if (!(fd = open(file, O_RDONLY)))
        return (0);    
    while ((ret = get_next_line(fd, &line)) > 0)
        if (!parse_global_attributes(line, &global_att) ||
            !parse_scene(fd, &line, global_att))
         return (0);
    return (1);
}

/*
** Parses the file for scene attributes and objects.
*/

int parse_scene(int fd, char **line, t_shared_attributes global_att)
{
    t_shared_attributes scene_att;
    int                 ret;
    static int  i = -1;

    if (!ft_strchr(*line, '{'))
        return (1);
    while ((ret = get_next_line(fd, line)) > 0 && !ft_strchr(*line, '}'))
        if (!(parse_shared_attributes(line, &scene_att)) ||
        !(parse_objects(fd, line, global_att, scene_att)))
            return (0)
    return (1);
}

/*
** Parses the file for objects.
** If an object is found, adds it to the t_list in scenes
*/

int parse_object(int fd, char **line, t_shared_attributes global_att, t_shared_attributes scene_att)
{
    int ret;
    
    if (!ft_strchr(*line, '{'))
        return (1);
    while ((ret = get_next_line(fd, line)) > 0 && !ft_strchr(*line, '}'))
        //parse first line for object type
        //add that object to list
        //parse for object attributes
        //updates object attributes
    return (1);
}

/*
** Looks for global or scene attirbutes.
** Updates the att structure if found.
*/

int parse_shared_attributes(char *line, t_shared_attributes *att)
{
    int attribute;

    attribute = 0;
    if (ft_strstr(line, "res") || ft_strstr(line, "resolution"))
        attribute = 1;
    else if (ft_strstr(line, "pos") || ft_strstr(line, "position"))
        attribute = 2;
    else if (ft_strstr(line, "rot") || ft_strstr(line, "rotation"))
        attribute = 3;
    else if (ft_strstr(line, "col") || ft_strstr(line, "color"))
        attribute = 4;
    attribute ? line = ft_strchr(line, ':') + 1 : 0;
    line ? update_shared_attributes(att, line, 1) : 0;
    return (1);
}

int update_shared_attirbutes()
{
    return (1);
}