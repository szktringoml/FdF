/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:33:18 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 17:43:12 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_fd(int fd)
{
	if (fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
}

void    error_read(int read_status)
{
    if (read_status <= 0)
	{
		write(2, EMPTY_FDF_FILE, EMPTY_FDF_FILE_CC);
		exit(BAD_EXIT);
	}
}

void    error_malloc()
{
    write(2, MALLOC_FAIL, MALLOC_FAIL_CC);
	exit(BAD_EXIT);
}

void	error_filename(char *filename)
{
	if (ft_strlen(filename) == 0)
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}
	if (!ft_isverify_file_extension(filename, ".fdf"))
	{
		write(2, NOT_FDF_FILE, NOT_FDF_FILE_CC);
		exit(BAD_EXIT);
	}
}

void	error_fdf_format(int store_length, int width)
{
	if (store_length != width)
	{
		write(2, FDF_FILE_DEFFELENT_FORMAT, FDF_FILE_DEFFELENT_FORMAT_CC);
		exit(BAD_EXIT);
	}
}
