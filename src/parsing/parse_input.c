/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/20 18:35:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void		parse_input(t_parse_tools *t)
{
	t->input_head = t->input;
	while (t->input)
	{
		t->parse[t->input->token](t);
		t->input = t->input->next;
	}
	if (t->in_scene || t->in_object)
		rt_file_error_exit(NULL, "Brackets error.");
}
