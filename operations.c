/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:40 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/11 18:36:06 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_fdf *fdf_info)
{
	fdf_info->zoom = 10;
	fdf_info->shift_x = 300;
	fdf_info->shift_y = 150;
	fdf_info->x_routation_theta = 0;
	fdf_info->y_routation_theta = 0;
	fdf_info->z_routation_theta = 0;
}

void	shift_map(t_fdf *fdf_info, int key)
{
	if (key == ALLOW_TOP)
		fdf_info->shift_y -= 500;
	if (key == ALLOW_RIGHT)
		fdf_info->shift_x += 500;
	if (key == ALLOW_BOTTOM)
		fdf_info->shift_y += 500;
	if (key == ALLOW_LEFT)
		fdf_info->shift_x -= 500;
}

void	zoom_map(t_fdf *fdf_info, int key)
{
	if (key == PLUS && fdf_info->zoom < 1000)
		fdf_info->zoom += 10;
	if (key == MINUS && fdf_info->zoom > 10)
		fdf_info->zoom -= 10;
}

void	routaion_map(t_fdf *fdf_info, int key)
{
	if(key == X)
	{
		if(fdf_info->x_routation_theta > 5.5)
			fdf_info->x_routation_theta = 0;
		else
			fdf_info->x_routation_theta += 0.8;
	}
	if(key == Y)
	{
		if(fdf_info->y_routation_theta > 5.5)
			fdf_info->y_routation_theta = 0;
		else
			fdf_info->y_routation_theta += 0.8;
	}
	if(key == Z)
	{
		if(fdf_info->z_routation_theta > 5.5)
			fdf_info->z_routation_theta = 0;
		else
			fdf_info->z_routation_theta += 0.8;
	}
}
