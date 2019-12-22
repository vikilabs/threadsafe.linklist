#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "test_util.h"
#include "lalloc.h"

#define HUNDRED_MS 100000

typedef void (*testcase_t) (void);

void list_test1_create_list()
{
    size_t start_mem = GetDynMemoryUsage();
    struct list *l = list_init();

    if(l==NULL){
        TEST_FAIL("list should not be NULL");
    }else{
        TEST_PASS("list should not be NULL");
    }

    if(l->head == NULL){
        TEST_PASS("head should be NULL");
    }else{
        TEST_FAIL("head should be NULL");
    }

    if(l->tail == NULL){
        TEST_PASS("tail should be NULL");
    }else{
        TEST_FAIL("tail should be NULL");
    }

    if( (start_mem + sizeof(struct list) + sizeof(pthread_mutex_t)) != GetDynMemoryUsage()){
        TEST_FAIL("struct list memory check");
    }else{
        TEST_PASS("struct list memory check");
    }

    LFREE(l);
}


void list_test1_create_node()
{
    int i = 0xFF;

    struct node *n = NULL;
    
    n = list_create_node(&i, sizeof(int));

    if(!n){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(*((int*)n->data) == 0xFF){
        TEST_PASS("node should store the data properly");
    }else{
        TEST_FAIL("node should store the data properly");
    }

    LFREE(n);

    n = list_create_node(NULL, sizeof(int));

    if(!n){
        TEST_FAIL("node should be created even if (data = NULL)");
    }else{
        TEST_PASS("node should be created even if (data = NULL)");
    }

    if(n->data == NULL){
        TEST_PASS("n->data should be NULL");
    }else{
        TEST_FAIL("n->data should be NULL");
    }

    LFREE(n);

    n = list_create_node(&i, 0);

    if(!n){
        TEST_FAIL("node should be created even if (data_size = 0)");
    }else{
        TEST_PASS("node should be created even if (data_size = 0)");
    }

    if(n->data == NULL){
        TEST_PASS("n->data should be NULL");
    }else{
        TEST_FAIL("n->data should be NULL");
    }
    
    LFREE(n);

}


void list_test1_add_element()
{
    size_t start_mem = 0;
    size_t calc_mem = 0;
    int i = 2;
    struct list *l = list_init();
    
    struct node *n1 = NULL;
    struct node *n2 = NULL;
    struct node *n3 = NULL;
    struct node *n4 = NULL;

    if(l==NULL){
        TEST_FAIL("list should not be null");
    }else{
        TEST_PASS("list should not be null");
    }

    start_mem = GetDynMemoryUsage();

    //first element
    n1 = list_create_node(&i, sizeof(int));

    calc_mem += sizeof(struct node) + sizeof(i) + start_mem;

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check");
    }else{
        TEST_PASS("struct list node memory check");
    }


    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(list_add_node(l, n1) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( (*( (int *) l->head->data ) == 2 ) &&\
          ( l->head->prev  == NULL ) &&\
          ( l->tail->next  == NULL ))
    {
        TEST_PASS("list first element added properly");
    }else{
        TEST_FAIL("list first element not added properly");
    }

    //second element
    i = 4;
    n2 = list_create_node(&i, sizeof(int));

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n2) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if(   (*( (int *) l->head->data ) == 2 ) &&\
          (*( (int *) l->head->next->data ) == 4 ) &&\
          ( l->head->prev  == NULL ) &&\
          ( l->tail->next  == NULL ))
    {
        TEST_PASS("list second element added properly");
    }else{
        TEST_FAIL("list second element not added properly");
    }

    calc_mem += sizeof(struct node) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check");
    }else{
        TEST_PASS("struct list node memory check");
    }

    //third element
    i = 6;
    n3 = list_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n3) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if(   (*( (int *) l->head->data ) == 2 ) &&\
          (*( (int *) l->head->next->data ) == 4 ) &&\
          (*( (int *) l->head->next->next->data ) == 6 ) &&\
          ( l->head->prev  == NULL ) &&\
          ( l->tail->next  == NULL ))
    {
        TEST_PASS("list third element added properly");
    }else{
        TEST_FAIL("list third element not added properly");
    }

    calc_mem += sizeof(struct node) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check");
    }else{
        TEST_PASS("struct list node memory check");
    }



    //fourth element
    i = 8;
    n4 = list_create_node(&i, sizeof(int));

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n4) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if(   (*( (int *) l->head->data ) == 2 ) &&\
          (*( (int *) l->head->next->data ) == 4 ) &&\
          (*( (int *) l->head->next->next->data ) == 6 ) &&\
          (*( (int *) l->head->next->next->next->data ) == 8 ) &&\
          ( l->head->prev  == NULL ) &&\
          ( l->tail->next  == NULL ))
    {
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }

    calc_mem += sizeof(struct node) + sizeof(i);

    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check");
    }else{
        TEST_PASS("struct list node memory check");
    }

}

void list_test1_delete_element()
{
    int i = 2;
    struct list *l = list_init();
    struct node *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL;
    size_t start_mem = 0;
    size_t calc_mem = 0;

    if(l==NULL){
        TEST_FAIL("list should not be null");
    }else{
        TEST_PASS("list should not be null");
    }

    //first element
    n1 = list_create_node(&i, sizeof(int));

    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(list_add_node(l, n1) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->data ) == 2 ){
        TEST_PASS("list first element added properly");
    }else{
        TEST_FAIL("list first element not added properly");
    }

    //second element
    i = 4;
    n2 = list_create_node(&i, sizeof(int));

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n2) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->next->data ) == 4 ){
        TEST_PASS("list second element added properly");
    }else{
        TEST_FAIL("list second element not added properly");
    }

    //third element
    i = 6;
    n3 = list_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n3) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->next->next->data ) == 6 ){
        TEST_PASS("list third element added properly");
    }else{
        TEST_FAIL("list third element not added properly");
    }

    //fourth element
    i = 8;
    n4 = list_create_node(NULL, 0);

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n4) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( l->head->next->next->next->data  == NULL ){
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }


    start_mem = GetDynMemoryUsage();
    
    //delete(6)        |   NULL <-> 6 <-> 4 <-> 2

    if(list_delete_node(l, n3) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    calc_mem = start_mem - (sizeof(struct node) + sizeof(int));
    
    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check after delete");
    }else{
        TEST_PASS("struct list node memory check after delete");
    }


    if( (    *( (int *) l->head->data) == 2) \
        && ( *( (int *) l->head->next->data) == 4) \
        && (  l->head->next->next->data == NULL ) \
        && (            l->head->next->next->next == NULL) \
        && (            l->head->prev  == NULL) \
        && (            l->tail->next  == NULL )){
        TEST_PASS("list third element(6) deleted properly");
    }else{
        TEST_FAIL("list third element(6) deleted properly");
    }

    
    //delete(2)        |   NULL <-> 4 <-> 2
    
    if(list_delete_node(l, n1) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    calc_mem -= (sizeof(struct node) + sizeof(int));
    
    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check after delete");
    }else{
        TEST_PASS("struct list node memory check after delete");
    }


    if( (    *( (int *) l->head->data) == 4) \
        &&( l->head->next->data == NULL) \
        && (            l->head->next->next == NULL) \
        && (            l->head->prev  == NULL) \
        && (            l->tail->next  == NULL )){
        TEST_PASS("list head element(2) deleted properly");
    }else{
        TEST_FAIL("list head element(2) deleted properly");
    }

    //delete(8)        |   NULL <-> 4 
    if(list_delete_node(l, n4) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    calc_mem -= sizeof(struct node); /*Deleting NULL data so no int addition*/
    
    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check after delete");
    }else{
        TEST_PASS("struct list node memory check after delete");
    }


    if( (    *( (int *) l->head->data) == 4) \
        && ( *( (int *) l->tail->data) == 4) \
        && (            l->head->next  == NULL) \
        && (            l->head->prev  == NULL) \
        && (            l->tail->next  == NULL) \
        && (            l->tail->prev  == NULL )){
        TEST_PASS("list third element deleted properly");
    }else{
        TEST_FAIL("list third element deleted properly");
    }

    //delete(4)        |   NULL <-> 4 <-> NULL
    if(list_delete_node(l, n2) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    calc_mem -= (sizeof(struct node) + sizeof(int));
    
    if(calc_mem != GetDynMemoryUsage()){
        TEST_FAIL("struct list node memory check after delete");
    }else{
        TEST_PASS("struct list node memory check after delete");
    }


    
    if( ( l->head  == NULL) &&\
        ( l->tail  == NULL))
    {
        TEST_PASS("list last element deleted properly");
    }else{
        TEST_FAIL("list last element deleted properly");
    }


}

void list_terminate_test()
{
    int i = 2;
    struct list *l = list_init();
    struct node *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL;

    struct rusage r_usage;

    if(l==NULL){
        TEST_FAIL("list should not be null");
    }else{
        TEST_PASS("list should not be null");
    }

    //first element
    n1 = list_create_node(&i, sizeof(int));

    if(!n1){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }


    if(list_add_node(l, n1) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->data ) == 2 ){
        TEST_PASS("list first element added properly");
    }else{
        TEST_FAIL("list first element not added properly");
    }

    //second element
    i = 4;
    n2 = list_create_node(&i, sizeof(int));

    if(!n2){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n2) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->next->data ) == 4 ){
        TEST_PASS("list second element added properly");
    }else{
        TEST_FAIL("list second element not added properly");
    }

    //third element
    i = 6;
    n3 = list_create_node(&i, sizeof(int));

    if(!n3){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n3) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->next->next->data ) == 6 ){
        TEST_PASS("list third element added properly");
    }else{
        TEST_FAIL("list third element not added properly");
    }

    //fourth element
    i = 8;
    n4 = list_create_node(&i, sizeof(int));

    if(!n4){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n4) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    if( *( (int *) l->head->next->next->next->data ) == 8 ){
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }

    if(list_terminate(l) == 0){
        TEST_PASS("list terminate");
    }else{
        TEST_FAIL("list terminate");
    }

}

void *th_create_n_add_node(void *args)
{
    int val = HUNDRED_MS * (rand()%7);
    usleep(val);

    int i = (int)GetDynMemoryUsage();
    struct list *l = (struct list *) args;
    struct node *n = NULL;
    n = list_create_node(&i, sizeof(int));

    if(!n){
        TEST_FAIL("node should not be NULL");
    }else{
        TEST_PASS("node should not be NULL");
    }

    if(list_add_node(l, n) == 0){
        TEST_PASS("list_add_node() success");
    }else{
        TEST_FAIL("list_add_node() success");
    }

    return NULL;
}

void *th_delete_node(void *args)
{
    int val = HUNDRED_MS * (rand()%7);
    usleep(val);

    struct list *l = (struct list *) args;
    if(list_delete_node(l, NULL) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }
    return NULL;
}

void list_test1_multithreaded()
{
    int i = 0;
    struct list *l = list_init();
    struct node *itr = NULL;
    pthread_t tid[100], dtid[100]; 

    for(i=0;i<100;i++){
        pthread_create(&tid[i], NULL, &th_create_n_add_node, (void *)l);
    }

    traverse_list(l);
    
    for(i=0;i<100;i++){
        pthread_join(tid[i], NULL);
    }

    traverse_list(l);
    
    if(get_nodes_count(l) != 100){
        TEST_FAIL("threaded list create");
    }else{
        TEST_PASS("threaded list create");
    }

    for(i=0;i<100;i++){
        pthread_create(&dtid[i], NULL, &th_delete_node, (void *)l);
    }
 
    traverse_list(l);
    
    for(i=0;i<100;i++){
        pthread_join(dtid[i], NULL);
    }
    
    traverse_list(l);


    if(get_nodes_count(l) != 0){
        TEST_FAIL("threaded list delete");
    }else{
        TEST_PASS("threaded list delete");
    }

}

void list_test2_multithreaded()
{
    int i = 0;
    struct list *l = list_init();
    struct node *itr = NULL;
    pthread_t tid[100], dtid[100]; 

    for(i=0;i<100;i++){
        pthread_create(&tid[i], NULL, &th_create_n_add_node, (void *)l);
        pthread_create(&dtid[i], NULL, &th_delete_node, (void *)l);
    }
    
    traverse_list(l);

    for(i=0;i<100;i++){
        pthread_join(dtid[i], NULL);
        pthread_join(tid[i], NULL);
    }


    traverse_list(l);
    list_terminate(l);
}



int main()
{
    int i = 0;
    testcase_t testcases[] = {
        list_test1_create_node,
        list_test1_create_list,
        list_test1_add_element,
        list_test1_delete_element,
        list_terminate_test,
        list_test1_multithreaded,
        list_test2_multithreaded, 
        NULL
    };
    
    while(testcases[i] != NULL){
        testcases[i](); 
        i++;
    }

    return 0;
}
