/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 14:50:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 11:47:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef SCENE_H
# define SCENE_H

typedef struct	s_scene
{
    char			*name;
    t_pt2			res;
    int				ray_depth;
    t_camera		*cameras;
    t_light			*lights;
    t_object		*objects;
    struct s_scene	*next;
}				t_scene;

#endif