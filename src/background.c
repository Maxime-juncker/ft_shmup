#include "shmup.h"

static void	update_obstacles(int **obstacles, int time)
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
			if (time % 2 == 0)
			{
				obstacles[y][x-1] = 1;
				obstacles[y][x] = 0;
			}
			move(y, x);
			addch('X');
			x++;
		}
		y++;
	}
}

static int create_obstacle(int **obstacles, int time)
{
	int y = 0;

	while (y < LINES)
	{
		srand(time);

		if ((rand() + y) % 130 == 1)
			obstacles[y][COLS - 1] = 1;
		y++;
	}
	return (1);
}

int **create_bg()
{
	int **obstacles;

	obstacles = ft_calloc(LINES, sizeof(int *));
	for (int i = 0; i < LINES; i++)
	{
		obstacles[i] = ft_calloc(COLS, sizeof(int));
	}
	return (obstacles);
}

int draw_bg(int **obstacles, int time)
{
	create_obstacle(obstacles, time);

	attron(COLOR_PAIR(2));
	update_obstacles(obstacles, time);
	attron(COLOR_PAIR(1));

	return (0);

}