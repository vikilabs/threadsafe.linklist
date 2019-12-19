/* This code is free ( free means free, Do whatever useful )
 *
 *      Author : Viki (a) Vignesh Natarajan
 *      Lab    : vikilabs.org   
 */
#ifndef ALLOC_UTIL_H
#define ALLOC_UTIL_H

#define SAFE_FREE(var){\
    if(var){\
        free(var);\
        var = NULL;\
    }\
}

#endif
