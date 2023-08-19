/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:27:03 by anmohamm          #+#    #+#             */
/*   Updated: 2023/08/18 17:35:07 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_from_buffer(int fd, char *finalbuffer)
{
	char		*buffer;
	ssize_t		bytesread;

	buffer = (char *) malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
	{
		return (NULL);
	}
	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		finalbuffer = ft_strjoin(finalbuffer, buffer);
		if (ft_strchr(finalbuffer, '\n'))
			break ;
	}
	free(buffer);
	return (finalbuffer);
}

char	*remaining_from(char *finalbuff)
{
	char	*rem;
	int		i;
	int		j;

	i = 0;
	while (finalbuff[i] && finalbuff[i] != '\n')
		i++;
	if (finalbuff[i] == '\n')
		i++;
	if (!finalbuff[i])
	{
		free(finalbuff);
		return (NULL);
	}
	rem = (char *)malloc(ft_strlen(finalbuff) - ft_lengthtilln(finalbuff) + 1);
	j = 0;
	while (finalbuff[i])
	{
		rem[j++] = finalbuff[i++];
	}
	rem[j] = '\0';
	free(finalbuff);
	return (rem);
}

char	*get_from_finalbuffer(char *finalbuffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!finalbuffer[i])
	{
		return (NULL);
	}
	line = (char *)malloc(ft_lengthtilln(finalbuffer) + 2 * (sizeof(char)));
	if (!line)
		return (NULL);
	while (finalbuffer[i] != '\0' && finalbuffer[i] != '\n')
	{
		line[i] = finalbuffer[i];
		i++;
	}
	if (finalbuffer[i] == '\n')
	{
		line[i] = finalbuffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*finalbuffer[256];
	char		*finalline;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	if (BUFFER_SIZE > 2147483647)
		return (NULL);
	finalbuffer[fd] = read_from_buffer(fd, finalbuffer[fd]);
	if (!finalbuffer[fd])
		return (NULL);
	finalline = get_from_finalbuffer(finalbuffer[fd]);
	finalbuffer[fd] = remaining_from(finalbuffer[fd]);
	return (finalline);
}

/*
 int main()
  {
	char *lines1;
	char *lines2;
	int fd1;
	int fd2;

	fd1 = open("a.txt",O_RDONLY);
	fd2 = open("b.txt",O_RDONLY);
	 while (1)
	 {
		lines1 = get_next_line(fd1);
		lines2 = get_next_line(fd2);

		printf("%s ||",lines1);
		printf("%s ||",lines2);

		if (!lines1 && !lines2)
		{
			break;
		}
		free(lines1);
		free(lines2);
	 }
	close(fd1);
	close(fd2);
	return(0);
 }
*/