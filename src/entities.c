/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:50:25 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 09:21:35 by mjuncker         ###   ########.fr       */
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

t_entity	*create_player(int id)
{
	t_entity *player = NULL;

	player = ft_calloc(sizeof(t_entity), 1);
	if (!player) // !! maybe replace later by calling a cleanup funciton
		return (NULL);

	player->id = PLAYER_ID;
	player->speed = 1;
	player->health = 1;
	player->fireate = 1;
	player->character = 'O';
	return (player);
}


t_entity	*create_entity(int id)
{
	static int 	id = 0;
	t_entity *entity = NULL;

	if (id == PLAYER_ID)
		return (create_player);

	id++;
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