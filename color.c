/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:03 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/11 14:19:07 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define BITMASK 0x0000ff

int bresenham_color_red(t_fdf *fdf_info, int x)
{
    int i = 0;
    int diff = 0;
    int *e = &fdf_info->color_info->r_bresenham_e;
    int delta_color = ft_abs_i(2 * (fdf_info->color_info->finish_color >> 16)&BITMASK);
    while(i < x)
    {
        *e = *e + delta_color;
        if(*e > fdf_info->zoom)
        {
            diff = diff + 1;
            *e = *e - (2 * fdf_info->zoom);
        }
        i++;
    }

    return diff;
}
int bresenham_color_green(t_fdf *fdf_info, int x)
{
    int i = 0;
    int diff = 0;
    int e = fdf_info->color_info->g_bresenham_e;
    int delta_color = ft_abs_i(2 * ((fdf_info->color_info->finish_color >> 8)&BITMASK));
    while(i < x)
    {
        e = e + delta_color;
        if(e > fdf_info->zoom)
        {
            diff = diff + 1;
            e = e - (2 * fdf_info->zoom);
        }
        i++;
    }
    return diff;
}

int bresenham_color_blue(t_fdf *fdf_info)
{
    int i = 0;
    int diff = 0;
    int e = fdf_info->color_info->b_bresenham_e;
    int delta_color = ft_abs_i(2 * (fdf_info->color_info->finish_color)&BITMASK);
    while(i < 255)
    {
        e = e + delta_color;
        if(e > fdf_info->zoom)
        {
            diff = diff + 1;
            e = e - (2 * fdf_info->zoom);
            break;
        }
        i++;
    }
    return i;
}


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

//stepを計算したい、これをz_startのcolorに足すだけで良くなるように
//fdf_info->color_info->f_temp = (fdf_info->color_info->finish_color>>16)&(BITMASK);は直接書き込んで演算すると負にならなかったのでtempに入れている
void    get_each_rgbcolor_step(t_fdf *fdf_info, int x)
{
    if(fdf_info->coordinate->decreace_flag == -1)
    {
        fdf_info->color_info->color_step = 0;
        fdf_info->color_info->r_step = 0;
        fdf_info->color_info->g_step = 0;
        fdf_info->color_info->b_step = 0;
        printf("この線は緑\n");
    }
    else
    {   
        //step < zoomの状態になると浮動小数計算になるのでbresenhamを使う
        if(fdf_info->zoom)
        fdf_info->color_info->r_step = bresenham_color_red(fdf_info, x);
        
        fdf_info->color_info->g_step = bresenham_color_green(fdf_info, x);

        fdf_info->color_info->b_step = bresenham_color_blue(fdf_info, x);
    }
}


void get_start_finish_color_of_each_point(t_fdf *fdf_info)
{

     if(fdf_info->coordinate->decreace_flag == 0)
    {
        fdf_info->color_info->start_color = fdf_info->color_info->color_min;
        fdf_info->color_info->finish_color = fdf_info->color_info->color_max;
        fdf_info->color_info->color = fdf_info->color_info->color_min;
    }
    else
    {
        fdf_info->color_info->start_color = fdf_info->color_info->color_max;
        fdf_info->color_info->finish_color = fdf_info->color_info->color_min;
        fdf_info->color_info->color = fdf_info->color_info->color_max;
    }
}

void color_properties_init(t_fdf *fdf_info)
{
    fdf_info->color_info->color = 0;
	fdf_info->color_info->z_max_abs = 0;
	fdf_info->color_info->color_max = 0;
	fdf_info->color_info->color_min = 0;
	fdf_info->color_info->color_step = 0;
	fdf_info->color_info->start_color = 0;
	fdf_info->color_info->finish_color = 0;
	fdf_info->color_info->r_bresenham_e = 0;
	fdf_info->color_info->g_bresenham_e = 0;
	fdf_info->color_info->b_bresenham_e = 0;

}

void	get_color_range_in_this_line(t_fdf *fdf_info)
{
    int minz = 0;
    int maxz = 0;
    int color_min = 0;
    int color_max = 0;
    
    color_properties_init(fdf_info);
    get_min_max_z(fdf_info, &minz, &maxz);
    get_color_min_max_in_this_line(fdf_info, minz, &fdf_info->color_info->color_min);
    get_color_min_max_in_this_line(fdf_info, maxz, &fdf_info->color_info->color_max);
    if(color_min > color_max)
        write(2, "ありえないことが起きている\n", 14);
    //get_each_rgbcolor_step(fdf_info);
    get_start_finish_color_of_each_point(fdf_info);
}
