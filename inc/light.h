/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 15:02:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 12:09:03 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef LIGHT_H
# define LIGHT_H

typedef struct	s_light
{
    char			*name;
    t_vec3			pos;
    //t_vec3		rotation;
    t_color			color;
    struct s_light	*next;
}				t_light;

#endif