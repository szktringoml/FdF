#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a<0) ? -a : a)
float mode(float i)
{
	return (i < 0) ? -i : i;
}

void bresenham(int x_start, int x_finish, float y_start, float y_finish, t_fdf *form_info)
{
	float x_step;
	float y_step;
	int max;
	x_step = x1 - x;
	y_step = y1 - y;

	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(form_info->mlx_ptr, form_info->win_ptr, x, y, 0xffffff);
		x += x_step;
		y += y_step;
	}
}


void draw(t_fdf *fdf_info)
{
	size_t x;
	size_t y;

	x = 1;
	y = 1;
	while(y <= fdf_info->height)
	{
		while(x <= fdf_info->width)
		{
			bresenham(x, x + 1, y, y, fdf_info);
			bresenham(x, x, y, y - 1, fdf_info);
			x++;
		}
		y++;
	}
}