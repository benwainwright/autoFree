#include <stdlib.h>

/**
 * This library allows automatic freeing of mallocs and callocs.
 * Heap pointers are stored using multiple linked list data
 * structures, all chained together on their initial node. Call
 * newHeapList() to initialise a new list. Allocate memory with
 * malloc() and calloc(). Once you are done, freeHeapList() will
 * free all memory allocated after the last call to newHeapList().
 *
 * To perform these function calls implicitly using blocks, use
 * AUTOFREE blocks (which can be nested) as shown below:
 * 
 * AUTOFREE {
 *   char* var1 malloc(20);
 *   char* var2 malloc(25);
 * }
 *
 * newHeapList() is automatically called at the start of the AUTOFREE
 * block. When it exits, freeHeapList() will be called, deallocating
 * both var1 and 2
 * 
 * @author Ben Wainwright
 * @date 2015/2016
 */ 
#include "autoFreeBlock.h"

/**
 * Initialise a new heaplist
 */
void newHeapList( void );

/**
 * Iterate the most recent heaplist, free all memory then
 * replace the internal 'current' pointer with the top of 
 * the previous list
 */
void freeHeapList( void );

/**
 * Allocates memory with malloc() and adds the address to
 * the current heaplist. This file includes #defines so that
 * calling this function directly is not necessary
 */
void* allocate( size_t size );

/**
 * Allocates memory with calloc() and adds the address to
 * the current heaplist. This file includes #defines so that
 * calling this function directly is not necessary
 */
void* callocate( size_t num, size_t size );

/**
 * Add a pointer to the heaplist. Only use this in combination with
 * the two 'offList' functions below'
 */
void toHeapList( void* pnt );

/**
 * Calls 'calloc()' without adding to the heaplist. Use this to perform
 * conditional heapList adds by performing tests and then using toHeapList() 
 * if the test is successfull
 */
void* callocOffList( size_t num, size_t size );

/**
 * Calls 'malloc()' without adding to the heaplist. Use this to perform
 * conditional heapList adds by performing tests and then using toHeapList()
 * if the test is successfull
 */
void* allocOffList( size_t size );

/**
 * Automatically replace all calls to malloc() and calloc()
 * with the above
 */
#ifndef DONT_REPLACE_MALLOC
#define malloc( size ) allocate( size )
#define calloc( size ) callocate( num, size )
#endif

