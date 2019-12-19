/* This piece of code is free ( free means free. Do whatever useful )
 *
 *                      Author: Viki (a) Vignesh Natarajan
 *                      Lab   : vikilabs.org
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "alloc_util.h"

struct node *create_node(void *data, int data_size)
{
    struct node *n = NULL;
    void *d = NULL;
    int8_t ret = 0;

    /* It is possible to alloc a node with NULL data */
    if( (data) && ( data_size > 0 )){
        d = (void *) calloc(1, data_size);
        
        if(!d){
            printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
            ret = -1; goto safe_return;
        }
    
    }

    n = (void *) calloc(1, sizeof(struct node));

    if(!n){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
        SAFE_FREE(d);
        ret = -1; goto safe_return;
    }
    
    if(d){
        memcpy(d, data, data_size);
    }
    
    n->next = NULL;
    n->prev = NULL;
    n->data = d;

safe_return:
    
    if(ret == -1){
        return NULL;
    }

    return n;
}


struct list *list_create()
{
    struct list *l = NULL;
    l = (struct list *) calloc(1, sizeof(struct list));
    
    if(!l){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
    }else{
        l->head = NULL;
        l->tail = NULL;
    }

    return l;
}

/* adding like a queue fashion. Adding new node to the tail of the list
 */
int8_t list_add(struct list *l, struct node *n)
{
    assert( l != NULL);
    assert( n != NULL);

    if(!l->tail){

        /*
            .........         .........     
            .       .         .       .
            .  TAIL .         . HEAD  . 
            .       .         .       .
            .........         .........

                    |           |
                    V           V
                  ...................
                  .                 .  --> NULL
         NULL <---.   NODE (FIRST)  .
                  ...................

        */      

        l->tail = n;
        l->head = n;
    }else{

        /*

                                      .........                 .........     
                                      .       .                 .       .
                                      .  TAIL .                 . HEAD  . 
                                      .       .                 .       .
                                      .........                 .........

                                        |                           |
                                        V                           V
                  ...............     ...........               ........
                  .             .---> .         . --  ----  --> .      .
         NULL <---.   NEW NODE  .<--- .  NODE   . <-- ----  --- . NODE .     
                  ...............     ...........               ........

        */

        n->prev = NULL;
        n->next = l->tail;
        l->tail->prev = n;

        /*
                    .........                                   .........     
                    .       .                                   .       .
                    .  TAIL .                                   . HEAD  . 
                    .       .                                   .       .
                    .........                                   .........

                        |                                           |
                        V                                           V
                  ...............     ...........               ........
                  .             .---> .         . --  ----  --> .      .
         NULL <---.   NEW NODE  .<--- .  NODE   . <-- ----  --- . NODE .     
                  ...............     ...........               ........


        */      

        l->tail = n;
    }

    return 0;
}


/* adding like a queue fashion. Adding new node to the tail of the list
 */
int8_t list_delete(struct list *l, struct node *n)
{
    struct node *d=NULL, *itr=NULL;
    struct node *n1 = NULL, *n2=NULL;

    assert( l != NULL);
    assert( n != NULL);

    itr = l->head;

    while(itr){

        /*

                    .........                         .........     
                    .       .                         .       .
                    .  TAIL .                         . HEAD  . 
                    .       .                         .       .
                    .........                         .........

                        |                                  |
                        V                                  V
                  ............       ............       ........
                  .          .  ---> .          . ----> .      .
         NULL <---.   NODE   .  <--- .  NODE (D). <---- . NODE .---> NULL     
                  ............       ............       ........

        */

        if(itr == n){
            
            d = itr;

            if(d == l->head){
                l->head = l->head->prev;
                l->head->next = NULL;
            }else{
                n1 = d->prev;
                n2 = d->next;
                n1->next = n2;
                n2->prev = n1;
            }

            free(d);
            d = NULL;

            itr = itr->prev;

        }

    }

    return 0;
}



