/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:31:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/20 18:35:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	init_tokens2(t_parse_tools *t);

void	init_tokens(t_parse_tools *t)
{
	if (!(t->tokens = (char **)ft_memalloc(sizeof(char *) * T_COUNT + 1)))
		ft_errno_exit();
	if (!(t->tokens[T_OPEN_BRACKET] = ft_strdup("{")))
		ft_errno_exit();
	if (!(t->tokens[T_CLOSE_BRACKET] = ft_strdup("}")))
		ft_errno_exit();
	if (!(t->tokens[T_EMPTY_LINE] = ft_strdup("")))
		ft_errno_exit();
	if (!(t->tokens[T_SCENE] = ft_strdup("scene")))
		ft_errno_exit();
	if (!(t->tokens[T_CAMERA] = ft_strdup("camera")))
		ft_errno_exit();
	if (!(t->tokens[T_LIGHT] = ft_strdup("light")))
		ft_errno_exit();
	if (!(t->tokens[T_PLANE] = ft_strdup("plane")))
		ft_errno_exit();
	if (!(t->tokens[T_DISK] = ft_strdup("disk")))
		ft_errno_exit();
	if (!(t->tokens[T_SPHERE] = ft_strdup("sphere")))
		ft_errno_exit();
	if (!(t->tokens[T_CYLINDER] = ft_strdup("cylinder")))
		ft_errno_exit();
	if (!(t->tokens[T_CONE] = ft_strdup("cone")))
		ft_errno_exit();
	if (!(t->tokens[T_RESOLUTION] = ft_strdup("resolution")))
		ft_errno_exit();
	if (!(t->tokens[T_RAY_DEPTH] = ft_strdup("ray depth")))
		ft_errno_exit();
	if (!(t->tokens[T_BACKGROUND_COLOR] = ft_strdup("background color")))
		ft_errno_exit();
	if (!(t->tokens[T_KA] = ft_strdup("ka")))
		ft_errno_exit();
	if (!(t->tokens[T_AMBIENT_LIGHT_COLOR] = ft_strdup("ambient light color")))
		ft_errno_exit();
	if (!(t->tokens[T_POSITION] = ft_strdup("position")))
		ft_errno_exit();
	init_tokens2(t);
}

static void	init_tokens2(t_parse_tools *t)
{
	if (!(t->tokens[T_DIRECTION] = ft_strdup("direction")))
		ft_errno_exit();
	if (!(t->tokens[T_ROTATION] = ft_strdup("rotation")))
		ft_errno_exit();
	if (!(t->tokens[T_LOOK_AT] = ft_strdup("look at")))
		ft_errno_exit();
	if (!(t->tokens[T_COLOR] = ft_strdup("color")))
		ft_errno_exit();
	if (!(t->tokens[T_RADIUS] = ft_strdup("radius")))
		ft_errno_exit();
	if (!(t->tokens[T_HEIGHT] = ft_strdup("height")))
		ft_errno_exit();
	if (!(t->tokens[T_DIFFUSE_COEF] = ft_strdup("kd")))
		ft_errno_exit();
	if (!(t->tokens[T_REFRACTION] = ft_strdup("refraction")))
		ft_errno_exit();
	if (!(t->tokens[T_REFLECTION] = ft_strdup("reflection")))
		ft_errno_exit();
	if (!(t->tokens[T_SPECULAR_EXPONENT] = ft_strdup("specular exponent")))
		ft_errno_exit();
	if (!(t->tokens[T_SPECULAR_COEF] = ft_strdup("ks")))
		ft_errno_exit();
	if (!(t->tokens[T_TRANSPARENCY] = ft_strdup("transparency")))
		ft_errno_exit();
	if (!(t->tokens[T_FOV] = ft_strdup("fov")))
		ft_errno_exit();
	if (!(t->tokens[T_INTENSITY] = ft_strdup("intensity")))
		ft_errno_exit();
	if (!(t->tokens[T_IMPORT_RT_FILE] = ft_strdup("import rt file")))
		ft_errno_exit();
	if (!(t->tokens[T_READ_RT_FILE] = ft_strdup("read rt file")))
		ft_errno_exit();
	if (!(t->tokens[T_READ_OBJ_FILE] = ft_strdup("read obj file")))
		ft_errno_exit();
	if (!(t->tokens[T_READ_TEXTURE_FILE] = ft_strdup("read texture file")))
		ft_errno_exit();
	if (!(t->tokens[T_READ_MATERIAL_FILE] = ft_strdup("read material file")))
		ft_errno_exit();
	if (!(t->tokens[T_HASHTAG] = ft_strdup("#")))
		ft_errno_exit();
	if (!(t->tokens[T_INVALID_TOKEN] = ft_strdup("invalid token")))
		ft_errno_exit();
	t->tokens[T_COUNT] = NULL;
}
