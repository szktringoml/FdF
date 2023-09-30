#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "minilibx_macos/mlx.h"

//gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

#ifndef FDF_FILE_PATH
 # define FDF_FILE_PATH "test_maps/10-2.fdf"
#endif
typedef struct s_fdf{
	size_t height;
	size_t width;
	size_t zoom;
	int **z_values;
	void *mlx_ptr;
	void *win_ptr;

}			t_fdf;

void bresenham(float x, float y, float x1, float y1, t_fdf *data);

void draw(t_fdf *fdf_info);

#endif
