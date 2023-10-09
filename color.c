/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:03 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 20:21:12 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_min_max_z(t_fdf *fdf_info, int *minz, int *maxz)
{
    if(fdf_info->coordinate->z_start < fdf_info->coordinate->z_finish)
    {
        *minz = fdf_info->coordinate->z_start;
        *maxz = fdf_info->coordinate->z_finish;
    }
    else if (fdf_info->coordinate->z_start > fdf_info->coordinate->z_finish)
    {
        *minz = fdf_info->coordinate->z_finish;
        *maxz = fdf_info->coordinate->z_start;
    }
}

void	bresenham_color(t_fdf *fdf_info, int dx, int d)
{
	int	e;
	int	y;
	int	color;
    d = 2 * (maxz - minz) * x;

	color = 0;
	e = 0;
	y = 0;
	while (color < d)
	{
		e = e + d;
		if (e > dx)
		{
			y = y + 1;
			e = e - (2 * dx);
		}
		color++;
	}
}

int get_z(t_fdf *fdf_info, int *z, int dx, int x)
{
    if(fdf_info->coordinate->z_start == fdf_info->coordinate->z_finish)
        *z = fdf_info->coordinate->z_start;
	else   
    {
        int minz;
        int maxz;
        get_min_max_z(fdf_info, &minz, &maxz);
        
        
        *z = minz + ((maxz-maxz/dx) * x);
    }
}

void	get_color_by_z_value(t_fdf *fdf_info, int dx, int x)
{
    int z;
    z = get_z(fdf_info, &z, dx, x);
}