/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:18:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/09 12:08:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Prints an error to the screen and exits the program.
*/

void	error_line_exit(const char *msg, size_t line)
{
	// ft_printf("test: %s\n", msg);
	ft_printf("%{red}ERROR at line: %lu : %s\n%{}", line, (char *)msg);
	exit(0);
}