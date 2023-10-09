/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:00:13 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 15:45:34 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	coordinate_init(t_coordinate *coordinate)
{
	coordinate->x_start = 0;
	coordinate->y_start = 0;
	coordinate->x_finish = 0;
	coordinate->y_finish = 0;
}

void	coordinate_store_x(t_coordinate *coordinate, int x, int y)
{
	coordinate->x_start = x;
	coordinate->y_start = y;
	coordinate->x_finish = x + 1;
	coordinate->y_finish = y;
}

void	coordinate_store_y(t_coordinate *coordinate, int x, int y)
{
	coordinate->x_start = x;
	coordinate->y_start = y;
	coordinate->x_finish = x;
	coordinate->y_finish = y + 1;
}
