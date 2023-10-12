/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:03 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/11 18:05:13 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define BITMASK 0x0000ff

//rgb_stepを16進数にして返す
int calc_rgb_hexa(t_fdf *fdf_info)
{
    int hexa;
    int r_start = (fdf_info->color_info->color >> 16)&BITMASK;
    int g_start= (fdf_info->color_info->color >> 8)&BITMASK;
    int b_start= (fdf_info->color_info->color)&BITMASK;
    // printf("[%d] + %d = %d\n", r_start, fdf_info->color_info->red_progress->step, r_start + fdf_info->color_info->red_progress->step);
    // printf("[%d] + %d = %d\n", g_start, fdf_info->color_info->green_progress->step, g_start + fdf_info->color_info->green_progress->step);
    // printf("[%d] + %d = %d\n", b_start, fdf_info->color_info->blue_progress->step, b_start + fdf_info->color_info->blue_progress->step);
    hexa = 0;
    hexa = ((r_start + fdf_info->color_info->red_progress->step) << 16);
    // printf("apply hexa red = %x\n", hexa);
    hexa = hexa + ((g_start + fdf_info->color_info->green_progress->step) << 8);
    // printf("apply hexa green = %x\n", hexa);
    hexa = hexa + b_start + fdf_info->color_info->blue_progress->step;
    // printf("apply hexa blue = %x\n", hexa);
    return hexa;
}

int bresenham_color_red(t_rgb_color_red *red_progress, int x, int zoom)
{   
    while(red_progress->xi < x)
    {
        red_progress->bresenham_e = red_progress->bresenham_e + red_progress->delta_color;
        if(red_progress->bresenham_e > zoom)
        {
            red_progress->diff = red_progress->diff + 1;
            red_progress->bresenham_e = red_progress->bresenham_e - (2 * zoom);
        }
        red_progress->xi++;
    }

    return red_progress->diff;
}

int bresenham_color_green(t_rgb_color_green *green_progress, int x, int zoom)
{   
    while(green_progress->xi < x)
    {
        green_progress->bresenham_e = green_progress->bresenham_e + green_progress->delta_color;
        if(green_progress->bresenham_e > zoom)
        {
            green_progress->diff = green_progress->diff + 1;
            green_progress->bresenham_e = green_progress->bresenham_e - (2 * zoom);
        }
        green_progress->xi++;
    }

    return green_progress->diff;
}

int bresenham_color_blue(t_rgb_color_blue *blue_progress, int x, int zoom)
{   
    while(blue_progress->xi < x)
    {
        blue_progress->bresenham_e = blue_progress->bresenham_e + blue_progress->delta_color;
        if(blue_progress->bresenham_e > zoom)
        {
            blue_progress->diff = blue_progress->diff + 1;
            blue_progress->bresenham_e = blue_progress->bresenham_e - (2 * zoom);
        }
        blue_progress->xi++;
    }

    return blue_progress->diff;
}


void get_min_max_z(t_fdf *fdf_info, int *minz, int *maxz)
{
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

void get_color_min_max_in_this_line(t_fdf *fdf_info, int z, int *want_color)
{
    int green = 0x00ff00;
    if(z > 0)
    {
        *want_color = (255/fdf_info->z_max_abs) * z;
        *want_color = *want_color << 16;
    }
    else if(z < 0)
    {
        *want_color = (255/fdf_info->z_max_abs) * (fdf_info->z_max_abs - z);
        *want_color = *want_color << 8;
    }
    else
        *want_color = green;
}

//xのときcolorにどれくらい足せば良いか知りたい
void    get_each_rgbcolor_step(t_fdf *fdf_info, int x)
{
    int zoom = fdf_info->zoom;

    
    if(fdf_info->color_info->red_progress->color_sf_diff/zoom == 0)
    {
        fdf_info->color_info->red_progress->delta_color = ft_abs_i(2 * (fdf_info->color_info->finish_color >> 16)&BITMASK -  (fdf_info->color_info->start_color >> 16)&BITMASK);
        fdf_info->color_info->red_progress->step = bresenham_color_red(fdf_info->color_info->red_progress, x, fdf_info->zoom);
    }
    else
        fdf_info->color_info->red_progress->step = (fdf_info->color_info->green_progress->color_sf_diff/zoom) * x;
    if(fdf_info->color_info->green_progress->color_sf_diff/zoom == 0)
    {
        fdf_info->color_info->red_progress->delta_color = ft_abs_i(2 * ((fdf_info->color_info->finish_color >> 8)&BITMASK - (fdf_info->color_info->start_color >> 8)&BITMASK));
        fdf_info->color_info->green_progress->step = bresenham_color_green(fdf_info->color_info->green_progress, x, fdf_info->zoom);
    }
    else{
        fdf_info->color_info->green_progress->step = (fdf_info->color_info->green_progress->color_sf_diff/zoom) * x;
    } 
    if((fdf_info->color_info->blue_progress->color_sf_diff)/zoom == 0)
        fdf_info->color_info->blue_progress->step = bresenham_color_blue(fdf_info->color_info->blue_progress, x, fdf_info->zoom);
    else{
        fdf_info->color_info->blue_progress->step = ((fdf_info->color_info->blue_progress->color_sf_diff)/zoom) * x;
    } 
}


void get_start_finish_color_of_each_point(t_fdf *fdf_info)
{
    int zoom;
    zoom = fdf_info->zoom;
     if(fdf_info->coordinate->decreace_flag == 0)
    {
        fdf_info->color_info->start_color = fdf_info->color_info->color_min;
        fdf_info->color_info->finish_color = fdf_info->color_info->color_max;
    }
    else
    {
        fdf_info->color_info->start_color = fdf_info->color_info->color_max;
        fdf_info->color_info->finish_color = fdf_info->color_info->color_min;
    }
    fdf_info->color_info->red_progress->f_temp = (fdf_info->color_info->finish_color >>16)&(BITMASK);//直接書き込んで演算すると負にならなかった
    fdf_info->color_info->red_progress->s_temp = (fdf_info->color_info->start_color >>16)&(BITMASK);
    fdf_info->color_info->red_progress->color_sf_diff = fdf_info->color_info->red_progress->f_temp - fdf_info->color_info->red_progress->s_temp;
    fdf_info->color_info->red_progress->color_sf_diff_div_zoom = fdf_info->color_info->red_progress->color_sf_diff/zoom;
    printf("zoomで割ったが文字化けしてないか red %d\n",  fdf_info->color_info->red_progress->color_sf_diff_div_zoom);
    fdf_info->color_info->green_progress->f_temp = (fdf_info->color_info->finish_color >>8)&(BITMASK);//直接書き込んで演算すると負にならなかった
    fdf_info->color_info->green_progress->s_temp = (fdf_info->color_info->start_color >>8)&(BITMASK);
    fdf_info->color_info->green_progress->color_sf_diff = fdf_info->color_info->green_progress->f_temp - fdf_info->color_info->green_progress->s_temp;
    fdf_info->color_info->green_progress->color_sf_diff_div_zoom = fdf_info->color_info->green_progress->color_sf_diff/zoom;
    printf("zoomで割ったが文字化けしてないか green %d\n",  fdf_info->color_info->green_progress->color_sf_diff_div_zoom);

    fdf_info->color_info->blue_progress->f_temp = (fdf_info->color_info->finish_color)&(BITMASK);//直接書き込んで演算すると負にならなかった
    fdf_info->color_info->blue_progress->s_temp = (fdf_info->color_info->start_color)&(BITMASK);
    fdf_info->color_info->red_progress->color_sf_diff = fdf_info->color_info->red_progress->f_temp - fdf_info->color_info->blue_progress->s_temp;
    fdf_info->color_info->red_progress->color_sf_diff_div_zoom = fdf_info->color_info->red_progress->color_sf_diff/zoom;
    printf("zoomで割ったが文字化けしてないか blue %d\n",  fdf_info->color_info->blue_progress->color_sf_diff_div_zoom);

    printf("--------------------------------------------------------------------------");
}

void red_progress_init(t_rgb_color_red *red_progress)
{
    red_progress->step = 0;
    red_progress->delta_color = 0;
    red_progress->diff = 0;
    red_progress->xi = 0;
    red_progress->bresenham_e = 0;
}

void green_progress_init(t_rgb_color_green *green_progress)
{
    green_progress->step = 0;
    green_progress->delta_color = 0;
    green_progress->diff = 0;
    green_progress->xi = 0;
    green_progress->bresenham_e = 0;
}

void blue_progress_init(t_rgb_color_blue *blue_progress)
{
    blue_progress->step = 0;
    blue_progress->delta_color = 0;
    blue_progress->diff = 0;
    blue_progress->xi = 0;
    blue_progress->bresenham_e = 0;
}
void color_properties_init(t_fdf *fdf_info)
{

    fdf_info->color_info->color = 0;
	fdf_info->color_info->color_max = 0;
	fdf_info->color_info->color_min = 0;
	fdf_info->color_info->start_color = 0;
	fdf_info->color_info->finish_color = 0;
    fdf_info->color_info->red_progress = (t_rgb_color_red *)malloc(sizeof(t_rgb_color_red));
    fdf_info->color_info->green_progress = (t_rgb_color_green *)malloc(sizeof(t_rgb_color_green));
    fdf_info->color_info->blue_progress = (t_rgb_color_blue *)malloc(sizeof(t_rgb_color_blue));
    red_progress_init(fdf_info->color_info->red_progress);
    green_progress_init(fdf_info->color_info->green_progress);
    blue_progress_init(fdf_info->color_info->blue_progress);


}

void	get_color_range_in_this_line(t_fdf *fdf_info)
{
    int minz = 0;
    int maxz = 0;
    
    color_properties_init(fdf_info);
    get_min_max_z(fdf_info, &minz, &maxz);
    get_color_min_max_in_this_line(fdf_info, minz, &fdf_info->color_info->color_min);
    get_color_min_max_in_this_line(fdf_info, maxz, &fdf_info->color_info->color_max);
    get_start_finish_color_of_each_point(fdf_info);
}


