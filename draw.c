/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:16:07 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 18:37:16 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_degrees(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * cos(0.8) - z;
}

void	put_pixel(t_fdf *fdf_info, int x, int y, int color)
{
	int	i;

	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
	{
		i = (y * fdf_info->size_line) + (x * fdf_info->bit_per_pixel / 8);
		fdf_info->data_addr[i] = color;
		fdf_info->data_addr[i + 1] = color >> 8;
		fdf_info->data_addr[i + 2] = color >> 16;
	}
}

void	put_pixel_hub(t_fdf *fdf_info, int x, int y)
{
	if (fdf_info->coordinate->x_start < fdf_info->coordinate->x_finish
		&& fdf_info->coordinate->y_start < fdf_info->coordinate->y_finish)
	{
		put_pixel(fdf_info, fdf_info->coordinate->x_start + x
			+ fdf_info->shift_x, fdf_info->coordinate->y_start + y
			+ fdf_info->shift_y, fdf_info->color);
	}
	else if (fdf_info->coordinate->x_start > fdf_info->coordinate->x_finish
		&& fdf_info->coordinate->y_start < fdf_info->coordinate->y_finish)
	{
		put_pixel(fdf_info, fdf_info->coordinate->x_start - x
			+ fdf_info->shift_x, fdf_info->coordinate->y_start + y
			+ fdf_info->shift_y, fdf_info->color);

	}
	else if (fdf_info->coordinate->x_start > fdf_info->coordinate->x_finish
		&& fdf_info->coordinate->y_start > fdf_info->coordinate->y_finish)
	{
		put_pixel(fdf_info, fdf_info->coordinate->x_start - x
			+ fdf_info->shift_x, fdf_info->coordinate->y_start - y
			+ fdf_info->shift_y, fdf_info->color);
	}
	else if (fdf_info->coordinate->x_start < fdf_info->coordinate->x_finish
		&& fdf_info->coordinate->y_start > fdf_info->coordinate->y_finish)
	{
		put_pixel(fdf_info, fdf_info->coordinate->x_start + x
			+ fdf_info->shift_x, fdf_info->coordinate->y_start - y
			+ fdf_info->shift_y, fdf_info->color);
	}
}

void	bresenham_algo(t_fdf *fdf_info, int dx, int d)
{
	int	e;
	int	y;
	int	x;

	x = 0;
	e = 0;
	y = 0;
	while (x < dx)
	{
		e = e + d;
		if (e > dx)
		{
			y = y + 1;
			e = e - (2 * dx);
		}
		get_color_by_z_value(fdf_info, dx, x);
		put_pixel_hub(fdf_info, x, y);
		x++;
	}
}

void	draw(t_fdf *fdf_info)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf_info->height)
	{
		x = 0;
		while (x < fdf_info->width)
		{
			if (x < fdf_info->width - 1)
			{
				coordinate_store_x(fdf_info->coordinate, x, y);
				apply_properties_to_one_line_points(fdf_info);
			}
			if (y < fdf_info->height - 1)
			{
				coordinate_store_y(fdf_info->coordinate, x, y);
				apply_properties_to_one_line_points(fdf_info);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf_info->mlx_ptr, fdf_info->win_ptr,
		fdf_info->img_ptr, 0, 0);
}
