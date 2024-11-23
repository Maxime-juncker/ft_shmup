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
		attron(COLOR_PAIR(1));
		draw_bg(obstacles, time);
		move(1, 1);
		printw("Window active since: %ds  x=%d  y=%d\n", time, player->x, player->y);

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
			if (bullet->x == COLS)
				bullet->active = 0;
			else
				bullet->x += 1;
		}
		mvprintw(bullet->y, bullet->x, "%c", bullet->character);

		if (player_collide(obstacles, player))
			break;

		refresh();
		time += 1;
		napms(16);
		clear();
	}

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