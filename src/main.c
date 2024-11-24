/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:42 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 14:10:50 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

int	cleanup(t_map_data *map)
{
	int	i = 0;

	while (i < LINES)
	{
		free(map->obstacles[i]);
		i++;
	}
	free(map->obstacles);

	i = 0;
	while (i < MAX_BULLET)
	{
		free(map->bullets[i]);
		i++;
	}

	free(map->player);
	free(map);

	return (0);
}

t_map_data	*create_map()
{
	t_map_data	*map;
	int	i = 0;

	map = ft_calloc(sizeof(t_map_data), 1);
	if (map == NULL)
		return (NULL);

	map->player = create_player(LINES, COLS);
	if (map->player == NULL)
		return (NULL);
	map->obstacles = create_bg();
	if (map->obstacles == NULL)
		return (NULL);
	i = 0;
	while (i < MAX_BULLET)
	{
		map->bullets[i] = NULL;
		i++;
	}
	return (map);
}

int	update_player(t_map_data *map, int time, int key)
{
	if (key == KEY_UP && map->player->y > 1)map->player->y -= 1;
	if (key == KEY_DOWN && map->player->y < LINES - 1)map->player->y += 1;
	if (key == KEY_LEFT && map->player->x > 1)map->player->x -= 1;
	if (key == KEY_RIGHT && map->player->x < COLS - 1)map->player->x += 1;
	if (fire(map, time) == -1)
		return (-1);

	if (player_collision(map->player, map->obstacles))
	{
		map->player->health -= 45;
		map->obstacles[map->player->y][map->player->x] = 0;
		map->obstacles[map->player->y][map->player->x-1] = 0;
	}
	return (0);
}

int	game_stop(t_map_data *map, int time)
{
	return (map->player->health <= 0 || time >= 2147483645);
}

void	game_over(t_map_data *map)
{
	nodelay(stdscr, FALSE);
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	mvprintw(LINES / 2, (COLS / 2) - 8, "Final score : %d", map->score);
	refresh();
	getch();
}

int	loop()
{
	int			time = 0;
	int			key = 0;
	t_map_data	*map = create_map();

	if (map == NULL)
	{
		cleanup(map);
		return (1);
	}

	while ((key = getch()) != 'q' && !game_stop(map, time))
	{
		// update cycle
		update_bg(map->obstacles, time);
		ememy_update(map);
		if (update_player(map, time, key) == -1)
			break;

		// render screen
		render_frame(map);

		// wait next frame
		napms(16);
		time++;
	}
	game_over(map);
	return (cleanup(map));
}

void init()
{
	srand(0);

	initscr();

	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);\

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}
int main()
{
	init();

	loop();
	endwin();
	exit_curses(0);
	return (0);
}
