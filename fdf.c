/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:26:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/13 17:40:58 by kousuzuk         ###   ########.fr       */
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
	mlx_clear_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
	fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr,
			&fdf_info->bit_per_pixel,
			&fdf_info->size_line,
			&fdf_info->endian);
	draw(fdf_info);
	return (0);
}

int	close_window(t_fdf *fdf_info)
{
	mlx_destroy_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	exit(SUCCESS_EXIT);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q fdf");
// }

void	fdf_info_init(t_fdf *fdf_info)
{
	fdf_info->zoom = 30;
	fdf_info->shift_x = 1000;
	fdf_info->shift_y = 150;
	fdf_info->mlx_ptr = mlx_init();
	fdf_info->win_ptr = mlx_new_window(fdf_info->mlx_ptr, WIDTH, HEIGHT, "FDF");
	fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
	fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr,
			&fdf_info->bit_per_pixel,
			&fdf_info->size_line,
			&fdf_info->endian);
	fdf_info->coordinate = (t_coordinate *)malloc(sizeof(t_coordinate));
	coordinate_init(fdf_info->coordinate);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf_info;

	if (argc == 2)
	{
		fdf_info = (t_fdf *)malloc(sizeof(t_fdf));
		error_filename(argv[1]);
		read_fdf(&fdf_info, argv[1]);
		fdf_info_init(fdf_info);
		draw(fdf_info);
		mlx_key_hook(fdf_info->win_ptr, deal_key, fdf_info);
		mlx_hook(fdf_info->win_ptr, 17, 1L << 17, close_window, fdf_info);
		mlx_loop(fdf_info->mlx_ptr);
	}
	else
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}
}
