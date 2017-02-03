/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:30:40 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/03 16:12:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Initializes global, scene and element attributes.
*/

int	init_attributes(t_attributes **att)
{
	int	i;

	printf("INIT_ATTRIBUTES\n");
	if (!(*att = (t_attributes *)ft_memalloc(sizeof(t_attributes) * 3)))
		return (0);
	i = -1;
	while (++i < 3)
		reset_attributes(&((*att)[i]));
	return (1);
}