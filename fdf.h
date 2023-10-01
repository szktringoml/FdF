#ifndef FDF_H
# define FDF_H

#include "libftex/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include "minilibx_macos/mlx.h"

//gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

#ifndef FDF_FILE_PATH
 # define FDF_FILE_PATH "test_maps/42.fdf"
#endif
typedef struct s_fdf{
	size_t height;
	size_t width;
	size_t zoom;
	int color;
	int **z_values;
	void *mlx_ptr;
	void *win_ptr;

}			t_fdf;


//void bresenham_x(int x_start, int y_start, int y_finish, t_fdf *fdf_info);
void bresenham_x(int x_start, int y_start, int x_finish, int y_finish, t_fdf *fdf_info);
void bresenham_y(int y_start, int x_start, int x_finish, t_fdf *fdf_info);

void draw(t_fdf *fdf_info);

#endif
