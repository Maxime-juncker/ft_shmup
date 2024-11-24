/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shmup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:10:22 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 11:24:20 by mjuncker         ###   ########.fr       */
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
	int	speed;
	int color;
} t_bullet;

typedef struct map_data
{
	t_entity	*player;
	t_bullet	*bullets[MAX_BULLET];
	int			**obstacles;

} t_map_data;

int			get_inactive_bullet(t_bullet *bullets[MAX_BULLET]);
t_entity	*create_player(int row, int col);
t_entity	*create_entity(int id);
t_bullet	*create_bullet(int speed);

void bullet_update(t_bullet *bullet, t_map_data *map);
int	get_inactive_bullet(t_bullet *bullets[MAX_BULLET]);
void fire(t_map_data *map, int time);

int			draw_bg(int **obstacles, int time);
int			**create_bg();

int			collide(int x1, int y1, int x2, int y2);
int 		bullet_collision(t_bullet *bullet, int **obstacles);
int 		player_collision(t_entity *player, int **obstacles);

void		ememy_update(t_map_data *map);

#endif