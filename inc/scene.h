/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 14:50:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 14:56:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef SCENE_H
# define SCENE_H

typedef struct  s_scene
{
    char    *name;
    t_pt2   resolution;
    t_list  **cameras;
    t_list  **lights;
    t_list  **objects;
}               t_scene;

#endif