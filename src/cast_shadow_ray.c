/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:22:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 10:34:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int	intersection(t_object *obj, t_ray *cam_ray, t_ray *ray, t_object *light);

void	cast_shadow_ray(t_ray *cam_ray, t_object *hitobj, t_scene *scene)
{
	t_object	*light;
	t_ray		ray;
	t_color		new_col;
	// static int	i = 1000;

	light = scene->lights;
	ray.origin = v_add(cam_ray->hit, v_scale(cam_ray->nhit, BIAS));
	while (light)
	{
		if (!intersection(scene->objects, cam_ray, &ray, light))
		{
			double r2 = powf(v_length(v_sub(cam_ray->hit, light->pos)), 2.0);
			new_col = v_scale(v_mult(light->col, v_scale(hitobj->col, light->intensity / (255.0 * 4 * M_PI * r2))), ft_clampd(v_dot(v_scale(ray.dir, -1), cam_ray->nhit), 0, 1));
			new_col = v_clamp(new_col, 0, 255);
			cam_ray->col = v_clamp(v_add(cam_ray->col, new_col), 0, 255);
			// print_vec(cam_ray->col);
		}
		// else
		// {
		// 	if (i)
		// 	{
		// 		C(1)
		// 		i--;
		// 	}
		// 	cam_ray->col = v_add(cam_ray->col, v_new(0, 0, 0));

		// }
		light = light->next;
	}
}

static int	intersection(t_object *obj, t_ray *cam_ray, t_ray *ray, t_object *light)
{
	double	t;
	// static int i = 1;
	// static int y = 500;

	ray->dir = v_norm(v_sub(cam_ray->hit, light->pos));
	t = v_length(v_sub(light->pos, cam_ray->hit));
	// if (y)
	// {
	// 	ft_printf("%{green}intersection%{}\n");
	// 	print_vec(ray->origin);
	// 	print_vec(ray->dir);
	// 	print_vec(light->pos);
	// }
	while (obj)
	{
		//if intersection is found,
		ray->t = INFINITY;
				// if (y)
				// {
				// 	printf("t: [%f]\n", t);
				// 	printf("obj: [%s]\n", obj->name);
				// 	y--;
				// }
		if (get_intersection(ray, obj))
		{
			//if intersection point between origin and light,
			// if (y)
			// {
			// 	printf("found intersection: ray->t: [%f]\n", ray->t);
			// }
			if (0 < ray->t && ray->t < t)
			{
				//valid intersection found
				// if (y)
				// {
				// 	printf("return 1\n");
				// }
				return (0);
			}
		}
		obj = obj->next;
	}
	// if (y)
	// {
	// 	ft_printf("%{red}return 0\n%{}");
	// }
	return (1);
}

// hitobj->col

// v_mult(hitobj->col, v_scale(light->col, 1 / 255))
// diffuse color

// spherical light distance

// phong