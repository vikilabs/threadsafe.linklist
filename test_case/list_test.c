#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "test_util.h"
#include "alloc_util.h"

typedef void (*testcase_t) (void);

void list_test1_create_list()
{
    struct list *l = list_create();


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
    
    n = create_node(&i, sizeof(int));

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

    n = create_node(NULL, sizeof(int));

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

    n = create_node(&i, 0);

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


void list_test1_add_one_element()
{
    struct list *l = list_create();

    if(l==NULL){
        TEST_FAIL("");
    }else{
        TEST_PASS("");
    }

    //list_add(l, );
 
}


int main()
{
    int i = 0;
    testcase_t testcases[] = {
        list_test1_create_node,
        list_test1_create_list,
        NULL
    };
    
    while(testcases[i] != NULL){
        testcases[i](); 
        i++;
    }



    return 0;
}
