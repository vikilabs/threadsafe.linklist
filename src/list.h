/* This piece of code is free ( free means free. Do whatever useful )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#ifndef _LIST_H
#define _LIST_H
#include <stdint.h>
#include <pthread.h>

struct node{
    void *data;
    struct node *next, *prev;
};

struct list{
    uint8_t active;
    int node_count;
    pthread_mutex_t *lock;
    struct node *head, *tail;
};

extern struct   list    *list_init();
extern int8_t           list_terminate(struct list *l);
extern struct   node    *list_create_node(void *data, size_t data_size);
extern int8_t           list_add_node(struct list *l, struct node *n);
extern int8_t           list_delete_node(struct list *l, struct node *n);
extern void             traverse_list(struct list *l);
extern int              get_nodes_count(struct list *l);

#endif
