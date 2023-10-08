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

int **get_fdfmap(t_fdf *fdf_info, char *filename)
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
	while(j < fdf_info->height)
	{
		i = 0;
		row = get_next_line(fd);\
		sp_row = ft_split(row, ' ');
		free(row);
		row_values = malloc(sizeof(int) * fdf_info->width);
		while(i < fdf_info->width)
		{
			row_values[i] = ft_atoi(sp_row[i]);
			if(ft_abs_i(row_values[i]) > fdf_info->z_max_abs)
				fdf_info->z_max_abs = ft_abs_i(row_values[i]);
			i++;
		}
		fdf_info->z_values[j] = row_values;

		j++;
	}
	
	// while(sp_row[--width])
	// 	free(sp_row[width]);
	// free(sp_row);
	return fdf_info->z_values;
}