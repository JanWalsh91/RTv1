/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:39:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/25 16:31:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void	rt_file_error_exit(t_parse_tools *t, char *msg)
{
	ft_printf("%{red}ERROR in file %{i}%s%{}%{red} on line %{i}%lu%{}%{red}:\n%s\n%{}",
	t->input->file_name, t->input->line_number, (char *)msg);
	exit(0);
}

void	rt_file_warning(t_parse_tools *t, char *msg)
{
	ft_printf("%{yellow}ERROR in file %{i}%s%{}%{yellow} on line %{i}%lu%{}%{yellow}:\n%s\n%{}",
	t->input->file_name, t->input->line_number, (char *)msg);
}