/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:53 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 16:52:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void enemy_fire(int x, int y, t_bullet *bullets[MAX_BULLET])
{
	int			i = 0;

	i = get_inactive_bullet(bullets);
	if (i == -1)
		return ;
	bullets[i]->x = x - 2;
	bullets[i]->y = y;
	bullets[i]->speed = -2;
	bullets[i]->active = 1;
	bullets[i]->color = 2;

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
			if (tmp == 4 && rand() % 100 == 0)
			{
				enemy_fire(x, y, map->bullets);
			}
			if (tmp == 6 && rand() % 70 == 0)
			{
				enemy_fire(x, y, map->bullets);
			}
			x++;
		}
		y++;
	}
}
