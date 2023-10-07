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

#define FDF_FILE_PATH "test_maps/42.fdf"
//gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
#define WIDTH 700
#define HEIGHT 700

#define BAD_EXIT 1
#define SUCCESS_EXIT 0
#define NON_FILENAME_ARGUMENT "Usage: ./fdf \"<.fdf file>\"\n"
#define NON_FILENAME_ARGUMENT_CC 27

#define NOT_FDF_FILE "Please specify .fdf file\n"
#define NOT_FDF_FILE_CC 25

#define COULD_NOT_OPEN_FILE "This file could not be opened. Please double check the path and name.\n"
#define COULD_NOT_OPEN_FILE_CC 70
// #ifndef FDF_FILE_PATH
//  # define FDF_FILE_PATH "test_maps/pylone.fdf"
// #endif
typedef struct s_fdf{
	size_t height;
	size_t width;
	size_t zoom;
	int color;
	int z_maxvalue;
	int **z_values;
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int  img_width;
	int img_height;
	char *data_addr;
	int size_line;
	int bit_per_pixel;
	int endian;

}			t_fdf;

void bresenham_x(int x_start, int y_start, int y_finish, t_fdf *fdf_info);
//void bresenham_x(int x_start, int y_start, int x_finish, int y_finish, t_fdf *fdf_info);
//void bresenham_y(int x_start,int y_start, int x_finish, int y_finish, t_fdf *fdf_info);

void draw(t_fdf *fdf_info);

#endif
