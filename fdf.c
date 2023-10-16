/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:26:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/16 13:38:29 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void z_values_conf(size_t fdfheight, size_t fdfwidth, int **z_values)
// {
// 	size_t height = 0;
// 	size_t width = 0;
// 	while(height < fdfheight)
// 	{
// 		width = 0;
// 		while(width < fdfheight)
// 		{
// 			printf("% i ", z_values[height][width]);
// 			width++;
// 		}
// 		printf("\n");
// 		height++;
// 	}
// }

int	deal_key(int key, t_fdf *fdf_info)
{
	if (fdf_info == NULL)
		return (0);
	if (key == PLUS || key == MINUS)
		zoom_map(fdf_info, key);
	if (key == ALLOW_TOP || key == ALLOW_RIGHT || key == ALLOW_BOTTOM
		|| key == ALLOW_LEFT)
		shift_map(fdf_info, key);
	if (key == ESC)
		close_window(fdf_info);
	if (key == X || key == Y || key == Z)
		routaion_map(fdf_info, key);
	if (key == SPACE)
		init_map(fdf_info);
	mlx_destroy_image(fdf_info->mlx_ptr, fdf_info->img_ptr);
	mlx_clear_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	image_init(fdf_info);
	draw(fdf_info);
	return (0);
}

int	close_window(t_fdf *fdf_info)
{
	mlx_destroy_image(fdf_info->mlx_ptr, fdf_info->img_ptr);
	mlx_clear_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	mlx_destroy_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	exit(SUCCESS_EXIT);
	return (0);
}

void	image_init(t_fdf *fdf_info)
{
	fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
	if (!fdf_info->img_ptr)
		error_malloc();
	fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr,
			&fdf_info->bit_per_pixel,
			&fdf_info->size_line,
			&fdf_info->endian);
	if (!fdf_info->data_addr)
		error_malloc();
}

void	fdf_info_init(t_fdf *fdf_info)
{
	fdf_info->zoom = 30;
	fdf_info->shift_x = 1000;
	fdf_info->shift_y = 150;
	fdf_info->x_routation_theta = 0;
	fdf_info->y_routation_theta = 0;
	fdf_info->z_routation_theta = 0;
	fdf_info->mlx_ptr = mlx_init();
	if (!fdf_info->mlx_ptr)
		error_malloc();
	fdf_info->win_ptr = mlx_new_window(fdf_info->mlx_ptr, WIDTH, HEIGHT, "FDF");
	if (!fdf_info->win_ptr)
		error_malloc();
	image_init(fdf_info);
	fdf_info->coordinate = (t_coordinate *)malloc(sizeof(t_coordinate));
	if (!fdf_info->coordinate)
		error_malloc();
	coordinate_init(fdf_info->coordinate);
}
