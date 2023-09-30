#include "fdf.h"

size_t get_fdfheight(void)
{
	int fd;
	size_t height;
	char *line;
	height = 0;
	fd = open(FDF_FILE_PATH, O_RDONLY);
	if(fd == -1)
	{
		printf("fd = -1\n");
		exit(0);
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

size_t get_fdfwidth(void)
{
	int fd;
	size_t width;
	char *line;
	char **row_values;
	size_t i;
	
	width = 0;
	fd = open(FDF_FILE_PATH, O_RDONLY);
	if(fd == -1)
	{
		printf("fd = -1\n");
		exit(0);
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
	return width-1;
}

int **get_fdfmap(int **z_values, size_t width, size_t height)
{
	int fd;
	char **sp_row;
	int *row_values;
	size_t i;
	size_t j;
	char *row;
	j = 0;	
	fd = open(FDF_FILE_PATH, O_RDONLY);
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

void z_values_conf(size_t fdfheight, size_t fdfwidth, int **z_values)
{
	size_t height = 0;
	size_t width = 0;
	while(height < fdfheight)
	{
		width = 0;
		while(width < fdfheight)
		{
			printf("% i ", z_values[height][width]);
			width++;
		}
		printf("\n");
		height++;
	}
}

void read_fdf(t_fdf **fdf_info)
{
	(*fdf_info)->height = get_fdfheight();
	(*fdf_info)->width = get_fdfwidth();
	(*fdf_info)->zoom = 20;
	printf("height = %zu\n", (*fdf_info)->height);
	printf("width = %zu\n", (*fdf_info)->width);
	(*fdf_info)->z_values = malloc(sizeof(int*) * (*fdf_info)->height);
	(*fdf_info)->z_values = get_fdfmap((*fdf_info)->z_values, (*fdf_info)->width, (*fdf_info)->height);\
}

int deal_key(int key, void *data)
{
	printf("%d", key);
	return 0;
}

int main(int argc, char **argv)
{
	t_fdf *fdf_info;
	fdf_info = (t_fdf*)malloc(sizeof(t_fdf));
	read_fdf(&fdf_info);
	fdf_info->zoom = 20;
	//z_values_conf(fdf_info->height, fdf_info->width, fdf_info->z_values);
	fdf_info->mlx_ptr = mlx_init();
	fdf_info->win_ptr = mlx_new_window(fdf_info->mlx_ptr, 1000, 1000, "FDF");

	draw(fdf_info);
	mlx_key_hook(fdf_info->win_ptr, deal_key, NULL);
	mlx_loop(fdf_info->mlx_ptr);

}
