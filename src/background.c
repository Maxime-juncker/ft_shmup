#include "shmup.h"

static void	update_obstacles(int **obstacles, int time)
{
	int x = 0;
	int y = 0;
	int	tmp = 0;

	box(stdscr, ACS_VLINE, ACS_HLINE);

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			tmp = obstacles[y][x];
			if (tmp == 0)
			{
				x++;
				continue;
			}
			if (time % tmp == 0)
			{
				obstacles[y][x-1] = tmp;
				obstacles[y][x] = 0;
			}
			move(y, x);
			if (tmp == 2)
			{
				attron(COLOR_PAIR(3));
				addch('o');
			}
			else if (tmp == 4)
			{
				attron(COLOR_PAIR(2));
				addch('X');
			}
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

		if ((rand() + y) % 200 == 1)
			obstacles[y][COLS - 1] = 2; // 2 = asteroid
		else if ((rand() + y) % 400 == 1)
			obstacles[y][COLS - 1] = 4; // 4 = enemy
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

	attron(COLOR_PAIR(3));
	update_obstacles(obstacles, time);

	return (0);

}