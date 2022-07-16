/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:23:18 by mykman            #+#    #+#             */
/*   Updated: 2022/07/16 15:41:44 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// TO REMOVE
#include <stdio.h>

// read()
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
// malloc() / free()
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

// Main function
char	*get_next_line(int fd);

// Modified strjoin to free str1 if it has been malloc before
char	*ft_strjoin(char *str1, char *str2);
// Return the size of str
int		ft_strlen(char *str);
// Return the index value of c in str. Return -1 if c is not in str
int		ft_index(char *str, char c);
// Return NULL and free ptr
void	*ft_free(void *ptr);

#endif