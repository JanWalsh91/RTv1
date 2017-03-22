/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:39:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 15:16:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Exits the program atfer printing an error message.
*/

void	rt_file_error_exit(t_parse_tools *t, char *msg)
{
	if (t)
		ft_printf("%{red}ERROR in file \"%{i}%s%{}%{red}\" on \
line %{i}%lu%{}%{red}:\n%s\n%{}",
	t->input->file_name, t->input->line_number, (char *)msg);
	else
		ft_printf("%{red}ERROR: %s\n", msg);
	exit(0);
}

/*
** Displays a warning message.
*/

void	rt_file_warning(t_parse_tools *t, char *msg)
{
	if (t)
		ft_printf("%{yellow}WARNING in file \"%{i}%s%{}%{yellow}\" \
on line %{i}%lu%{}%{yellow}:\n%s\n%{}",
	t->input->file_name, t->input->line_number, (char *)msg);
	else
		ft_printf("%{yellow}WARNING: %s\n", msg);
}

/*
** Exits the program atfer printing an error message.
*/

void	data_error_exit(t_scene *scene, int type, void *object, char *msg)
{
	if (type == T_CAMERA)
		ft_printf("%{red}ERROR in scene \"%s\" in camera \"%s\":\n%s%{}\n",
		scene->name, ((t_camera *)object)->name, msg);
	else if (type == T_LIGHT)
		ft_printf("%{red}ERROR in scene \"%s\" in light \"%s\":\n%s%{}\n",
		scene->name, ((t_light *)object)->name, msg);
	else if (type == T_SPHERE || type == T_PLANE ||
		type == T_DISK || type == T_CYLINDER || type == T_CONE)
		ft_printf("%{red}ERROR in scene \"%s\" in object \"%s\":\n%s%{}\n",
		scene->name, ((t_object *)object)->name, msg);
	else if (scene)
		ft_printf("%{red}ERROR in scene: \"%s\":\n%s%{}\n", scene->name, msg);
	else
		ft_printf("%{red}ERROR:\n%s%{}\n", msg);
	exit(0);
}

/*
** Displays a warning message.
*/

void	data_warning(t_scene *scene, int type, void *object, char *msg)
{
	if (type == T_CAMERA)
		ft_printf("%{yellow}WARNING in scene \"%s\" in camera \"%s\":\n%s%{}\n",
		scene->name, ((t_camera *)object)->name, msg);
	else if (type == T_LIGHT)
		ft_printf("%{yellow}WARNING in scene \"%s\" in light \"%s\":\n%s%{}\n",
		scene->name, ((t_light *)object)->name, msg);
	else if (type == T_SPHERE || type == T_PLANE ||
		type == T_DISK || type == T_CYLINDER || type == T_CONE)
		ft_printf("%{yellow}WARNING in scene \"%s\" in object \"%s\":\n%s%{}\n",
		scene->name, ((t_object *)object)->name, msg);
	else
		ft_printf("%{yellow}WARNING in scene: \"%s\":\n%s%{}\n",
		scene->name, msg);
}
