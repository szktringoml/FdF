/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:36:13 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/16 13:36:15 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	routation_x(t_fdf *fdf_info, int *x, int *y, int *z)
{
	float	theta;

	theta = fdf_info->x_routation_theta;
	*x = (1 * *x);
	if (theta == 0)
		return ;
	else
	{
		*y = (cos(theta) * *y) + (-sin(theta) * *z);
		*z = (sin(theta) * *y) + (cos(theta) * *z);
	}
}

void	routation_y(t_fdf *fdf_info, int *x, int *y, int *z)
{
	float	theta;

	theta = fdf_info->y_routation_theta;
	if (theta == 0)
		return ;
	else
	{
		*x = (cos(theta) * *x) + (sin(theta) * *z);
		*y = (1 * *y);
		*z = (-sin(theta) * *x) + (cos(theta) * *z);
	}
}

void	routation_z(t_fdf *fdf_info, int *x, int *y, int *z)
{
	float	theta;

	theta = fdf_info->z_routation_theta;
	if (theta == 0)
		return ;
	else
	{
		*x = (cos(theta) * *x) + (-sin(theta) * *y);
		*y = (sin(theta) * *x) + (cos(theta) * *y);
		*z = (1 * *z);
	}
}
