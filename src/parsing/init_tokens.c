/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:31:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:49:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	init_tokens2(t_parse_tools *t);

/*
** Initializes the list of tokens for the parser.
** These are strings that the user must match in their rt file.
*/

void		init_tokens(t_parse_tools *t)
{
	if (!(t->tokens = (char **)ft_memalloc(sizeof(char *) * T_COUNT + 1)))
		ft_errno_exit();
	if ((!(t->tokens[T_OPEN_BRACKET] = ft_strdup("{"))) ||
		(!(t->tokens[T_CLOSE_BRACKET] = ft_strdup("}"))) ||
		(!(t->tokens[T_EMPTY_LINE] = ft_strdup(""))) ||
		(!(t->tokens[T_SCENE] = ft_strdup("scene"))) ||
		(!(t->tokens[T_CAMERA] = ft_strdup("camera"))) ||
		(!(t->tokens[T_LIGHT] = ft_strdup("light"))) ||
		(!(t->tokens[T_PLANE] = ft_strdup("plane"))) ||
		(!(t->tokens[T_DISK] = ft_strdup("disk"))) ||
		(!(t->tokens[T_SPHERE] = ft_strdup("sphere"))) ||
		(!(t->tokens[T_CYLINDER] = ft_strdup("cylinder"))) ||
		(!(t->tokens[T_CONE] = ft_strdup("cone"))) ||
		(!(t->tokens[T_RESOLUTION] = ft_strdup("resolution"))) ||
		(!(t->tokens[T_RAY_DEPTH] = ft_strdup("ray depth"))) ||
		(!(t->tokens[T_BACKGROUND_COLOR] = ft_strdup("background color"))) ||
		(!(t->tokens[T_KA] = ft_strdup("ka"))) ||
		(!(t->tokens[T_AMBIENT_LIGHT_COLOR] =
			ft_strdup("ambient light color"))) ||
		(!(t->tokens[T_POSITION] = ft_strdup("position"))))
		ft_errno_exit();
	init_tokens2(t);
}

static void	init_tokens2(t_parse_tools *t)
{
	if ((!(t->tokens[T_DIRECTION] = ft_strdup("direction"))) ||
		(!(t->tokens[T_ROTATION] = ft_strdup("rotation"))) ||
		(!(t->tokens[T_LOOK_AT] = ft_strdup("look at"))) ||
		(!(t->tokens[T_COLOR] = ft_strdup("color"))) ||
		(!(t->tokens[T_RADIUS] = ft_strdup("radius"))) ||
		(!(t->tokens[T_HEIGHT] = ft_strdup("height"))) ||
		(!(t->tokens[T_DIFFUSE_COEF] = ft_strdup("kd"))) ||
		(!(t->tokens[T_REFRACTION] = ft_strdup("refraction"))) ||
		(!(t->tokens[T_REFLECTION] = ft_strdup("reflection"))) ||
		(!(t->tokens[T_SPECULAR_EXPONENT] = ft_strdup("specular exponent"))) ||
		(!(t->tokens[T_SPECULAR_COEF] = ft_strdup("ks"))) ||
		(!(t->tokens[T_TRANSPARENCY] = ft_strdup("transparency"))) ||
		(!(t->tokens[T_FOV] = ft_strdup("fov"))) ||
		(!(t->tokens[T_INTENSITY] = ft_strdup("intensity"))) ||
		(!(t->tokens[T_IMPORT_RT_FILE] = ft_strdup("import rt file"))) ||
		(!(t->tokens[T_READ_RT_FILE] = ft_strdup("read rt file"))) ||
		(!(t->tokens[T_READ_OBJ_FILE] = ft_strdup("read obj file"))) ||
		(!(t->tokens[T_READ_TEXTURE_FILE] = ft_strdup("read texture file"))) ||
		(!(t->tokens[T_READ_MATERIAL_FILE] =
			ft_strdup("read material file"))) ||
		(!(t->tokens[T_HASHTAG] = ft_strdup("#"))) ||
		(!(t->tokens[T_INVALID_TOKEN] = ft_strdup("invalid token"))))
		ft_errno_exit();
	t->tokens[T_COUNT] = NULL;
}
