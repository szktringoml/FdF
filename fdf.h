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

# define WIDTH 1000
# define HEIGHT 1000

# define BAD_EXIT 1
# define SUCCESS_EXIT 0
# define NON_FILENAME_ARGUMENT "Usage: ./fdf \"<.fdf file>\"\n"
# define NON_FILENAME_ARGUMENT_CC 27

# define NOT_FDF_FILE "Please specify .fdf file\n"
# define NOT_FDF_FILE_CC 25

# define COULD_NOT_OPEN_FILE "This file could not be opened. Please double check the path and name.\n"
# define COULD_NOT_OPEN_FILE_CC 70

typedef struct s_fdf
{
	size_t	height;
	size_t	width;
	int		**z_values;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data_addr;
	int		size_line;
	int		bit_per_pixel;
	int		endian;
	size_t	zoom;
	int		color;
	int		z_maxvalue;
	int		z_minvalue;

}			t_fdf;

size_t		get_fdfheight(char *filename);

void		split_free(char **str, size_t sec);

size_t		get_fdfwidth(char *filename);

int			**get_fdfmap(int **z_values, char *filename, size_t width,
				size_t height);

void		read_fdf(t_fdf **fdf_info, char *filename);

int			deal_key(int key, void *data);

int			close_window(t_fdf *fdf_info);

void		error_handler(char *filename);

void		bresenham_x(int x_start, int y_start, int y_finish,
				t_fdf *fdf_info);

void		draw(t_fdf *fdf_info);

#endif
