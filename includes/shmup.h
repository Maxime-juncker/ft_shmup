/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shmup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:10:22 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 16:05:16 by mjuncker         ###   ########.fr       */
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

# ifndef MAX_BULLET
# define MAX_BULLET 128
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
	short int active;
	int x;
	int y;
	char character;
} t_bullet;

void	add_entity(t_entity *new, t_entity *entities[MAX_ENTITY]);
t_entity	*create_player(int row, int col);
t_entity	*create_entity(int id);
t_bullet	*create_bullet(t_entity *source);


int draw_bg(int **obstacles, int time);
int **create_bg();

int	collide(int x1, int y1, int x2, int y2);
int bullet_collision(t_bullet *bullet, int **obstacles);
int player_collision(t_entity *player, int **obstacles);


#endif