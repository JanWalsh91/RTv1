/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 15:02:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 15:03:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef LIGHT_H
# define LIGHT_H

typedef struct  s_light
{
    char        *name;
    t_vec3      pos;
    //t_vec3      rotation;
    t_color     color;
}               t_light;

#endif