#include "shmup.h"

void	draw_hud(t_map_data *map, int time)
{
	if (map->player->health <= 25)
		attron(COLOR_PAIR(2));
	else
		attron(COLOR_PAIR(1));
	box(stdscr, ACS_VLINE, ACS_HLINE);
	move(1, 1);
	printw("score=%dp  x=%d  y=%d ship-intergrity=%d%%",
	time, map->player->x, map->player->y, map->player->health);

}

void	draw_scene(t_map_data *map)
{
	int	i = 0;
	int	y = 0;
	int	tmp = 0;

	if (map->player->health <= 25)
		attron(COLOR_PAIR(2));
	else
		attron(COLOR_PAIR(1));
	mvprintw(map->player->y, map->player->x, "%c", map->player->character);

	i = 0;
	while (i < MAX_BULLET)
	{

		if (map->bullets[i]->active)
		{
			attron(COLOR_PAIR(map->bullets[i]->color));
			mvprintw(map->bullets[i]->y, map->bullets[i]->x, "-");
		}
		i++;
	}

	while (y < LINES)
	{
		i = 0;
		while (i < COLS)
		{
			tmp = map->obstacles[y][i];
			if (tmp == 2)
			{
				attron(COLOR_PAIR(3));
				mvprintw(y, i, "o");
			}
			else if (tmp == 4)
			{
				attron(COLOR_PAIR(2));
				mvprintw(y, i, "X");
			}
			i++;
		}
		y++;
	}
}

void	render_frame(t_map_data *map, int time)
{
	clear();
	draw_scene(map);
	draw_hud(map, time);
	refresh();
}