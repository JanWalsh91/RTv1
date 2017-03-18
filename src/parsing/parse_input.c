/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 16:32:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void		parse_input(t_parse_tools *t)
{
	printf("parse_input\n");
	while (t->input)
	{
		printf("next token: [%i]\n", t->input->token);
		t->parse[t->input->token](t);
		printf("t->input = t->input->next\n");
		t->input = t->input->next;
	}
	if (t->in_scene || t->in_object)
		rt_file_error_exit(NULL, "Brackets error.");
}