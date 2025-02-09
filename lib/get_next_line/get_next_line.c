/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/13 22:25:43 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char const *prefix, char const *suffix)
{
	char	*array;
	size_t	prefixlength;
	size_t	suffixlength;
	size_t	i;

	prefixlength = ft_strlen_gnl(prefix);
	suffixlength = ft_strlen_gnl(suffix);
	i = 0;
	array = (char *)malloc(prefixlength + suffixlength + 1);
	if (array == NULL)
		return (NULL);
	while (i < (prefixlength))
	{
		array[i] = prefix[i];
		i++;
	}
	while (i < (prefixlength + suffixlength))
	{
		array[i] = suffix[i - prefixlength];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*polish_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_substr_gnl(buffer, 0, i + 1);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*create_saved_chars(char *line_read)
{
	char	*saved_chars;
	char	*newline_pos;

	newline_pos = ft_strchr_gnl(line_read, '\n');
	if (newline_pos == NULL)
		return (free(line_read), NULL);
	saved_chars = ft_strdup_gnl(newline_pos + 1);
	if (!saved_chars)
		return (free(line_read), NULL);
	return (free(line_read), saved_chars);
}

char	*return_single_line(int fd, char *buffer)
{
	int		bytes_read;
	char	read_data[BUFFER_SIZE + 1];
	char	*temp;

	if (!buffer)
		buffer = ft_strdup_gnl("");
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, read_data, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		read_data[bytes_read] = '\0';
		temp = ft_strjoin_gnl(buffer, read_data);
		free(buffer);
		if (!temp)
			return (NULL);
		buffer = temp;
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*full_text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!full_text)
		full_text = NULL;
	full_text = return_single_line(fd, full_text);
	if (!full_text)
		return (NULL);
	line = polish_new_line(full_text);
	if (!line)
	{
		free(full_text);
		full_text = NULL;
		return (NULL);
	}
	full_text = create_saved_chars(full_text);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL && i < 20)
// 	{
// 		i++;
// 		printf("Read Line: %s", line);
// 	}
// 	close(fd);
// 	return (0);
// }
