/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:37:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 15:45:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Parses the key in the key-value combination.
** Returns the enum value. 
*/

int	get_token(char *key)
{
	char	**list;
	int		i;

	i = 0;	
	list = ft_strsplit(TYPES, ',');
	while (i < OBJECT_COUNT && ft_strcmp(list[i], key))
		++i;
	if (i < OBJECT_COUNT)
	{
		//free list.
		return (i);
	}
	//free list.
	ft_error_exit("Formatting error in .rt file: invalid key");
	return (0); //ERROR: INVALID OBJECT key
}