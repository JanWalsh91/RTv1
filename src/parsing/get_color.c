/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:13:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/02 15:07:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_vec3	get_color(t_parse_tools *t, char *value)
{
	t_vec3	new_col;
	
	if (ft_charcount(value, ',') == 2)
		new_col = parse_rgb(t, value);
	else if (ft_charcount(value, ',') != 0)
		return (v_new(NAN, NAN, NAN));
	else if (value && value[0] == '0' && ft_tolower(value[1]) == 'x')
		new_col = parse_hexadecimal(t, value);
	else if (value && ft_isalpha(value[0]))
		new_col = parse_color_name(t, value);
	else
		return (v_new(NAN, NAN, NAN));
	return (new_col);

	//check if there are commas ->parse rgb
	//check if first two chars are 0x or 0X ->parse hexademical
	//check if first char is alpha ->parse color_name
}

//add debug here from outside function
t_vec3	parse_rgb(t_parse_tools *t, char *value)
{
	(void)t;
	return (parse_vector(value));
}

t_vec3	parse_hexadecimal(t_parse_tools *t, char *value)
{
	int		i;
	t_vec3	new_col;

	i = 2;
	new_col = v_new(NAN, NAN, NAN);
	if (!(value && value[0] == '0' && ft_tolower(value[1]) == 'x') ||
	 (value && ft_strlen(value) > 8))
	{
		rt_file_warning(t, "Invalid hexademical format.");
		return (new_col);
	}
	while (value[i])
	{
		if (!(ft_isdigit(value[i]) || ('a' <= ft_tolower(value[i]) && ft_tolower(value[i]) <= 'f')))
		{
			printf("value: [%c]\n", value[i]);
			rt_file_warning(t, "Invalid hexademical format.");
			return (new_col);
		}
		++i;
	}
	if (ft_tolower(value[i - 1]) == 'x')
	{
		rt_file_warning(t, "Invalid hexademical format.");
		return (new_col);
	}
	ft_tolower(value[i - 1]) != 'x' ? new_col.z = get_hex_value(value[--i]) : 0;
	ft_tolower(value[i - 1]) != 'x' ? new_col.z += 16 * get_hex_value(value[--i]) : 0;
	ft_tolower(value[i - 1]) != 'x' ? new_col.y = get_hex_value(value[--i]) : 0;
	ft_tolower(value[i - 1]) != 'x' ? new_col.y += 16 * get_hex_value(value[--i]) : 0;
	ft_tolower(value[i - 1]) != 'x' ? new_col.x = get_hex_value(value[--i]) : 0;
	ft_tolower(value[i - 1]) != 'x' ? new_col.x += 16 * get_hex_value(value[--i]) : 0;
	return (new_col);
}

int	get_hex_value(char c)
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

t_vec3	parse_color_name(t_parse_tools *t, char *value)
{
	t_vec3	new_col;

	new_col = v_new(NAN, NAN, NAN);
	if (!t->colors)
		init_color_list(&t->colors);
	if (find_color_value(t->colors, value, &new_col))
		return (new_col);
	else
		rt_file_warning(t, "Color name not found.");
	return (new_col);
}

/*
** Looks for matching color in t->colors. Returns 1 if found, 0 if not.
** If found, modifies new_col.
*/

bool	find_color_value(t_color_list *colors, char *value, t_vec3 *new_col)
{
	t_color_list *ptr;

	ptr = colors;
	while (ptr)
	{
		if (!ft_strcmp(value, ptr->name))
		{
			*new_col = ptr->value;
			return (true);
		}
		ptr = ptr->next;
	}
	return (false);
}