/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:42 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 18:18:16 by mjuncker         ###   ########.fr       */
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

t_map_data	*create_map(int difficulty)
{
	t_map_data	*map;
	int	i = 0;

	map = ft_calloc(sizeof(t_map_data), 1);
	if (map == NULL)
		return (NULL);

	map->player = create_player(LINES);
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

	if (difficulty == 0)
	{
		map->asteroid_rate = 150;
		map->basic_enemy_rate = 1000;
		map->hard_enemy_rate = 2147483647;
	}
	else if (difficulty == 1)
	{
		map->asteroid_rate = 150;
		map->basic_enemy_rate = 500;
		map->hard_enemy_rate = 800;
	}
	else if (difficulty == 2)
	{
		map->asteroid_rate = 300;
		map->basic_enemy_rate = 100;
		map->hard_enemy_rate = 200;
	}
	return (map);
}

int	update_player(t_map_data *map, int time, int key)
{
	if (key == KEY_UP && map->player->y > 2)map->player->y -= 1;
	if (key == KEY_DOWN && map->player->y < LINES - 2)map->player->y += 1;
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
	mvprintw(LINES / 2 + y_offset, (COLS / 2) - (len / 2) + x_offset, "%s", msg);
}

int menu(int selected)
{
	int	key = -1;

	clear();
	nodelay(stdscr, FALSE);
	box(stdscr, '|', '#');
	print_in_middle("PLAY EASY", 0, 0);
	print_in_middle("PLAY MEDIUM", 1, 0);
	attron(COLOR_PAIR(2));
	print_in_middle("PLAY HARD", 2, 0);
	attron(COLOR_PAIR(3));
	print_in_middle("QUIT", 3, 0);
	print_in_middle(">>", selected, -7);
	refresh();
	key = getch();

	if (key == KEY_UP && selected > 0)
		return (menu(selected - 1));
	if (key == KEY_DOWN && selected < 3)
		return (menu(selected + 1));
	else if (key == '\n')
	{
		if (selected == 0)
			return 0;
		if (selected == 1)
			return 1;
		if (selected == 2)
			return 2;
		if (selected == 3)
			return -1;
	}
	return (menu(selected));
}

int	loop()
{
	int			time = 0;
	int			key = 0;
	int			difficulty = -1;
	t_map_data	*map = NULL;

	difficulty = menu(0);
	if (difficulty == -1)
		return (0);
	nodelay(stdscr, TRUE);

	map = create_map(difficulty);
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
		update_bg(map, time);
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
