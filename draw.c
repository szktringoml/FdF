#include "fdf.h"

void degrees(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * cos(0.8) - z;
}


int abs_i(int x)
{
	if(x < 0)
	{
		return -x;
	}
	else
		return x;
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
	if(z_start > 0){
		fdf_info->color = 0x008000 + (fdf_info->plus_color * z_start) ;
		printf("=======================================================================================\n");
		printf("color = %dにしたいのに%dになる\n",16711680,0x008000 + (fdf_info->plus_color * z_start));}
	else
		fdf_info->color = 0x008000 - (fdf_info->minus_color * z_start);
	//fdf_info->color = fdf_info->z_maxvalue * (0xe80c0c/0xffffff);
	//calc_bresenham_x(x_start, y_start, y_finish, fdf_info);
	x_start = x_start*fdf_info->zoom;
	y_start = y_start*fdf_info->zoom;
	x_finish = x_finish*fdf_info->zoom;
	y_finish = y_finish*fdf_info->zoom;
	printf("prev : (y_start: %d , x_start: %d) (y_finish: %d , x_finish: %d,  color: %d)\n", y_start, x_start, y_finish, x_finish, fdf_info->color);
	degrees(&x_start, &y_start, z_start);
	degrees(&x_finish, &y_finish, z_finish);
	printf("after : (y_start: %d , x_start: %d) (y_finish: %d , x_finish: %d,  color: %d)\n", y_start, x_start, y_finish, x_finish, fdf_info->color);
	
	int d = abs_i(2 * (y_finish - y_start));
	int dx = abs_i(x_finish - x_start);
	int e;
	int y;
	int x = 0;
	e = 0;
	y = 0; 
	while(x < dx)
	{
		e = e + d;
		if(e > dx)
		{
		 	y = y + 1;
			e = e - (2 * dx);
		}
		if(x_start < x_finish && y_start < y_finish)//x:+方向 y:+方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start + x + 300, y_start + y, fdf_info->color);
		else if(x_start > x_finish && y_start < y_finish)//x:-方向 y:+方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start - x + 300, y_start + y, fdf_info->color);
		else if(x_start > x_finish && y_start > y_finish)//x:-方向 y:-方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start - x + 300, y_start - y, fdf_info->color);
		else if(x_start < x_finish && y_start > y_finish)//x:+方向 y:-方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start + x + 300, y_start - y, fdf_info->color);
		x++;
	}
}

void draw(t_fdf *fdf_info)
{
	int x;
	int y;
	int i = 0;

	y = 0;
	int median = (fdf_info->z_maxvalue - fdf_info->z_minvalue) / 2;
	if(fdf_info->z_maxvalue - median != 0){
		fdf_info->plus_color = (0xff0000 - 0x008000) / fdf_info->z_maxvalue - median;
	}
	else
		fdf_info->plus_color = 0;
	if(median - fdf_info->z_minvalue != 0)
		fdf_info->minus_color = (0x008000 - 0x0000ff) / -(median - fdf_info->z_minvalue);
	else
		fdf_info->minus_color = 0;
	printf("z_maxvalue = %d, z_maxvalue = %d, plus_color = %d, minus_color = %d \n", fdf_info->z_maxvalue, fdf_info->z_minvalue, fdf_info->plus_color,fdf_info->minus_color);
	while(y < fdf_info->height)
	{
		x = 0;
		while(x < fdf_info->width)
		{
			if(x < fdf_info->width - 1)
			{
				printf("= = = = = = = = = (%d : %d)  = = = = = = = = = = = =\n", y, x);
				bresenham(x, y, x+1, y, fdf_info);
			}
			if(y < fdf_info->height - 1)
				bresenham(x, y, x, y + 1, fdf_info);
			x++;
		}
		y++;
	}
}