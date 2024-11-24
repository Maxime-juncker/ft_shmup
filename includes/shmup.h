/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shmup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:10:22 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/24 18:08:20 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHMUP_H
# define SHMUP_H

# include <ncurses.h>
# include <libft.h>

# ifndef MAX_BULLET
# define MAX_BULLET 2048
# endif
typedef struct s_entity
{
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
	int			score;
	int			asteroid_rate;
	int			basic_enemy_rate;
	int			hard_enemy_rate;

} t_map_data;

// entity.c
t_entity	*create_player(int row);
t_bullet	*create_bullet(int speed);

// bullet.c
void bullet_update(t_bullet *bullet, t_map_data *map);
int	get_inactive_bullet(t_bullet *bullets[MAX_BULLET]);
int fire(t_map_data *map, int time);

// bacground.c
int			update_bg(t_map_data *map, int time);
int			**create_bg();

// collision.c
int			collide(int x1, int y1, int x2, int y2);
int 		bullet_collision(t_bullet *bullet, int **obstacles);
int 		player_collision(t_entity *player, int **obstacles);

// enemy.c
void		ememy_update(t_map_data *map);

// Renderer.c
void	render_frame(t_map_data *map);

#endif