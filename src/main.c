/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11 /23 08:12:02 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 08:16:02 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"


void	update_obstacles(int **obstacles)
{
	int x = 0;
	int y = 0;

	box(stdscr, ACS_VLINE, ACS_HLINE);

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			if (obstacles[y][x] == 0)
			{
				x++;
				continue;
			}
			obstacles[y][x-1] = 1;
			obstacles[y][x] = 0;
			move(y, x);
			addch('X');
			x++;
		}
		y++;
	}
}

int create_obstacle(int **obstacles, int time)
{
	int y = 0;

	while (y < LINES)
	{
		if ((time + y ) % 5 == 1)
			obstacles[y][COLS - 1] = 1;
	}
	return (1);
}

int	loop()
{
	int **obstacles;
	obstacles = ft_calloc(LINES, sizeof(int *));
	for (int i = 0; i < LINES; i++)
	{
		obstacles[i] = ft_calloc(COLS, sizeof(int));
	}
	obstacles[10][15] = 1;

	int			time = 0;
	t_entity	*player;
	t_bullet	*bullet;
	int			key;

	player = create_player(LINES, COLS);
	bullet = create_bullet();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	key = 0;
	while ((key = getch()) != '\n')
	{
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

		update_obstacles(obstacles);
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
	initscr();
	curs_set(0);
	loop();

	endwin();
	return (0);
}