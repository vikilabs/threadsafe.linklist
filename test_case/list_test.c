#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "test_util.h"
#include "alloc_util.h"

typedef void (*testcase_t) (void);

void list_test1_create_list()
{
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

    SAFE_FREE(l);
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

    SAFE_FREE(n);

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

    SAFE_FREE(n);

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
    
    SAFE_FREE(n);

}


void list_test1_add_element()
{
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

    if( (*( (int *) l->head->data ) == 2 ) &&\
          ( l->head->next  == NULL ) &&\
          ( l->tail->prev  == NULL ))
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
          (*( (int *) l->head->prev->data ) == 4 ) &&\
          ( l->head->next  == NULL ) &&\
          ( l->tail->prev  == NULL ))
    {
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

    if(   (*( (int *) l->head->data ) == 2 ) &&\
          (*( (int *) l->head->prev->data ) == 4 ) &&\
          (*( (int *) l->head->prev->prev->data ) == 6 ) &&\
          ( l->head->next  == NULL ) &&\
          ( l->tail->prev  == NULL ))
    {
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

    if(   (*( (int *) l->head->data ) == 2 ) &&\
          (*( (int *) l->head->prev->data ) == 4 ) &&\
          (*( (int *) l->head->prev->prev->data ) == 6 ) &&\
          (*( (int *) l->head->prev->prev->prev->data ) == 8 ) &&\
          ( l->head->next  == NULL ) &&\
          ( l->tail->prev  == NULL ))
    {
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }



}

void list_test1_delete_element()
{
    int i = 2;
    struct list *l = list_init();
    struct node *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL;

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

    if( *( (int *) l->head->prev->data ) == 4 ){
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

    if( *( (int *) l->head->prev->prev->data ) == 6 ){
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

    if( *( (int *) l->head->prev->prev->prev->data ) == 8 ){
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }


    //delete(6)        |   8 <-> 6 <-> 4 <-> 2

    if(list_delete_node(l, n3) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    if( (    *( (int *) l->head->data) == 2) \
        && ( *( (int *) l->head->prev->data) == 4) \
        && ( *( (int *) l->head->prev->prev->data) == 8) \
        && (            l->head->prev->prev->prev == NULL) \
        && (            l->head->next  == NULL) \
        && (            l->tail->prev  == NULL )){
        TEST_PASS("list third element(6) deleted properly");
    }else{
        TEST_FAIL("list third element(6) deleted properly");
    }

    
    //delete(2)        |   8 <-> 4 <-> 2
    
    if(list_delete_node(l, n1) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
    }

    if( (    *( (int *) l->head->data) == 4) \
        && ( *( (int *) l->head->prev->data) == 8) \
        && (            l->head->prev->prev == NULL) \
        && (            l->head->next  == NULL) \
        && (            l->tail->prev  == NULL )){
        TEST_PASS("list head element(2) deleted properly");
    }else{
        TEST_FAIL("list head element(2) deleted properly");
    }

    //delete(8)        |   8 <-> 4 
    if(list_delete_node(l, n4) == 0){
        TEST_PASS("list element deleted");
    }else{
        TEST_FAIL("list element not deleted");
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

    if( ( l->head  == NULL) &&\
        ( l->tail  == NULL))
    {
        TEST_PASS("list last element deleted properly");
    }else{
        TEST_FAIL("list last element deleted properly");
    }


}


int main()
{
    int i = 0;
    testcase_t testcases[] = {
        list_test1_create_node,
        list_test1_create_list,
        list_test1_add_element,
        list_test1_delete_element,
        NULL
    };
    
    while(testcases[i] != NULL){
        testcases[i](); 
        i++;
    }



    return 0;
}
