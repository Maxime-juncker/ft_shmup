/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:28 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 17:57:23 by mjuncker         ###   ########.fr       */
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
	if (xsrc >= COLS - 1)
		return (0);
	if (obstacles[ysrc][xsrc] > 0 || obstacles[ysrc][xsrc + 1] > 0)
	{
		obstacles[ysrc][xsrc] = 0;
		obstacles[ysrc][xsrc + 1] = 0;
		return (1);
	}
	return (0);
}

int bullet_collision(t_bullet *bullet, int **obstacles)
{
	if (bullet->speed < 0)
		return (0);
	return (obstacle_collide(obstacles, bullet->x, bullet->y));
}

int player_collision(t_entity *player, int **obstacles)
{
	return (obstacle_collide(obstacles, player->x, player->y));
}
