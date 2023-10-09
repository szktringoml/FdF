/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:03 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 20:03:37 by kousuzuk         ###   ########.fr       */
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
void	get_color_by_z_value(t_fdf *fdf_info, int dx, int x)
{
    int z;
    if(fdf_info->coordinate->z_start == fdf_info->coordinate->z_finish)
        z = fdf_info->coordinate->z_start;
	else   
    {
        int minz;
        int maxz;
        get_min_max_z(fdf_info, &minz, &maxz);

        
        z = minz + ((maxz-maxz/dx) * x);



    }
}