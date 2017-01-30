/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:30:40 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 15:34:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Initializes global, scene and element attributes.
*/

int	init_attributes(t_attributes *att)
{
	if (!(att = (t_attributes *)ft_memalloc(sizeof(*att) * 3)))
		return (0);
	return (1);
}