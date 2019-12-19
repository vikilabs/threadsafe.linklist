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
    struct node *n = NULL;

    if(l==NULL){
        TEST_FAIL("list should not be null");
    }else{
        TEST_PASS("list should not be null");
    }

    //first element
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

    if( *( (int *) l->head->data ) == 2 ){
        TEST_PASS("list first element added properly");
    }else{
        TEST_FAIL("list first element not added properly");
    }

    //second element
    i = 4;
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

    if( *( (int *) l->head->prev->data ) == 4 ){
        TEST_PASS("list second element added properly");
    }else{
        TEST_FAIL("list second element not added properly");
    }

    //third element
    i = 6;
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

    if( *( (int *) l->head->prev->prev->data ) == 6 ){
        TEST_PASS("list third element added properly");
    }else{
        TEST_FAIL("list third element not added properly");
    }

    //fourth element
    i = 8;
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

    if( *( (int *) l->head->prev->prev->prev->data ) == 8 ){
        TEST_PASS("list fourth element added properly");
    }else{
        TEST_FAIL("list fourth element not added properly");
    }

}


int main()
{
    int i = 0;
    testcase_t testcases[] = {
        list_test1_create_node,
        list_test1_create_list,
        list_test1_add_element,
        NULL
    };
    
    while(testcases[i] != NULL){
        testcases[i](); 
        i++;
    }



    return 0;
}
