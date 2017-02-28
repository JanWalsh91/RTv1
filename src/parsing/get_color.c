/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:13:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/28 15:51:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_vec3	get_color(char *value)
{
	t_vec3	new_col;
	
	if (ft_charcount(value, ',') == 2)
		new_col = parse_rgb(value);
	else if (ft_charcount(value, ',') != 0)
		return (v_new(NAN, NAN, NAN));
	else if (value && value[0] == '0' && ft_tolower(value[1]) == 'x')
		new_col = parse_hexadecimal(value);
	else if (value && ft_isalpha(value[0]))
		new_col = parse_color_name(value);
	else
		return (v_new(NAN, NAN, NAN));
	

	//check if there are commas ->parse rgb
	//check if first two chars are 0x or 0X ->parse hexademical
	//check if first char is alpha ->parse color_name
}

t_vec3	parse_rgb(char *value)
{
	return (parse_vector(value));
}

t_vec3	parse_hexadecimal(char *value)
{
	//check if only digits and a-f and A-F after 0x/0X.
	//start at end: add last digit to blue
	//add next * 16 to blue
	//add next to green
	//add next * 16 to green
	// same for red.
	//stop if x or X is reached. 
}

t_vec3	parse_color_name(char *value)
{
	int	i;

	i = -1;
	while (value && value[++i])
	{
		if (!ft_isalpha(value[i]) && value[i] != ' ')
			return (v_new(NAN, NAN, NAN));
	}
	i = -1;
	while (!ft_strcmp(COLORS_CHAR[1][1], value))
	{
		
	}
}