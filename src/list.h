/* This piece of code is free ( free means free. Do whatever useful )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#ifndef _LIST_H
#define _LIST_H
#include <stdint.h>

struct node{
    void *data;
    struct node *next, *prev;
};

struct list{
    struct node *head, *tail;
};

extern struct node *create_node(void *data, int data_size);
extern struct list *list_create();
extern int8_t list_add(struct list *l, struct node *n);
extern int8_t list_delete(struct list *l, struct node *n);

#endif
