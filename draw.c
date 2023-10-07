#include "fdf.h"

void degrees(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * cos(0.8) - z;
}

void put_pixel(t_fdf *fdf_info, int x, int y, int color)
{
	int i;
	// printf("(y = %d, x = %d)\n", y, x);
	if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
	{
		i = (y * fdf_info->size_line) + (x * fdf_info->bit_per_pixel/8);
		// printf("  i = %d", i);
		fdf_info->data_addr[i] = color;
		fdf_info->data_addr[i+1] = color >> 8;
		fdf_info->data_addr[i+2] = color >> 16;
	}
}

//dxは結局１になるので省略してfdf_info->zoomで良い
//第一引数は(引く方向＿線の始まり).第二引数は傾きを得ためのもの

void bresenham(int x_start,int y_start, int x_finish, int y_finish, t_fdf *fdf_info)
{
	int z_start;
	int z_finish;
	//dx *= fdf_info->zoom;
	z_start = fdf_info->z_values[y_start][x_start];
	z_finish = fdf_info->z_values[y_finish][x_finish];
	
	fdf_info->color = (z_start) ? 0xe80c0c : 0xffffff;

	//calc_bresenham_x(x_start, y_start, y_finish, fdf_info);
	x_start = x_start*fdf_info->zoom;
	y_start = y_start*fdf_info->zoom;
	x_finish = x_finish*fdf_info->zoom;
	y_finish = y_finish*fdf_info->zoom;
	// printf("prev : (y_start: %d , x_start: %d) (y_finish: %d , x_finish: %d)\n", y_start, x_start, y_finish, x_finish);
	degrees(&x_start, &y_start, z_start);
	degrees(&x_finish, &y_finish, z_finish);
	// printf("after : (y_start: %d , x_start: %d) (y_finish: %d , x_finish: %d)\n", y_start, x_start, y_finish, x_finish);

	int d = ft_abs_i(2 * (y_finish - y_start));
	int dx = ft_abs_i(x_finish - x_start);
	int e;
	int y;
	int x = 0;
	e = 0;
	y = 0; 
	while(x < dx)//dxが0だと入らないので条件分岐が必要
	{
		e = e + d;
		if(e > dx)
		{
		 	y = y + 1;
			e = e - (2 * dx);
		}
		if(x_start < x_finish && y_start < y_finish)//x:+方向 y:+方向
			put_pixel(fdf_info, x_start + x + 300, y_start + y, fdf_info->color);
		else if(x_start > x_finish && y_start < y_finish)//x:-方向 y:+方向
			put_pixel(fdf_info, x_start - x + 300, y_start + y, fdf_info->color);
		else if(x_start > x_finish && y_start > y_finish)//x:-方向 y:-方向
			put_pixel(fdf_info, x_start - x + 300, y_start - y, fdf_info->color);
		else if(x_start < x_finish && y_start > y_finish)//x:+方向 y:-方向
			put_pixel(fdf_info, x_start + x + 300, y_start - y, fdf_info->color);
		x++;
	}
}

void draw(t_fdf *fdf_info)
{
	int x;
	int y;
	int i = 0;

	y = 0;
	while(y < fdf_info->height)
	{
		x = 0;
		while(x < fdf_info->width)
		{
			if(x < fdf_info->width - 1)
			{
				// printf("= = = = = = = = = (%d : %d)  = = = = = = = = = = = =\n", y, x);
				bresenham(x, y, x+1, y, fdf_info);
			}
			if(y < fdf_info->height - 1)
				bresenham(x, y, x, y + 1, fdf_info);
			x++;
		}
		//printf("\n");
		y++;
	}
	//mlx_put_image_to_window(fdf_info->mlx_ptr, fdf_info->win_ptr, fdf_info->img_ptr, 0, 0);
}