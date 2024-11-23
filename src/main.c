#include "shmup.h"

static void	ft_delonemonster(t_entity *monster)
{
	if (monster == NULL)
		return ;
	free(monster);
}

int	loop()
{
	int			time = 0;
	int			point = 0;
	t_player	*player;
	t_bullet	*bullet;
	t_entity	*monster;
	int			key;

	player = create_player(LINES, COLS);
	bullet = create_bullet();
	monster = create_entity(1);

	key = 0;
	monster->x = COLS / 1.5;
	monster->y = LINES / 2;
	while ((key = getch()) != 'q')
	{
		attron(COLOR_PAIR(1));

		// TIME
		printw("Window active since: %ds  score=%d  x=%d  y=%d\n", time, point, player->x, player->y);
		
		// PLAYER MOVE
		if (key == KEY_UP && player->y > 1)player->y -= 1;
		if (key == KEY_DOWN && player->y < LINES - 1)player->y += 1;
		if (key == KEY_LEFT && player->x > 1)player->x -= 1;
		if (key == KEY_RIGHT && player->x < COLS - 1)player->x += 1;
		mvprintw(player->y, player->x, "%c", player->character);

		// BULLET COLLISION
		if (bullet->x == monster->x && bullet->y == monster->y)
		{
			ft_delonemonster(monster);
			monster = create_entity(1);
			monster->x = COLS / 1.5;
			monster->y = (rand() % (LINES - 1)) + 1;
			bullet->active = 0;
			point++;
		}

    	attron(COLOR_PAIR(2));

		// BULLET MOVE
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

		// MONSTER PRINT
		mvprintw(monster->y, monster->x, "%c", monster->character);

		refresh();
		time += 1;
		napms(16);
		clear();
	}
	printw("Window was active for %ds", time);
	
	refresh();
	nodelay(stdscr, FALSE);

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