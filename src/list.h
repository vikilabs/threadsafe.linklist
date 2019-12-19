/* This piece of code is free ( free means free. Do whatever useful )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#ifndef _LIST_H
#define _LIST_H
#include <stdint.h>

enum __list_error_codes{
    OPERATION_SUCCESS,
    OUT_OF_MEMORY,
    LIST_HANDLE_NULL,
    LIST_NODE_NULL
};

struct node{
    void *data;
    struct node *next, *prev;
};

struct list{
    struct node *head, *tail;
};

extern struct   list    *list_init();
extern int8_t           list_terminate(struct list *l);
extern struct   node    *list_create_node(void *data, int data_size);
extern int8_t           list_add_node(struct list *l, struct node *n);
extern int8_t           list_delete_node(struct list *l, struct node *n);

#endif
