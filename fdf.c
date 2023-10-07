#include "fdf.h"
size_t get_fdfheight(char *filename)
{
	int fd;
	size_t height;
	char *line;
	height = 0;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	else
	{
		line = get_next_line(fd);
		if(line)
			height++;
		while(line)
		{
			free(line);
			line = get_next_line(fd);
			height++;
		}
	}
	close(fd);
	return height - 1;
}

void	split_free(char **str, size_t sec)
{
	while (str[sec])
	{
		free(str[sec]);
		sec--;
	}
	free(str);
}

size_t get_fdfwidth(char *filename)
{
	int fd;
	size_t width;
	char *line;
	char **row_values;
	size_t i;
	
	width = 0;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	else
	{
		line = get_next_line(fd);
		row_values = ft_split(line, ' ');
		while(row_values[width])
			width++;
	}
	i = width;
	
	//free(line);
	//split_free(row_values, width-1);
	//while(row_values[--i] && i >= 0)
	 	//free(row_values[i]);
	 //free(row_values);
	return width;
}

int **get_fdfmap(int **z_values, char *filename, size_t width, size_t height)
{
	int fd;
	char **sp_row;
	int *row_values;
	size_t i;
	size_t j;
	char *row;
	j = 0;	
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	while(j < height)
	{
		i = 0;
		row = get_next_line(fd);
		//printf("---------%s---------\n", row);
		sp_row = ft_split(row, ' ');
		free(row);
		row_values = malloc(sizeof(int) * width);
		while(i < width)
		{
			row_values[i] = ft_atoi(sp_row[i]);
			i++;
		}
		z_values[j] = row_values;

		j++;
	}
	
	// while(sp_row[--width])
	// 	free(sp_row[width]);
	// free(sp_row);
	return z_values;
}



// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q fdf");
// }

// void z_values_conf(size_t fdfheight, size_t fdfwidth, int **z_values)
// {
// 	size_t height = 0;
// 	size_t width = 0;
// 	while(height < fdfheight)
// 	{
// 		width = 0;
// 		while(width < fdfheight)
// 		{
// 			printf("% i ", z_values[height][width]);
// 			width++;
// 		}
// 		printf("\n");
// 		height++;
// 	}
// }

void read_fdf(t_fdf **fdf_info, char *filename)
{
	(*fdf_info)->height = get_fdfheight(filename);
	(*fdf_info)->width = get_fdfwidth(filename);
	printf("height = %zu\n", (*fdf_info)->height);
	printf("width = %zu\n", (*fdf_info)->width);
	(*fdf_info)->z_values = malloc(sizeof(int*) * (*fdf_info)->height);
	(*fdf_info)->z_values = get_fdfmap((*fdf_info)->z_values, filename, (*fdf_info)->width, (*fdf_info)->height);
}

int deal_key(int key, void *data)
{
	(void)data;
	printf("%d", key);
	return 0;
}

int close_window(t_fdf *fdf_info)
{
	mlx_destroy_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
    exit(SUCCESS_EXIT);
    return (0);
}

void error_handler(char *filename)
{
	if(ft_strlen(filename) == 0)
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}
	if(!ft_isverify_file_extension(filename, ".fdf"))
	{
		write(2, NOT_FDF_FILE, NOT_FDF_FILE_CC);
		exit(BAD_EXIT);
	}
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		t_fdf *fdf_info;
		fdf_info = (t_fdf*)malloc(sizeof(t_fdf));
		error_handler(argv[1]);
		read_fdf(&fdf_info, argv[1]);
		fdf_info->zoom = 30;
		fdf_info->mlx_ptr = mlx_init();
		fdf_info->win_ptr = mlx_new_window(fdf_info->mlx_ptr, WIDTH, HEIGHT, "FDF");
		fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
		fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr, &fdf_info->bit_per_pixel, &fdf_info->size_line, &fdf_info->endian);
		draw(fdf_info);
		mlx_key_hook(fdf_info->win_ptr, deal_key, NULL);
		mlx_put_image_to_window(fdf_info->mlx_ptr, fdf_info->win_ptr, fdf_info->img_ptr, 0, 0);
		mlx_hook(fdf_info->win_ptr, 17, 1L << 17, close_window, fdf_info);
		mlx_loop(fdf_info->mlx_ptr);	
	}
	else
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}

}
