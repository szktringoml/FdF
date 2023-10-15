/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:26:09 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/13 13:28:35 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_zoom_to_one_line_points(t_fdf *fdf_info)
{
	fdf_info->coordinate->x_start = fdf_info->coordinate->x_start
		* fdf_info->zoom;
	fdf_info->coordinate->y_start = fdf_info->coordinate->y_start
		* fdf_info->zoom;
	fdf_info->coordinate->x_finish = fdf_info->coordinate->x_finish
		* fdf_info->zoom;
	fdf_info->coordinate->y_finish = fdf_info->coordinate->y_finish
		* fdf_info->zoom;
}

void	apply_properties_to_one_line_points(t_fdf *fdf_info)
{
	int	d;
	int	dx;
	
	fdf_info->coordinate->z_start = fdf_info->z_values[fdf_info->coordinate->y_start]
	[fdf_info->coordinate->x_start];
	fdf_info->coordinate->z_finish = fdf_info->z_values[fdf_info->coordinate->y_finish]
	[fdf_info->coordinate->x_finish];
	//fdf_info->color = (fdf_info->coordinate->z_start) ? 0xe80c0c : 0xffffff; ///////////////normここだけ(4)
	apply_zoom_to_one_line_points(fdf_info);
	// apply_degrees(&(fdf_info->coordinate->x_start),
	// 	&(fdf_info->coordinate->y_start),
	// 	fdf_info->coordinate->z_start);
	// apply_degrees(&(fdf_info->coordinate->x_finish),
	// 	&(fdf_info->coordinate->y_finish),
	// 	fdf_info->coordinate->z_finish);
	routation_x(fdf_info, &(fdf_info->coordinate->x_start),
		&(fdf_info->coordinate->y_start),
		&fdf_info->coordinate->z_start);
	routation_x(fdf_info, &(fdf_info->coordinate->x_finish),
		&(fdf_info->coordinate->y_finish),
		&fdf_info->coordinate->z_finish);
	routation_y(fdf_info, &(fdf_info->coordinate->x_start),
		&(fdf_info->coordinate->y_start),
		&fdf_info->coordinate->z_start);
	routation_y(fdf_info, &(fdf_info->coordinate->x_finish),
		&(fdf_info->coordinate->y_finish),
		&fdf_info->coordinate->z_finish);
	routation_z(fdf_info, &(fdf_info->coordinate->x_start),
		&(fdf_info->coordinate->y_start),
		&fdf_info->coordinate->z_start);
	routation_z(fdf_info, &(fdf_info->coordinate->x_finish),
		&(fdf_info->coordinate->y_finish),
		&fdf_info->coordinate->z_finish);
	get_color_range_in_this_line(fdf_info);
	fdf_info->color_info->put_pixel_cnt_in_this_line = 0;
	d = ft_abs_i(2 * (fdf_info->coordinate->y_finish
				- fdf_info->coordinate->y_start));
	dx = ft_abs_i(fdf_info->coordinate->x_finish
			- fdf_info->coordinate->x_start);
	bresenham_algo(fdf_info, dx, d);
}
