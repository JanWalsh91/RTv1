/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:20:32 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:51:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Parses a double.
*/

double	parse_double(char *value)
{
	double	new_d;
	int		i;

	new_d = NAN;
	if (ft_charcount(value, ',') ||
		!((ft_charcount(value, '.') == 1) ||
		ft_charcount(value, '.') == 0))
		return (new_d);
	i = -1;
	while (value && value[++i])
		if (!((ft_isdigit(value[i]) || value[i] == '-' ||
			value[i] == '+') || value[i] == '.'))
			return (new_d);
	new_d = ft_atod(value);
	return (new_d);
}
