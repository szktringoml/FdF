/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 07:58:25 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/09/30 14:22:30 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

//size_t	ft_strlen(const char *s);
char	*ft_gnlstrchr(const char *s, int c);
//void	ft_bzero(void *s, size_t n);
char	*ft_gnlstrjoin(char *input, char *str);
//void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);
char	*ft_input_each_fd(int fd, char *input);
char	*ft_getline(char *input);
char	*ft_reshape(char *input);

#endif
