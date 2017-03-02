/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:22:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/01 15:57:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Splits and trims lines from the input file.
** Puts the first string (type) in lowercase.
*/

char 	**split_trim(char *s, char c)
{
	char	**result;
	int		i;
	
	i = -1;
	result = ft_strsplit(s, c);
	while (result && result[++i])
		result[i] = ft_strtrim(result[i]);
	ft_strtolower(result[0]);
	return (result);
}