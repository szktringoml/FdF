/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:03 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/10 17:10:43 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_min_max_z(t_fdf *fdf_info, int *minz, int *maxz)
{
    //printf("zs = %d, zf = %d\n",fdf_info->coordinate->z_start , fdf_info->coordinate->z_finish);
    if(fdf_info->coordinate->z_start < fdf_info->coordinate->z_finish)
    {
        *minz = fdf_info->coordinate->z_start;
        *maxz = fdf_info->coordinate->z_finish;
        fdf_info->coordinate->decreace_flag = 0;
    }
    else if (fdf_info->coordinate->z_start > fdf_info->coordinate->z_finish)
    {
        *minz = fdf_info->coordinate->z_finish;
        *maxz = fdf_info->coordinate->z_start;
        fdf_info->coordinate->decreace_flag = 1;
    }
    else
    {
        *minz = fdf_info->coordinate->z_finish;
        *maxz = fdf_info->coordinate->z_start;
        fdf_info->coordinate->decreace_flag = -1;
    }
}

void get_color_min_max_in_this_line(t_fdf *fdf_info, int minz, int *want_color)
{
    int green = 0x00ff00;
    if(minz > 0)
    {
        *want_color = (255/fdf_info->color_info->z_max_abs) * minz;
        *want_color = *want_color << 16;
    }
    else if(minz < 0)
    {
        *want_color = (255/fdf_info->color_info->z_max_abs) * (fdf_info->color_info->z_max_abs - minz);
        *want_color = *want_color << 8;
    }
    else
        *want_color = green;
}

void    get_color_step(t_fdf *fdf_info)
{
    int r_diff;
    int g_diff;
    int b_diff;
    int color_step;
    if(fdf_info->coordinate->decreace_flag == -1)
    {
        fdf_info->color_info->color_step = 0;
        printf("この線は緑\n");
    }
    else
    {
        r_diff = (fdf_info->color_info->color_max  - fdf_info->color_info->color_min)/fdf_info->zoom;
        g_diff = ((fdf_info->color_info->color_max >> 8) - (fdf_info->color_info->color_min >> 8))/fdf_info->zoom;
        b_diff = ((fdf_info->color_info->color_max >> 16)  - (fdf_info->color_info->color_min >> 16))/fdf_info->zoom;
        color_step = b_diff;
        color_step = (color_step << 8) + g_diff;
        fdf_info->color_info->color_step = (color_step << 8) + r_diff;
        if(color_step == 0)
            write(2, "bresenham plz\n", 0);
    }
}

void	get_color_range_in_this_line(t_fdf *fdf_info)
{
    int minz = 0;
    int maxz = 0;
    int color_min = 0;
    int color_max = 0;
    
    get_min_max_z(fdf_info, &minz, &maxz);
    get_color_min_max_in_this_line(fdf_info, minz, &fdf_info->color_info->color_max);
    get_color_min_max_in_this_line(fdf_info, maxz, &fdf_info->color_info->color_max);
    if(color_min > color_max)
        write(2, "ありえないことが起きている\n", 14);
    get_color_step(fdf_info);
    if(fdf_info->coordinate->decreace_flag == 0)
        fdf_info->color_info->color = fdf_info->color_info->color_min;
    else
        fdf_info->color_info->color = fdf_info->color_info->color_max;
}
