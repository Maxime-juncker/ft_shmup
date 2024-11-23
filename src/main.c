/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11 /23 08:12:02 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/23 08:16:02 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

int	loop()
{
	int	time = 0;

	nodelay(stdscr, TRUE);
	while (getch() == ERR)
	{
		printw("Window active since: %ds\n", time);
		refresh();
		time += 1;
		napms(1000);
		clear();
	}
	printw("Window was active for %ds", time);
	refresh();
	nodelay(stdscr, FALSE);

	return (0);
}

int main()
{
	// t_entity entities[MAX_ENTITY];
	// add_entity(create_entity(PLAYER_ID), entities);
	initscr();
	loop();

	getch();

	endwin();
	return (0);
}