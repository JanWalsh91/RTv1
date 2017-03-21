/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:01:40 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 16:01:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	free_input(t_input *input);
static void	free_tokens(char **tokens);
static void	free_colors(t_color_list *list);

/*
** Frees the t_parse_tools structure and substructures.
*/

void		free_parse_tools(t_parse_tools *t)
{
	free_input(t->input_head);
	free_colors(t->colors);
	free_tokens(t->tokens);
	free(t->tokens);
	t->tokens = NULL;
	free(t->global_attributes);
	free(t->scene_attributes);
	free(t->object_attributes);
	free(t->parse);
}

static void	free_input(t_input *input)
{
	t_input *tmp;

	while (input)
	{
		tmp = input;
		free(input->value);
		input->value = NULL;
		if (input->file_name)
			free(input->file_name);
		input->file_name = NULL;
		input = input->next;
		free(tmp);
	}
}

static void	free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i])
			free(tokens[i]);
	}
}

static void	free_colors(t_color_list *list)
{
	t_color_list	*tmp;

	while (list)
	{
		tmp = list;
		if (list->name)
			free(list->name);
		list = list->next;
		free(tmp);
	}
}
