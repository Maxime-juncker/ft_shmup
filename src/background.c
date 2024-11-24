/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:38:33 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 13:44:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void	update_obstacles(int **obstacles, int time)
{
	int x = 0;
	int y = 0;
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
				continue;
			}
			if (time % tmp == 0)
			{
				if (x - 1 > 0)
					obstacles[y][x-1] = tmp;
				obstacles[y][x] = 0;
			}
			x++;
		}
		y++;
	}
}

int create_obstacle(int **obstacles, int time)
{
	int y = 0;

	while (y < LINES)
	{
		srand(time);

		if ((rand() + y) % 200 == 1)
			obstacles[y][COLS - 1] = 2; // 2 = asteroid
		else if ((rand() + y) % 400 == 1)
			obstacles[y][COLS - 1] = 4; // 4 = enemy basic
		else if ((rand() + y) % 400 == 1)
			obstacles[y][COLS - 1] = 6; // 4 = enemy harder
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

int update_bg(int **obstacles, int time)
{
	create_obstacle(obstacles, time);

	attron(COLOR_PAIR(3));
	update_obstacles(obstacles, time);

	return (0);
}