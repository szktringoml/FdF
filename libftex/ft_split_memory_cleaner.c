/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_memory_cleaner.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:28 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 17:58:30 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_memory_cleaner(size_t memory_len, char **array)
{
	size_t	i;

	i = 0;
	while (i < memory_len)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
