/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:22:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/06 20:51:55 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * @note if error, why not free map_storage as well?
 *       : game.map already points to map_storage ,
 *         freeing it once is sufficient to prevent double free errors.
 */
int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map_info;
	char	**map_data_storage;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file>\n", 2);
		return (1);
	}
	map_data_storage = get_map_data(argv[1]); // 문자열 배열 형식으로 맵 저장
	if (!map_data_storage)
	{
		ft_putstr_fd("Error: Failed to read map.\n", 2); // 1. retangular 2. walls 3. elements 4. valid path -> map_utils.c
		return (1);
	}
	if (!validate_map_data(map_data_storage, &map_info)) // map_data_validator.c
	{
		free_map_data_storage(map_data_storage);
		map_data_storage = NULL;
		return (1);
	}
	game.map = map_data_storage;
	game.height = map_info.height;
	game.width = map_info.width;
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		free_map_data_storage(game.map);
		game.map = NULL;
		ft_putstr_fd("Error: mlx initialization failed.\n", 2);
		return (1);
	}
	if (!create_window(&game))
	{
		free_map_data_storage(game.map);
		game.map = NULL;
		ft_putstr_fd("Error: Window creation failed.\n", 2);
		return (1);
	}
	init_game(&game, map_data_storage, &map_info);
	render_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}

/** TODO: Understands the code flow
 *  1. ft_putstr_fd(): OK
 *  2. get_map_data(): OK
 *     (1) count_map_lines(): OK
 *  3. validate_map_data(): ...
 *     (a) if_rectangualr(): OK
 *     (b) if_walls_enclose(): OK
 *     (c) if_a_valid_element_and_store: OK
 *     (d) if_valid_elements(): OK
 *     -> if_valid_path()
 *            (a) copy_line(): OK
 *            (b) fill_map_structure(): OK
 *            (c) flood_fill()
 *            (d) check_path_result()
 *            (e) copy_map()
 *  4. free_map_data_storage()
 *  5. ft_putstr_fd()
 *  6. create_window()
 *  7. init_game()
 *  8. render_map()
 *  9. /mlx
 */
