#include "shmup.h"

void enemy_fire(int x, int y, t_bullet *bullets[MAX_BULLET])
{
	int			i = 0;

	if (rand() % 100 == 0)
	{
		i = get_inactive_bullet(bullets);
		if (i == -1)
			return ;
		bullets[i]->x = x - 2;
		bullets[i]->y = y;
		bullets[i]->speed = -1;
		bullets[i]->active = 1;
		bullets[i]->color = 2;
	}

}

void	ememy_update(t_map_data *map)
{
	int x = 0;
	int y = 0;
	int	tmp = 0;

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			tmp = map->obstacles[y][x];
			if (tmp == 4)
			{
				enemy_fire(x, y, map->bullets);
			}
			x++;
		}
		y++;
	}
}
