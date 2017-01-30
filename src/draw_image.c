/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 10:59:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int draw_image(t_list *scene)
{
    t_pt2   i;

    i.x = 0;
    i.y = 0;
    //destroy / reset image
    while (i.y < scene.res.y) //for each row
        while (i.x < scene.res.x) //for each column
            trace_camera_ray();
    //get pixel color (ray trace)
    //set pixel colors to image.
    return(1);
}