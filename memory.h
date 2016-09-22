#ifndef _MEMORY_
#define _MEMORY_

#include <stdio.h>

typedef struct pointerList {
  void* pnt;
  struct pointerList* lastList;
  struct pointerList* prev;
} heapList_t;

/* Create a NEW heaplist structure linked at the top
 * with the old one */
void newHeapList( void );

/* Free all the memory stored on a single heaplist
 * then move the static pointer to point to the previous
 * list */
void freeHeapList( void );

/* Wrappers for malloc() which test for NULL and implicitly
 * add the pointer to the heaplist */
void* allocate( int size );
void* callocate( int num, int size );

/* If you need to conditionally add to heaplist, use the
 * functions below to separate the two steps */
heapList_t** toHeapList( void* pnt );
void*        callocOffList( int num, int size );
void*        allocOfflist( int size );
void*        reallocate( void* ptr, size_t size );
#endif

#ifdef REPLACE_MALLOC
#define malloc(size) allocate(size)
#define calloc(num, size) callocate(num, size)
#endif
