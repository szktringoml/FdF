#include "fdf.h"

void degrees(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * cos(0.8) - z;
}

void put_pixel(t_fdf *fdf_info, int x, int y, int color)
{
	int i;
	if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
	{
		i = (y * fdf_info->size_line) + (x * fdf_info->bit_per_pixel/8);
		fdf_info->data_addr[i] = color;
		fdf_info->data_addr[i+1] = color >> 8;
		fdf_info->data_addr[i+2] = color >> 16;
	}
}


int calc_color_by_z_value(int max_abs, int z_start, int z_finish, int ratio_of_x)
{
	int color;
	int red = 0xff0000;
	int green = 0x00ff00;
	int blue = 0x0000ff;
	int z;
	z = ratio_of_x * (z_finish - z_start);
	printf("z = %d (ratio = %d)\n", z, ratio_of_x);
	color = 0;
	if(z > 0)
	{
		color = z/max_abs * red/green;
	}
	else if(z < 0)
	{
		color = ft_abs_i(z)/max_abs * blue/green;
	}
	else
		color = 0x00ff00;
	
	return color;
}

void bresenham(int x_start,int y_start, int x_finish, int y_finish, t_fdf *fdf_info)
{
	int z_start;
	int z_finish;


	z_start = fdf_info->z_values[y_start][x_start];
	z_finish = fdf_info->z_values[y_finish][x_finish];
	
	// fdf_info->color = (z_start) ? 0xff0000 : 0xffffff;
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
			put_pixel(fdf_info, x_start + x + 300, y_start + y, calc_color_by_z_value(fdf_info->z_max_abs, z_start, z_finish, x/dx));
		else if(x_start > x_finish && y_start < y_finish)//x:-方向 y:+方向
			put_pixel(fdf_info, x_start - x + 300, y_start + y, calc_color_by_z_value(fdf_info->z_max_abs, z_start, z_finish, x/dx));
		else if(x_start > x_finish && y_start > y_finish)//x:-方向 y:-方向
			put_pixel(fdf_info, x_start - x + 300, y_start - y, calc_color_by_z_value(fdf_info->z_max_abs, z_start, z_finish, x/dx));
		else if(x_start < x_finish && y_start > y_finish)//x:+方向 y:-方向
			put_pixel(fdf_info, x_start + x + 300, y_start - y, calc_color_by_z_value(fdf_info->z_max_abs, z_start, z_finish, x/dx));
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
			printf("座標(y = %d, x = %d)のとき", y, x);
			if(x < fdf_info->width - 1)
				bresenham(x, y, x+1, y, fdf_info);
			if(y < fdf_info->height - 1)
				bresenham(x, y, x, y + 1, fdf_info);
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(fdf_info->mlx_ptr, fdf_info->win_ptr, fdf_info->img_ptr, 0, 0);
}