#include "shmup.h"

int	collide(t_entity *src, int xsrc, int ysrc)
{
	if (src->x == xsrc && src->y == ysrc)
		return (1);
	return (0);
}

int obstacle_collide(int **obstacles, t_entity *src)
{
	int x = 0;
	int y = 0;

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			if (obstacles[y][x] == 1 && collide(src, x, y))
				return(1);
			x++;
		}
		y++;
	}
	return (0);
}