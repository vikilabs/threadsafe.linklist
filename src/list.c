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
#include <pthread.h>
#include "list.h"
#include "lalloc.h"

static void list_lock(struct list *l)
{
    pthread_mutex_lock(l->lock);
}

static void list_unlock(struct list *l)
{
    pthread_mutex_unlock(l->lock);
}


struct list *list_init()
{
    struct list *l = NULL;
    l = (struct list *) lalloc(sizeof(struct list));
    
    if(!l){
        printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
    }else{
        l->head = NULL;
        l->tail = NULL;
        l->lock = (pthread_mutex_t *) lalloc(sizeof(pthread_mutex_t));
        l->node_count = 0;
        
        if(!l->lock){
            printf("( error ) OOM ( %s : %d )\n", __func__, __LINE__);
            lfree(l);
            return NULL;
        }
        
        pthread_mutex_init(l->lock, NULL);
        l->active = 1;
    }

    return l;
}

int8_t list_terminate(struct list *l)
{
    struct node *itr=NULL, *d=NULL;

    assert( l != NULL);
    
   
    list_lock(l);
    l->active = 0;

    itr = l->head;
    l->head = NULL;
    l->tail = NULL;

    while(itr){
        d = itr;
        itr = itr->next;
        l->node_count -= 1;
        LFREE(d);
    }
    
    list_unlock(l);
    
    pthread_mutex_destroy(l->lock);
    lfree(l->lock);
    return 0;
}

struct node *list_create_node(void *data, size_t data_size)
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

    list_lock(l);
 
    if(!l->active){
        list_unlock(l);
        return -1;
    }
   
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
    
    l->node_count += 1;
    
    list_unlock(l);

    return 0;
}


/* adding like a queue fashion. Adding new node to the tail of the list
 */
int8_t list_delete_node(struct list *l, struct node *n)
{
    struct node *d=NULL, *itr=NULL;
    struct node *n1 = NULL, *n2=NULL;

    assert( l != NULL);
    
    list_lock(l);

    if(!l->active){
        list_unlock(l);
        return -1;
    }
 
    if(n == NULL){
        n = l->tail; /* Delete Tail if argument is NULL*/
        itr = l->tail;
    }else{
        itr = l->head;
    }

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
            
            l->node_count -= 1;

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
            LFREE(d->data);
            LFREE(d);
            d = NULL;
            n = NULL;
        }

        itr = itr->next;
    }
    
    list_unlock(l);

    return 0;
}

int get_nodes_count(struct list *l)
{
    int c = 0;

    list_lock(l);
    c = l->node_count; 
    list_unlock(l);
    
    return c;
}

void traverse_list(struct list *l)
{
    struct node *itr;
    assert(l);
    
    list_lock(l);
 
    if(!l->active){
        list_unlock(l);
        return;
    }
    
    itr = l->head;
    printf("[ list ]");
    while(itr){
        printf("[ %d ]->", *((int*)itr->data));
        itr = itr->next;
    }
    printf("\n");
    list_unlock(l);
}

