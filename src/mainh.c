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

	// printw("%d %d", COLS, LINES);

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
	int **obstables;
	int time = 0;

	int y = 0;

	obstables = ft_calloc(LINES, sizeof(int *));
	if (!obstables)
		return (1);
	while (y < LINES)
	{
		obstables[y] = ft_calloc(COLS, sizeof(int));
		if (!obstables[y])
			return (1);
		y++;
	}

	obstables[10][10] = 1;
	nodelay(stdscr, TRUE);
	while (getch() == ERR)
	{
		box(stdscr, ACS_VLINE, ACS_HLINE);
		update_obstacles(obstables);
		refresh();
		napms(16);
		clear();
		create_obstacle(obstables, time);
		time++;
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

	endwin();
	return (0);
}