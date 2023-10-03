#include "fdf.h"

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

void degrees(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * cos(0.8) - z;
}

void calc_bresenham_x(int x_start, int y_start, int y_finish, t_fdf *fdf_info)
{
	int e;
	int y;
	int x;
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
		mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x + (x_start * fdf_info->zoom), y, fdf_info->color);
		x++;
	}
}

void calc_bresenham_y(int y_start, int x_start, int x_finish, t_fdf *fdf_info)
{
	int e;
	int y;
	int x;
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
	fdf_info->color = (z_start) ? 0xe80c0c : 0xffffff;

	//calc_bresenham_x(x_start, y_start, y_finish, fdf_info);
	x_start = x_start*fdf_info->zoom;
	y_start = y_start*fdf_info->zoom;
	x_finish = x_finish*fdf_info->zoom;
	y_finish = y_finish*fdf_info->zoom;
	printf("prev : (x_start: %d , y_start: %d) (x_finish: %d , y_finish: %d)\n", x_start, y_start, x_finish, y_finish);
	degrees(&x_start, &y_start, z_start);
	degrees(&x_finish, &y_finish, z_finish);
	printf("after : (x_start: %d , y_start: %d) (x_finish: %d , y_finish: %d)\n", x_start, y_start, x_finish, y_finish);
	
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
			
			if(y_start < y_finish)
			 	y = y + 1;
			else
				y = y - 1;
			e = e - (2 * dx);
		}
		if(x_start < x_finish && y_start < y_finish)//x:+方向 y:+方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start + x + 300, y_start + y, fdf_info->color);
		else if(x_start > x_finish && y_start < y_finish)//x:-方向 y:+方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start - x + 300, y_start + y, fdf_info->color);
		else if(x_start < x_finish && y_start > y_finish)//x:+方向 y:-方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start + x + 300, y_start - y, fdf_info->color);
		else if(x_start > x_finish && y_start > y_finish)//x:-方向 y:-方向
			mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x_start - x + 300, y_start - y, fdf_info->color);
		x++;
	}
}


void bresenham_y(int x_start,int y_start, int x_finish, int y_finish, t_fdf *fdf_info)
{
	int z_start;
	int z_finish;
	//dx *= fdf_info->zoom;
	z_start = fdf_info->z_values[y_start][x_start];
	z_finish = fdf_info->z_values[y_finish][x_finish];
	fdf_info->color = (z_start) ? 0xe80c0c : 0xffffff;
	printf("zs = %d, zf = %d\n", z_start, z_finish);
	//calc_bresenham_x(x_start, y_start, y_finish, fdf_info);
	x_start = x_start*fdf_info->zoom;
	y_start = y_start*fdf_info->zoom;
	x_finish = x_finish*fdf_info->zoom;
	y_finish = y_finish*fdf_info->zoom;
	degrees(&x_start, &y_start, z_start);
	degrees(&x_finish, &y_finish, z_finish);

	int d = 2 * (x_finish - x_start);
	int dx = (y_finish - y_start);
	printf("d = %d    dy = %d\n", d, dx);
	int e = 0;
	int y = y_start;
	int x = 0; 
	while(x < abs(dx))
	{
		e = e + d;
		if(e > abs(dx))
		{
			y = y + 1;
			e = e - (2 * abs(dx));
		}
		printf("x:%d y:%d\n", x + 300, y+y_start);
		mlx_pixel_put(fdf_info->mlx_ptr, fdf_info->win_ptr, x+ x_start + 300, y , fdf_info->color);
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
				printf("= = = = = = = = = (%d : %d)  = = = = = = = = = = = =\n", y, x);
				bresenham(x, y, x+1, y, fdf_info);
			}
			if(y < fdf_info->height - 1)
				bresenham(x, y, x, y + 1, fdf_info);
			x++;
		}
		//printf("\n");
		y++;
	}
}