/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:30 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/16 13:45:14 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q fdf");
// }

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

// int	main(void)
// {
// 	float xi = 0;
// 	float y = 0;

// 	while (xi < x_finish)
// 	{
// 		y = (int)(y_finish - y_start) / (int)(x_finish - x_finish) * (xi
// 				- x_start) + y_start;
// 		output(xi, y);
// 	}
// 	// ============================================
//      =============================================
// 	float xi = 0;
// 	float y = 0;

// 	float e = 0; //端数
// 	float d = (int)(y_finish - y_start) / (int)(x_finish - x_start);
// 	y = y_start;
// 	while (xi < x_finish)
// 	{
// 		e = e + d * (xi - x_start);
// 		if (e > 0.5)
// 		{
// 			y = y + 1;
// 			e = e - 1.0; //yが増加した分次のループで矛盾しないように
// 		}

// 		output(xi, y);

// 		e = 0;
// 	}
// 	// ==========================================
//      ===============================================
// 	int xi = 0;
// 	int y = 0;

// 	int e = 0; //端数
// 	int d = 2 * (int)(y_finish - y_start);
// 	int dx = (int)(x_finish - x_start);
// 	y = y_start;
// 	while (xi < x_finish)
// 	{
// 		e = e + d * (xi - x_start);
// 		if (e > dx)
// 		{
// 			y = y + 1;
// 			e = e - 2 * dx; //yが増加した分次のループで矛盾しないように
// 		}

// 		output(xi, y);
// 	}
// }