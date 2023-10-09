/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:02:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 17:22:51 by kousuzuk         ###   ########.fr       */
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

typedef struct s_coordinate
{
	int				x_start;
	int				y_start;
	int				x_finish;
	int				y_finish;

}					t_coordinate;

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
	int				color;
	size_t			zoom;
	size_t			shift_x;
	size_t			shift_y;
}					t_fdf;

size_t				get_fdfheight(char *filename);

size_t				get_fdfwidth(char *filename);

int					**get_fdfmap(int **z_values, char *filename, size_t width,
						size_t height);

void				get_fdfmap_generate_array(int fd, int **z_values,
						size_t width, size_t height);

void				read_fdf(t_fdf **fdf_info, char *filename);

void				fdf_info_init(t_fdf *fdf_info);

int					deal_key(int key, t_fdf *fdf_info);

int					close_window(t_fdf *fdf_info);

void				error_filename(char *filename);

void				error_fd(int fd);

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

#endif
