#include "shmup.h"

t_entity *add_monster(t_entity *head, int x, int y)
{
    t_entity *new_monster;

    new_monster = (t_entity *)calloc(1, sizeof(t_entity));
    if (!new_monster)
        return (head);
    new_monster->x = x;
    new_monster->y = y;
    new_monster->character = 'X';
    new_monster->next = head;
    return (new_monster);
}

t_entity   *remove_monster(t_entity *head, t_entity *to_remove)
{
    t_entity *current;
    t_entity *previous;

    if (!head || !to_remove)
        return (head);
    if (head == to_remove)
    {
        current = head->next;
        free(head);
        return (current);
    }
    previous = head;
    current = head->next;
    while (current)
    {
        if (current == to_remove)
        {
            previous->next = current->next;
            free(current);
            return (head);
        }
        previous = current;
        current = current->next;
    }
    return (head);
}

int check_collide(t_entity *player, t_entity *monster)
{
    if (player->x == monster->x && player->y == monster->y)
        return (1);
    return (0);
}

t_entity *monsters_collide(t_entity *player, t_entity *monsters)
{
    t_entity *current;
    t_entity *next;

    current = monsters;
    while (current != NULL)
    {
        next = current->next;
        if (check_collide(player, current))
            monsters = remove_monster(monsters, current);
        current = next;
    }
    return (monsters);
}

void enemy_fire(int x, int y, t_bullet *bullets[MAX_BULLET])
{
	int			i = 0;

	if (rand() % 100 == 0)
	{
		i = get_inactive_bullet(bullets);
		if (i == -1)
			return ;
		bullets[i]->x = x - 2;
		bullets[i]->y = y;
		bullets[i]->speed = -1;
		bullets[i]->active = 1;
		bullets[i]->color = 2;
	}

}

void	ememy_update(int **obstacles, t_bullet *bullets[MAX_BULLET])
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
			if (tmp == 4)
			{
				enemy_fire(x, y, bullets);
			}
			x++;
		}
		y++;
	}
}

//fct qui va appeller check_collide

// ici on veut : ajoute des monstres a la chaine dans une liste,
// appelle une fonction qui va verifier la collision du joueur avec chacun des monstres, 
// et sil y a une collision supprimer le monstre en question