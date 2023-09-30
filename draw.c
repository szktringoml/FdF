#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a<0) ? -a : a)
float mode(float i)
{
	return (i < 0) ? -i : i;
}

// void bresenham(float x, float x1, float y, float y1, t_fdf *form_info)
// {
// 	float x_step;
// 	float y_step;
// 	int max;
// 	x_step = x1 - x;
// 	y_step = y1 - y;

// 	max = MAX(MOD(x_step), MOD(y_step));
// 	x_step /= max;
// 	y_step /= max;
// 	while((int)(x - x1) || (int)(y - y1))
// 	{
// 		mlx_pixel_put(form_info->mlx_ptr, form_info->win_ptr, x, y, 0xffffff);
// 		x += x_step;
// 		y += y_step;
// 	}
// }

//dxは結局１になるので省略してfdf_info->zoomで良い
//第一引数は(引く方向＿線の始まり).第二引数は傾きを得ためのもの
void bresenham_x(int x_start, int y_start, int y_finish, t_fdf *fdf_info)
{
	int e;
	int y;
	int x;
	int z;
	//dx *= fdf_info->zoom;
	z = fdf_info->z_values[y_start][x_start];
	if(z)
		fdf_info->color = 0xe80c0c;
	else
		fdf_info->color = 0xffffff;
	y_start *= fdf_info->zoom;
	y_finish *= fdf_info->zoom;
	printf("x   z = %i\n", z);
	e = 0;
	y = y_start;
	x = 0;
	while(x < fdf_info->zoom)
	{
		e = e + (2 * (y_finish - y_start));
		if(e > fdf_info->zoom)
		{
			y = y + 1;
			e = e - (2 * fdf_info->zoom);
		}
		mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x + (x_start * fdf_info->zoom), y, 0xffffff);
		x++;
	}
}

void bresenham_y(int y_start, int x_start, int x_finish, t_fdf *fdf_info)
{
	int e;
	int x;
	int y;
	int z;
	//dx *= fdf_info->zoom;
	z = fdf_info->z_values[y_start][x_start];
	if(z)
		fdf_info->color = 0xe80c0c;
	else
		fdf_info->color = 0xffffff;
	x_start *= fdf_info->zoom;
	x_finish *= fdf_info->zoom;
	printf("y   z = %i\n", z);
	e = 0;
	x = x_start;
	y = 0;
	while(y < fdf_info->zoom)
	{
		e = e + (2 * (x_finish - x_start));
		if(e > fdf_info->zoom)
		{
			x = x + 1;
			e = e - (2 * fdf_info->zoom);
		}
		mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x , y + (y_start * fdf_info->zoom), fdf_info->color);
		y++;
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
			bresenham_x(x, y, y, fdf_info);
			bresenham_y(y, x, x, fdf_info);
			x++;
		}
		y++;
	}
	while(i<x)
		bresenham_x(i++, y, y, fdf_info);
	i=0;
	while(i < y)
		bresenham_y(i++, x, x, fdf_info);

}