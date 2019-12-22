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
#include "lalloc.h"


struct list *list_init()
{
    struct list *l = NULL;
    l = (struct list *) lalloc(sizeof(struct list));
    
    if(!l){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
    }else{
        l->head = NULL;
        l->tail = NULL;
    }

    return l;
}

int8_t list_terminate(struct list *l)
{
    struct node *itr=NULL, *d=NULL;

    assert( l != NULL);

    itr = l->head;
    l->head = NULL;
    l->tail = NULL;

    while(itr){
        d = itr;
        itr = itr->next;
        LFREE(d);
    }

    return 0;
}

struct node *list_create_node(void *data, int data_size)
{
    struct node *n = NULL;
    void *d = NULL;
    int8_t ret = 0;

    /* It is possible to alloc a node with NULL data */
    if( (data) && ( data_size > 0 )){
        d = (void *) lalloc(data_size);
        
        if(!d){
            printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
            ret = -1; goto safe_return;
        }
    
    }

    n = (void *) lalloc(sizeof(struct node));

    if(!n){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
        LFREE(d);
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


int8_t list_add_node(struct list *l, struct node *n)
{
    assert( l != NULL);
    assert( n != NULL);

    if(!l->tail){

        /*
            .........         .........     
            .       .         .       .
            .  HEAD .         . TAIL  . 
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
            .  HEAD .                 . TAIL  . 
            .       .                 .       .
            .........                 .........

                |                       |
                V                       V
            ...........               ........      ............
            .         . --  ----  --> .      . ---> .          .---> NULL
            .  NODE   . <-- ----  --- . NODE . <--- . NEW NODE .  
            ...........               ........      ............

        */

        n->next = NULL;
        n->prev = l->tail;
        l->tail->next = n;

        /*

            .........                               .........     
            .       .                               .       .
            .  HEAD .                               . TAIL  . 
            .       .                               .       .
            .........                               .........

                |                                       |
                V                                       V
            ...........               ........      ............
            .         . --  ----  --> .      . ---> .          .---> NULL
            .  NODE   . <-- ----  --- . NODE . <--- . NEW NODE .  
            ...........               ........      ............

        */

        l->tail = n;
    }

    return 0;
}


/* adding like a queue fashion. Adding new node to the tail of the list
 */
int8_t list_delete_node(struct list *l, struct node *n)
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
                    .  HEAD .                         . TAIL  . 
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
                if(l->head == l->tail){ // only one element in list
                    l->tail   = NULL;
                    l->head   = NULL;
                }else{                  // more than one element in list
                    l->head = l->head->next;
                    l->head->prev = NULL;
                }
            }else if(d == l->tail){     
                l->tail = l->tail->prev;
                l->tail->next = NULL;
            }else{
                n1 = d->prev;
                n2 = d->next;
                n1->next = n2;
                n2->prev = n1;
            }

            LFREE(d);
            d = NULL;
            n = NULL;
        }

        itr = itr->next;
    }

    return 0;
}



