/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 14:54:34 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 15:06:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef OBJECT_H
# define OBJECT_H

typedef struct  s_object
{
    t_type      type;
    char        *name;
    void        *t;
    t_vec3      pos;
    t_vec3      rotation;
    t_color     color;
    t_shading   shading;
}               t_object;

#endif