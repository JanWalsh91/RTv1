/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:13:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:46:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Parses a color attribute. Three formats available:
** - rgb (three ints separated by commas)
** - hexadecimal (hex value starting with 0x or 0X
** - name (string found in res/colors.txt).
*/

t_vec3	get_color(t_parse_tools *t, char *value)
{
	t_vec3	new_col;

	if (ft_charcount(value, ',') == 2)
		new_col = parse_rgb(value);
	else if (ft_charcount(value, ',') != 0)
		return (v_new(NAN, NAN, NAN));
	else if (value && value[0] == '0' && ft_tolower(value[1]) == 'x')
		new_col = parse_hexadecimal(value);
	else if (value && ft_isalpha(value[0]))
		new_col = parse_color_name(t, value);
	else
		return (v_new(NAN, NAN, NAN));
	return (new_col);
}

/*
** Parsing a vector is the same as parsing rgb input.
*/

t_vec3	parse_rgb(char *value)
{
	return (parse_vector(value));
}

/*
** Parses the hexademial color, converts it and returns the color if valid.
*/

t_vec3	parse_hexadecimal(char *value)
{
	int		i;
	t_vec3	new_col;

	i = 2;
	if (!valid_hex_format(value, &i))
		return (v_new(NAN, NAN, NAN));
	new_col = v_new(0, 0, 0);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.z = get_hex_value(value[--i]);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.z += 16 * get_hex_value(value[--i]);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.y = get_hex_value(value[--i]);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.y += 16 * get_hex_value(value[--i]);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.x = get_hex_value(value[--i]);
	if (ft_tolower(value[i - 1]) != 'x')
		new_col.x += 16 * get_hex_value(value[--i]);
	return (new_col);
}

bool	valid_hex_format(char *value, int *i)
{
	if (!(value && value[0] == '0' && ft_tolower(value[1]) == 'x') ||
		(value && ft_strlen(value) > 8))
	{
		ft_printf("%{yellow}Invalid hexademical format.\n%{}");
		return (false);
	}
	while (value[*i])
	{
		if (!(ft_isdigit(value[*i]) || ('a' <= ft_tolower(value[*i]) &&
			ft_tolower(value[*i]) <= 'f')))
		{
			ft_printf("%{yellow}Invalid hexademical format.\n%{}");
			return (false);
		}
		++*i;
	}
	if (ft_tolower(value[*i - 1]) == 'x')
	{
		ft_printf("%{yellow}Invalid hexademical format.\n%{}");
		return (false);
	}
	return (true);
}

int		get_hex_value(char c)
{
	int	i;

	c = ft_toupper(c);
	if (ft_isdigit(c))
		i = c - '0';
	else if ('A' <= c && c <= 'F')
		i = c - 'A' + 10;
	else
		i = 0;
	return (i);
}
