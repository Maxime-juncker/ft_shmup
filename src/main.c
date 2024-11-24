#include "shmup.h"


t_map_data	*create_map()
{
	t_map_data	*map;
	int	i = 0;

	map = ft_calloc(sizeof(t_map_data), 1);
	if (map == NULL)
		return (NULL);

	map->player = create_player(LINES, COLS);
	map->obstacles = create_bg();
	i = 0;
	while (i < MAX_BULLET)
	{
		map->bullets[i] = NULL;
		i++;
	}
	return (map);
}

int	loop()
{
	int			time = 0;
	int			key = 0;
	t_map_data	*map = create_map();

	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

	while ((key = getch()) != 'q' && time < 2147483645)
	{
		draw_bg(map->obstacles, time);
		if (map->player->health <= 25)
			attron(COLOR_PAIR(2));
		else
			attron(COLOR_PAIR(1));
		move(1, 1);
		printw("score=%dp  x=%d  y=%d ship-intergrity=%d%%", time, map->player->x, map->player->y, map->player->health);

		if (key == KEY_UP && map->player->y > 1)map->player->y -= 1;
		if (key == KEY_DOWN && map->player->y < LINES - 1)map->player->y += 1;
		if (key == KEY_LEFT && map->player->x > 1)map->player->x -= 1;
		if (key == KEY_RIGHT && map->player->x < COLS - 1)map->player->x += 1;
		mvprintw(map->player->y, map->player->x, "%c", map->player->character);
		fire(map, time);

		ememy_update(map);

		if (player_collision(map->player, map->obstacles))
		{
			map->player->health -= 45;
			map->obstacles[map->player->y][map->player->x] = 0;
			map->obstacles[map->player->y][map->player->x-1] = 0;
		}
		if (map->player->health <= 0)
			break;

		refresh();
		time += 1;
		napms(16);
		clear();
	}
	clear();
	printw("final score: %d\n", time);
	refresh();
	nodelay(stdscr, FALSE);
	getch();

	return (0);
}


int main()
{
	srand(0);

	initscr();
	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
	loop();

	endwin();

	return (0);
}