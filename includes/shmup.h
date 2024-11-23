/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shmup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:10:22 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 11:30:32 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHMUP_H
# define SHMUP_H

# include <ncurses.h>
# include <libft.h>

# define PLAYER_ID	0

# ifndef MAX_ENTITY
# define MAX_ENTITY 128
# endif

typedef struct s_entity
{
	int	id;

	int	x;
	int	y;

	int	speed;
	int	fireate;
	int	health;
	char character;

} t_entity;

typedef struct s_bullet
{
	int active;
	int x;
	int y;
	char character;
} t_bullet;

void	add_entity(t_entity *new, t_entity *entities[MAX_ENTITY]);
t_entity	*create_player(int row, int col);
t_entity	*create_entity(int id);
t_bullet	*create_bullet();


void draw_bg(int time);

#endif