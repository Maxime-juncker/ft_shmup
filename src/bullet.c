#include "shmup.h"




void bullet_update(t_bullet *bullet, t_map_data *map)
{
	if (!bullet)
		return ;
	attron(COLOR_PAIR(bullet->color));
	mvprintw(bullet->y, bullet->x, "%c", bullet->character);
	if (bullet_collision(bullet, map->obstacles) ||
	 bullet->x >= COLS || bullet->x <= 0)
		bullet->active = false;
	else if (collide(map->player->x, map->player->y, bullet->x, bullet->y))
	{
		bullet->active = false;
		map->player->health -= 45;
	}
	bullet->x += bullet->speed;
	attron(COLOR_PAIR(3));
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

void fire(t_map_data *map, int time)
{
	int			i = 0;

	if (map->bullets[0] == NULL)
	{
		while (i < MAX_BULLET)
		{
			map->bullets[i] = create_bullet(1);
			i++;
		}
	}

	i = 0;
	while (i < MAX_BULLET)
	{
		if (map->bullets[i]->active)
			bullet_update(map->bullets[i], map);
		i++;
	}

	i = 0;
	if (time % map->player->fireate == 0)
	{
		i = get_inactive_bullet(map->bullets);
		if (i == -1)
			return ;
		map->bullets[i]->x = map->player->x + 1;
		map->bullets[i]->y = map->player->y;
		map->bullets[i]->speed = 1;
		map->bullets[i]->color = 1;
		map->bullets[i]->active = true;
	}
}