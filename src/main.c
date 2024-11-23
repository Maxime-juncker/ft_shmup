#include "shmup.h"

int	loop()
{
	static int **obstacles;
	int			time = 0;
	t_entity	*player;
	t_bullet	*bullet;
	int			key;

	if (obstacles == NULL)
		obstacles = create_bg();
	player = create_player(LINES, COLS);
	bullet = create_bullet();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
	key = 0;
	while ((key = getch()) != '\n')
	{
		draw_bg(obstacles, time);
		if (player->health > 1)
			attron(COLOR_PAIR(1));
		move(1, 1);
		printw("score: %dp  x=%d  y=%d health=%d", time, player->x, player->y, player->health);

		if (key == KEY_UP && player->y > 1)player->y -= 1;
		if (key == KEY_DOWN && player->y < LINES - 1)player->y += 1;
		if (key == KEY_LEFT && player->x > 1)player->x -= 1;
		if (key == KEY_RIGHT && player->x < COLS - 1)player->x += 1;

		mvprintw(player->y, player->x, "%c", player->character);

		if (!bullet->active)
		{
			bullet->active = 1;
			bullet->x = player->x + 1;
			bullet->y = player->y;
		}
		else
		{
			if (obstacles[bullet->y][bullet->x] == 1 || obstacles[bullet->y][bullet->x-1] == 1)
			{
				bullet->active = 0;
				obstacles[bullet->y][bullet->x] = 0;
				obstacles[bullet->y][bullet->x-1] = 0;
			}
			else if (bullet->x == COLS)
				bullet->active = 0;
			else
				bullet->x += 1;
		}
		mvprintw(bullet->y, bullet->x, "%c", bullet->character);

		if (obstacle_collide(obstacles, player))
		{
			player->health--;
			obstacles[player->y][player->x] = 0;
			obstacles[player->y][player->x-1] = 0;
			if (player->health == 0)
				break;
		}

		refresh();
		time += 1;
		napms(16);
		clear();
	}
	clear();
	printw("final score: %d\n", time);
	refresh();
	nodelay(stdscr, FALSE);

	return (0);
}


int main()
{
	initscr();
	curs_set(0);
	loop();
	getch();
	endwin();
	return (0);
}