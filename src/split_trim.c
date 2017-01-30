/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:22:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 15:26:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Splits and trims lines from the input file. 
*/

char 	**split_trim(char *s)
{
	char	**result = ft_strsplit(s, ':');
	(result[0]) ? result[0] = ft_strtrim(result[0]) : 0;
	(result[1]) ? result[1] = ft_strtrim(result[1]) : 0;
	return (result);
}