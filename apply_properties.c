/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:26:09 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/11 18:31:09 by kousuzuk         ###   ########.fr       */
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
	int	z_start;
	int	z_finish;
	int	d;
	int	dx;

	z_start = fdf_info->z_values[fdf_info->coordinate->y_start]
	[fdf_info->coordinate->x_start];
	z_finish = fdf_info->z_values[fdf_info->coordinate->y_finish]
	[fdf_info->coordinate->x_finish];
	printf("%d\n", z_start);
	if(z_start > 0)
		fdf_info->color = 0xff2222;
	else if(z_start < 0)
		fdf_info->color = 0x7777ff;
	else
		fdf_info->color =  0xffffff;
	// fdf_info->color = (z_start) ? 0xe80c0c : 0xffffff; ///////////////normここだけ(4コつく)
	apply_zoom_to_one_line_points(fdf_info);
	apply_degrees(&(fdf_info->coordinate->x_start),
		&(fdf_info->coordinate->y_start),
		z_start);
	apply_degrees(&(fdf_info->coordinate->x_finish),
		&(fdf_info->coordinate->y_finish),
		z_finish);
	d = ft_abs_i(2 * (fdf_info->coordinate->y_finish
				- fdf_info->coordinate->y_start));
	dx = ft_abs_i(fdf_info->coordinate->x_finish
			- fdf_info->coordinate->x_start);
	bresenham_algo(fdf_info, dx, d);
}
