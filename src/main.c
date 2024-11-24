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

void	update_player(t_map_data *map, int time, int key)
{
	if (key == KEY_UP && map->player->y > 1)map->player->y -= 1;
	if (key == KEY_DOWN && map->player->y < LINES - 1)map->player->y += 1;
	if (key == KEY_LEFT && map->player->x > 1)map->player->x -= 1;
	if (key == KEY_RIGHT && map->player->x < COLS - 1)map->player->x += 1;
	fire(map, time);

	if (player_collision(map->player, map->obstacles))
	{
		map->player->health -= 45;
		map->obstacles[map->player->y][map->player->x] = 0;
		map->obstacles[map->player->y][map->player->x-1] = 0;
	}
}

int	game_stop(t_map_data *map, int time)
{
	return (map->player->health <= 0 || time >= 2147483645);
}

void	game_over(t_map_data *map)
{
	clear();
	printw("final score: %d\n", map->score);
	refresh();
	nodelay(stdscr, FALSE);
	getch();
}

int	loop()
{
	int			time = 0;
	int			key = 0;
	t_map_data	*map = create_map();

	if (map == NULL) // !! cleanup before return
		return (1);

	while ((key = getch()) != 'q' && !game_stop(map, time))
	{
		// update cycle
		update_bg(map->obstacles, time);
		ememy_update(map);
		update_player(map, time, key);

		// render screen
		render_frame(map, time);

		// wait next frame
		napms(16);
		time++;
		map->score++;
	}
	game_over(map);

	return (0);
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

	if (loop() == 1)
	{
		// !! cleanup
		exit(1);
	}
	endwin();

	return (0);
}