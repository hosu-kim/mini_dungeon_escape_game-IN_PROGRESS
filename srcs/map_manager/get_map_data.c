/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:36:50 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/05 19:05:21 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief checks if extension is ".ber"
 * @details 
 * - Used: read_map_file()->get_map_data()
 * - Codeflow
 * 	1. while: Counts length of file name
 * 	2. if(1): length < 5 -> return (0)
 * 	3. else if(1): last 4 characters != ".ber" -> return (0)
 * 	4. If file extension is ".ber" -> return 1
 * 
 * @param filename Filename to check
 * @return if extension is ".ber", 1, if not 0.
 */
static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len <= 4)
		return (0);
	else if (filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r')
		return (0);
	return (1);
}

/**
 * @brief Opens map file
 * @details
 * - Codeflow
 *   1. check_file_extention()
 *    (1) false: return -1 -> sending error as fd
 *   2. Open file: open(pathname, flags), O_RDONLY(Open for reading only) 
 *                 -> false: return -1
 *   3. Return fd
 * 
 * @param filename File to open
 * @return File descriptor
 */
int	read_map_file(char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		ft_putstr_fd("Error: The file extension is not '.ber'.\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: File open failure.\n", 2);
		return (-1);
	}
	return (fd);
}

/**
 * @brief
 * @details
 * - Codeflow
 *  1. count_map_lines(): counts how many lines in map (.ber)
 *  2. read map file
 *  3. allocates mem to map_data with line counts
 *  4. while(1st): appends lines to map_data
 */
char	**get_map_data(char *filename)
{
	int		fd;
	char	**map_data;
	char	*line;
	int		line_count;
	int		i;

	line_count = count_map_lines(filename);
	if (line_count <= 0)
	{
		ft_putstr_fd("Error: The map is empty or cannot be read.\n", 2);
		return (NULL);
	}
	fd = read_map_file(filename);
	if (fd == -1)
		return (NULL);
	map_data = malloc(sizeof(char *) * (line_count + 1));
	if (!map_data)
		return (NULL);
	line = get_line_from_fd(fd);
	i = 0;
	while (line != NULL && i < line_count)
	{
		map_data[i++] = line;
		line = get_line_from_fd(fd);
	}
	map_data[i] = NULL;
	close(fd);
	return (map_data);
}
