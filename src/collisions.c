#include "shmup.h"

int	collide(t_entity *player, int xsrc, int ysrc)
{
	if (player->x == xsrc && player->y == ysrc)
		return (1);
	return (0);
}

int player_collide(int **obstacles, t_entity *player)
{
	int x = 0;
	int y = 0;

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			if (obstacles[y][x] == 1 && collide(player, x, y))
			{
				clear();
				printw("You lost");
				refresh();
				return(1);
			}
			x++;
		}
		y++;
	}
	return (0);
}