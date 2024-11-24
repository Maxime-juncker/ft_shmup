/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:28 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 13:38:29 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

int	collide(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2)
		return (1);
	return (0);
}

int obstacle_collide(int **obstacles, int xsrc, int ysrc)
{
	int x = 0;
	int y = 0;

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			if ((obstacles[y][x] > 0 || obstacles[y][x - 1] > 0)
				&& collide(xsrc, ysrc, x, y))
			{
				obstacles[y][x] = 0;
				obstacles[y][x - 1] = 0;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int bullet_collision(t_bullet *bullet, int **obstacles)
{
	return (obstacle_collide(obstacles, bullet->x, bullet->y));
}

int player_collision(t_entity *player, int **obstacles)
{
	return (obstacle_collide(obstacles, player->x, player->y));
}
