/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:50:25 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 12:25:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"


/*
 * Add new entity to the entities arr
 * @param new the new entity
 * @param entities the arr containing all entities
*/

t_entity	*create_player(int row, int col)
{
	t_entity *player = NULL;
	(void)col;

	player = ft_calloc(sizeof(t_entity), 1);
	if (!player) // !! maybe replace later by calling a cleanup funciton
		return (NULL);

	player->x = 2;
	player->y = row / 2;
	player->speed = 1;
	player->health = 100;
	player->character = '>';
	player->fireate = 20;
	return (player);
}

t_bullet	*create_bullet(int speed)
{
	t_bullet	*bullet;

	bullet = ft_calloc(sizeof(t_bullet), 1);
	if (!bullet)
		return (NULL);
	bullet->active = 0;
	bullet->character = '-';
	bullet->speed = speed;
	return (bullet);
}
