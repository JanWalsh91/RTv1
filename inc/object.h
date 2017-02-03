/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 14:54:34 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/01 17:31:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#ifndef OBJECT_H
# define OBJECT_H

typedef struct	s_object
{
	t_type			type;
    char			*name;
	int				rad;
    void			*t;
    t_vec3			pos;
    t_vec3			rot;
    t_color			col;
    t_shading		shading;
	struct s_object	*next;
}				t_object;

#endif