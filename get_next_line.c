/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:26:54 by mykman            #+#    #+#             */
/*   Updated: 2022/07/16 16:30:02 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

int	ft_index(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	new = (char *)malloc(sizeof(char) * len);
	if (new)
	{
		i = 0;
		if (str1)
		{
			// if str1 exist, copy `str1` at the start of `new`
			while (str1[i])
			{
				new[i] = str1[i];
				i++;
			}
		}
		// copy `str2` after `str1` in `new`
		j = 0;
		while (str2[j])
		{
			new[i + j] = str2[j];
			j++;
		}
		new[i + j] = '\0';
	}
	// If str1 exist it means that it should be free'd
	// (Because it's the old saved => see use in get_next_line)
	if (str1)
		free(str1);
	return (new);
}

char	*ft_substr(char *str, int start, int end, int tofree)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (end - start + 1));
	if (new)
	{
		// Copy the part between start (included) and end (excluded) in new
		i = 0;
		while (start + i < end)
		{
			new[i] = str[start + i];
			i++;
		}
		new[i] = 0;
	}
	// If tofree is true, free the original string
	if (tofree)
		free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*saved;		// static string that keep the rest of the line
	char		*line;		// the line that's returned
	char		*buff;		// buffer for read() function
	int			ret;		// return value of read function

	// Verifications for the `fd` and for the BUFFER_SIZE
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Malloc the buffer
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);

	// Start ret at 1 to enter the loop the first time
	ret = 1;
	while (ret > 0 && ft_index(saved, '\n') < 0) // While (read someting && there is no '\n' in saved)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = 0;

		// join back to back in saved (old saved is free in ft_strjoin())
		saved = ft_strjoin(saved, buff);
		if (!saved)
			return (ft_free(buff));
	}
	// Don't need the buffer anymore => free
	free(buff);

	// If there is a '\n' in saved
	if (ft_index(saved, '\n') >= 0)
	{
		// substring of everything until '\n' (included)
		line = ft_substr(saved, 0, ft_index(saved, '\n') + 1, 0);
		// substring of everything from '\n' (excluded) to the end. Also free the old saved
		saved = ft_substr(saved, ft_index(saved, '\n') + 1, ft_strlen(saved), 1);
	}
	else
	{
		// Substring all of saved. Same as a strdup. Also free saved
		line = ft_substr(saved, 0, ft_strlen(saved), 1);
		if (!*line)
		{
			// if the line is empty don't forget to free it
			free(line);
			line = NULL;
		}
		// Set the static pointer to null
		saved = NULL;
	}
	return (line);
}