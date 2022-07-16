/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:35:40 by mykman            #+#    #+#             */
/*   Updated: 2022/07/16 15:31:20 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	ft_errormsg(char *msg, int ret)
{
	printf("Error: %s\n", msg);
	return (ret);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		return (ft_errormsg("Wrong argument count", 1));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_errormsg("File not found", 1));
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		printf("line: %s\n", line);
		free(line);
	}

	close(fd);
	return (0);
}
