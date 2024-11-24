/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:42 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 17:25:55 by mjuncker         ###   ########.fr       */
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

void	game_over(t_map_data *map, int time)
{
	int total_secondes = time / 40;
	nodelay(stdscr, FALSE);
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	mvprintw(LINES / 2 - 1, (COLS / 2) - 10, "Final score : %d", map->score);
	mvprintw(LINES / 2, (COLS / 2) - 9, "Survived : %dm %ds", total_secondes / 60, total_secondes % 60);
	refresh();
	getch();
}

void	print_in_middle(char *msg, int y_offset, int x_offset)
{
	int len = ft_strlen(msg);
	mvprintw(LINES / 2 + y_offset, (COLS / 2) - len + x_offset, "%s", msg);
}

int menu(int selected)
{
	int	key = -1;

	clear();
	nodelay(stdscr, FALSE);
	box(stdscr, '|', '#');
	print_in_middle("PLAY", 0, 0);
	print_in_middle("QUIT", 1, 0);
	print_in_middle(">>", selected, -5);
	refresh();
	key = getch();

	if (key == KEY_UP && selected > 0)
		return (menu(selected - 1));
	if (key == KEY_DOWN && selected < 1)
		return (menu(selected + 1));
	else if (key == '\n')
	{
		if (selected == 0)
			return 0;
		if (selected == 1)
			return -1;
	}
	return (menu(selected));

}

int	loop()
{
	int			time = 0;
	int			key = 0;
	t_map_data	*map = NULL;

	if (menu(0) == -1)
		return (0);
	nodelay(stdscr, TRUE);

	map = create_map();
	if (map == NULL)
	{
		cleanup(map);
		return (1);
	}

	while ((key = getch()) != 'q' && !game_stop(map, time))
	{
		// update cycle
		if (update_player(map, time, key) == -1)
			break;
		update_bg(map->obstacles, time);
		ememy_update(map);

		// render screen
		render_frame(map);

		// wait next frame
		napms(25);
		time++;
	}
	game_over(map, time);
	return (cleanup(map));
}

void init()
{
	srand(0);

	initscr();

	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

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
