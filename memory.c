/*
 * Memory management Functions
 *
 * Used to store pointers to heap allocated memory in a
 * linked list and then free the entire list when needed.
 *
 * Updated for wordladder coursework; now allows multiple lists
 * to be created and freed on demand
 *
 * Author: Ben Wainwright
 * Date: October 2015
 *
 */

#include "memory.h"

#include <stdlib.h>
#include "utilities.h"


/* Private function declarations */
heapList_t*  newHeapListNode( heapList_t* prev );
heapList_t** getHeapListPtr( void );
heapList_t*  getHeapList( void );

/* Function definitions */
heapList_t** toHeapList( void* pnt )
{
   static heapList_t* current = NULL;
   heapList_t*        prev    = NULL;

   if(pnt != NULL) {
      prev         = current;
      current      = newHeapListNode( prev );
      current->pnt = pnt;
   }
   return &current;
}

heapList_t* newHeapListNode( heapList_t* prev )
{
   heapList_t* newNode = (heapList_t*)allocOfflist( sizeof( heapList_t ) );
   newNode->lastList   = NULL;
   newNode->prev       = prev;
   if(prev != NULL) {
      newNode->lastList = prev->lastList;
   }
   return newNode;
}

void newHeapList( void )
{
   heapList_t** top    = getHeapListPtr( );
   heapList_t*  newTop = (heapList_t*)allocOfflist( sizeof( heapList_t ) );

   newTop->pnt      = NULL;
   newTop->prev     = NULL;
   newTop->lastList = *top;
   *top             = newTop;
}

/* toHeapList with NULL gets the address of current heaplist top */
heapList_t* getHeapList( void )
{
   heapList_t** list = toHeapList( NULL );
   return *list;
}

heapList_t** getHeapListPtr( void )
{
   heapList_t** list = toHeapList( NULL );
   return list;
}

void freeHeapList( void )
{
   heapList_t** endPtr   = getHeapListPtr();
   heapList_t*  end      = *endPtr;
   heapList_t*  current  = NULL;
   heapList_t*  lastList = end->lastList;

   while( end->prev != NULL ) {
      current = end;
      if( end->pnt != NULL ) {
         free( end->pnt );
         end->pnt = NULL;
      }
      end = end->prev;
      free( current );
   }
   free( end->pnt );
   free( end );
   if( lastList != NULL ) {
      *endPtr = lastList;
   }
   else {
      *endPtr = NULL;
   }
}

void* allocate( int size )
{
   void* returnVal = allocOfflist( size );
   toHeapList( returnVal );
   return returnVal;
}

void* callocate( int num, int size )
{
   void* returnVal = callocOffList( num, size );
   toHeapList( returnVal );
   return returnVal;
}


void* callocOffList(int num, int size)
{
   void* returnVal = NULL;
   if( ( returnVal = calloc( num, size ) ) == NULL ) {
      die( "Failed to allocate memory" );
   }
   return returnVal;
}
