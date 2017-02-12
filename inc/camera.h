/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 15:01:34 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/11 12:30:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_camera
{
    char			*name;
    t_vec3			pos;
    t_vec3			direction;
	struct s_camera	*next;
}				t_camera;

#endif