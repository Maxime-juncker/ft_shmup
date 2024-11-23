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

//fct qui va appeller check_collide

// ici on veut : ajoute des monstres a la chaine dans une liste,
// appelle une fonction qui va verifier la collision du joueur avec chacun des monstres, 
// et sil y a une collision supprimer le monstre en question