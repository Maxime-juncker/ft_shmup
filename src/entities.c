/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:50:25 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 11:09:07 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"


/*
 * Add new entity to the entities arr
 * @param new the new entity
 * @param entities the arr containing all entities
*/
void	add_entity(t_entity *new, t_entity *entities[MAX_ENTITY])
{
	if (!new)
		return ;
	entities[new->id] = new;
}

t_entity	*create_player(int row, int col)
{
	t_entity *player = NULL;
	(void)col;

	player = ft_calloc(sizeof(t_entity), 1);
	if (!player) // !! maybe replace later by calling a cleanup funciton
		return (NULL);

	player->id = PLAYER_ID;
	player->x = 2;
	player->y = row / 2;
	player->speed = 1;
	player->health = 1;
	player->character = '>';
	player->fireate = 1;
	return (player);
}

t_bullet	*create_bullet()
{
	t_bullet	*bullet;

	bullet = ft_calloc(sizeof(t_bullet), 1);
	if (!bullet)
		return (NULL);
	bullet->active = 0;
	bullet->character = '-';
	return (bullet);
}


t_entity	*create_entity(int id)
{
	// static int 	id = 0;
	t_entity *entity = NULL;

	// if (id == PLAYER_ID)
	// 	return (create_player());
	// id++;
	
	if (id > MAX_ENTITY)
		return (NULL);
	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);

	entity->id = id;
	entity->speed = 1;
	entity->health = 1;
	entity->fireate = 1;
	entity->character = 'x';
	return (entity);
}