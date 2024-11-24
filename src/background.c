/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:33 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 20:26:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void	update_obstacles(int **obstacles, int time)
{
	int	x = 0;
	int	y = 0;
	int	tmp = 0;

	while (y < LINES)
	{
		x = 0;
		while (x < COLS)
		{
			tmp = obstacles[y][x];
			if (tmp == 0)
			{
				x++;
				continue ;
			}
			if (time % tmp == 0)
			{
				if (x - 1 > 0)
					obstacles[y][x - 1] = tmp;
				obstacles[y][x] = 0;
			}
			x++;
		}
		y++;
	}
}

int	create_obstacle(t_map_data *map, int time)
{
	int y = 0;

	srand(time);
	while (y < LINES)
	{
		if ((rand() + y) % map->asteroid_rate == 1)
			map->obstacles[y][COLS - 1] = 2; // 2 = asteroid
		else if ((rand() + y) % map->basic_enemy_rate == 1)
			map->obstacles[y][COLS - 1] = 4; // 4 = enemy basic
		else if ((rand() + y) % map->hard_enemy_rate == 1)
			map->obstacles[y][COLS - 1] = 1; // 4 = enemy harder
		y++;
	}
	return (1);
}

int **create_bg()
{
	int **obstacles;

	obstacles = ft_calloc(LINES, sizeof(int *));
	if (obstacles == NULL)
		return (NULL);
	for (int i = 0; i < LINES; i++)
	{
		obstacles[i] = ft_calloc(COLS, sizeof(int));
		if (obstacles[i] == NULL)
			return (NULL);
	}
	return (obstacles);
}

int update_bg(t_map_data *map, int time)
{
	create_obstacle(map, time);

	attron(COLOR_PAIR(3));
	update_obstacles(map->obstacles, time);

	return (0);
}