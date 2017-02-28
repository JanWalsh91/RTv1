/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:37:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/28 12:25:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Parses the key in the key-value combination.
** Returns the enum value. 
*/

int	get_token(char *key)
{
	int		i;

	i = 0;
	if (ft_strchr(key, '#'))
		return (T_HASHTAG);
	while (i < (T_COUNT - 1) && ft_strcmp(TOKENS[i], key))
		++i;
	if (i < T_COUNT)
	{
		//free list.
		return (i);
	}
	else
		return (T_INVALID_TOKEN);
	//free list.
}