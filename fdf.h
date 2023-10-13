/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:02:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/13 13:27:48 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libftex/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

# define PLUS 24
# define MINUS 27

# define ALLOW_TOP 126
# define ALLOW_RIGHT 124
# define ALLOW_BOTTOM 125
# define ALLOW_LEFT 123

# define BAD_EXIT 1
# define SUCCESS_EXIT 0

# define NON_FILENAME_ARGUMENT "Usage: ./fdf \"<.fdf file>\"\n"
# define NON_FILENAME_ARGUMENT_CC 27

# define NOT_FDF_FILE "Please specify .fdf file\n"
# define NOT_FDF_FILE_CC 25

# define COULD_NOT_OPEN_FILE "This file could not be opened. \
Please double check the path and name.\n"
# define COULD_NOT_OPEN_FILE_CC 70

# define FDF_FILE_DEFFELENT_FORMAT "fdf file is invalid. \
Please load a file with the correct format.\n"
# define FDF_FILE_DEFFELENT_FORMAT_CC 65

# define EMPTY_FDF_FILE "The specified file was empty.\n"
# define EMPTY_FDF_FILE_CC 30

# define MALLOC_FAIL "malloc fail\n"
# define MALLOC_FAIL_CC 22

typedef struct s_coordinate
{
	int				x_start;
	int				y_start;
	int 			z_start;
	int				x_finish;
	int				y_finish;
	int				z_finish;
	int 			decreace_flag;
}					t_coordinate;

typedef struct s_rgb_color_red
{
	int s_temp;
    int f_temp;
	int				color_sf_diff;
	int				color_sf_diff_div_zoom;\

	int				step;
	int 			delta_color;
	int 			xi;
	int 			diff;
	int 			bresenham_e;
}			t_rgb_color_red;

typedef struct s_rgb_color_green
{
	int s_temp;
    int f_temp;
	int				color_sf_diff;
	int				color_sf_diff_div_zoom;

	int				step;
	int 			delta_color;
	int 			xi;
	int 			diff;
	int 			bresenham_e;
}			t_rgb_color_green;

typedef struct s_rgb_color_blue
{
	int s_temp;
    int f_temp;
	int				color_sf_diff;
	int				color_sf_diff_div_zoom;

	int				step;
	int 			delta_color;
	int 			xi;
	int 			diff;
	int 			bresenham_e;
}			t_rgb_color_blue;


typedef struct s_color
{
	int					color;
	int 				color_max;
	int 				color_min;
	int 				start_color;
	int 				finish_color;
	int					put_pixel_cnt_in_this_line;
	t_rgb_color_red		*red_progress;
	t_rgb_color_green	*green_progress;
	t_rgb_color_blue	*blue_progress;

}					t_color;



typedef struct s_fdf
{
	size_t			height;
	size_t			width;
	int				**z_values;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				size_line;
	int				bit_per_pixel;
	int				endian;
	t_coordinate	*coordinate;
	t_color 		*color_info;
	int				z_max_abs;
	size_t			zoom;
	size_t 			shift_x;
	size_t 		shift_y;
}					t_fdf;

size_t				get_fdfheight(char *filename);

size_t				get_fdfwidth(char *filename);

int					**get_fdfmap(t_fdf *fdf_info, int **z_values, char *filename, size_t width,
						size_t height);

void				get_fdfmap_generate_array(t_fdf *fdf_info, int fd, int **z_values,
						size_t width, size_t height);

void				read_fdf(t_fdf **fdf_info, char *filename);

void				fdf_info_init(t_fdf *fdf_info);

int					deal_key(int key, t_fdf *fdf_info);

int					close_window(t_fdf *fdf_info);

void				error_filename(char *filename);

void				error_fd(int fd);

void				error_read(int read_status);

void				error_malloc(void);

void				error_fdf_format(int i, int width);

void				coordinate_init(t_coordinate *coordinate);

void				coordinate_store_x(t_coordinate *coordinate, int x, int y);

void				coordinate_store_y(t_coordinate *coordinate, int x, int y);

void				apply_degrees(int *x, int *y, int z);

void				apply_properties_to_point(t_fdf *fdf_info);

void				apply_zoom_to_one_line_points(t_fdf *fdf_info);

void				apply_properties_to_one_line_points(t_fdf *fdf_info);

void				bresenham_algo(t_fdf *fdf_info, int dx, int d);

void				put_pixel_hub(t_fdf *fdf_info, int x, int y);

void				draw(t_fdf *fdf_info);

void				shift_map(t_fdf *fdf_info, int key);

void				zoom_map(t_fdf *fdf_info, int key);

void get_min_max_z(t_fdf *fdf_info, int *minz, int *maxz);

void get_color_min_max_in_this_line(t_fdf *fdf_info, int minz, int *want_color);

void 	get_color_range_in_this_line(t_fdf *fdf_info);

void    get_each_rgbcolor_step(t_fdf *fdf_info, int x);

int calc_rgb_hexa(t_fdf *fdf_info);

#endif
