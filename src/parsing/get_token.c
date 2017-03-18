/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:37:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 13:27:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Parses the key in the key-value combination.
** Returns the enum value. 
*/

int	get_token(t_parse_tools *t, char *key)
{
	int		i;

	// printf("get token\n");
	i = 0;
	if (!key)
		return (T_EMPTY_LINE);
	if (ft_strchr(key, '#') && (key[0] == '#'))
		return (T_HASHTAG);
	while (i < (T_COUNT - 1))
	{
		if (t->tokens[i] == NULL)
			ft_errno_exit();
		if (!ft_strcmp(t->tokens[i], key))
			break ;
		++i;
	}
	if (i < T_COUNT)
		return (i);
	else
		return (T_INVALID_TOKEN);
}