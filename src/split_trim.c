/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:22:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/12 14:16:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Splits and trims lines from the input file.
** Puts the first string (type) in lowercase.
*/

char 	**split_trim(char *s, char c)
{
	char	**result;
	int		i;
	
	i = -1;
	//printf("split_trim: [%s] [%c]\n", s, c);
	result = ft_strsplit(s, c);
	free(s);
	while (result && result[++i])
	{
		result[i] = ft_strtrim(result[i]);
		ft_strtolower(result[i]);
	}
	//printf("split trim result: [%s] and [%s]\n", result[0], result[1]);
	return (result);
}