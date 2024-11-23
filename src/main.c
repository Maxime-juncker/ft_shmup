#include "shmup.h"

void bullet_update(t_bullet *bullet, int **obstacles)
{
	if (!bullet)
		return ;
	mvprintw(bullet->y, bullet->x, "%c", bullet->character);
	if (bullet_collision(bullet, obstacles))
	{
		bullet->active = false;
	}
	bullet->x++;
}

int	get_inactive_bullet(t_bullet *bullets[MAX_BULLET])
{
	int	i = 0;

	while (i < MAX_BULLET)
	{
		if (!bullets[i]->active)
			return (i);
		i++;
	}
	return (-1);
}

void fire(t_entity *player, int** obstacles, int time)
{
	static t_bullet	*bullets[MAX_BULLET] = {NULL};
	int			i = 0;

	if (*bullets == NULL) // creation
	{
		while (i < MAX_BULLET)
		{
			bullets[i] = create_bullet(player);
			i++;
		}
	}

	i = 0;
	while (i < MAX_BULLET)
	{
		if (bullets[i]->active)
			bullet_update(bullets[i], obstacles);
		i++;
	}

	i = 0;
	if (time % player->fireate == 0)
	{
		i = get_inactive_bullet(bullets);
		if (i == -1)
			return ;
		bullets[i]->x = player->x;
		bullets[i]->y = player->y;
		bullets[i]->active = true;
	}
}

int	loop()
{
	static int **obstacles;
	int			time = 0;
	t_entity	*player;
	int			key;

	if (obstacles == NULL)
		obstacles = create_bg();
	player = create_player(LINES, COLS);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
	key = 0;
	while ((key = getch()) != '\n' && time < 2147483645)
	{
		draw_bg(obstacles, time);
		if (player->health <= 25)
			attron(COLOR_PAIR(2));
		else
			attron(COLOR_PAIR(1));
		move(1, 1);
		printw("score=%dp  x=%d  y=%d ship-intergrity=%d%%", time, player->x, player->y, player->health);

		if (key == KEY_UP && player->y > 1)player->y -= 1;
		if (key == KEY_DOWN && player->y < LINES - 1)player->y += 1;
		if (key == KEY_LEFT && player->x > 1)player->x -= 1;
		if (key == KEY_RIGHT && player->x < COLS - 1)player->x += 1;

		mvprintw(player->y, player->x, "%c", player->character);
		fire(player, obstacles, time);

		if (player_collision(player, obstacles))
		{
			player->health -= 45;
			obstacles[player->y][player->x] = 0;
			obstacles[player->y][player->x-1] = 0;
			if (player->health <= 0)
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