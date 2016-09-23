#include <stdio.h>

#define DONT_REPLACE_MALLOC
#include "autoFree.h"

typedef struct pointerList {
  void* pnt;
  struct pointerList* lastList;
  struct pointerList* prev;
} heapList_t;

/*********************************************************
/***************** Private Declarations ******************
/*********************************************************/

heapList_t*  newHeapListNode( heapList_t* prev );
heapList_t** getHeapListPtr( void );
heapList_t*  getHeapList( void );
heapList_t** toHeapListAndReturnList( void* pnt );

/*********************************************************
/***************** Function Definitions ******************
/*********************************************************/

autoFreeStatus_t startAutoFree( )
{
   newHeapList( );
   return CONTINUE;
}

autoFreeStatus_t endAutoFree( )
{
   freeHeapList( );
   return FINISH;
}


heapList_t** toHeapListAndReturnList( void* pnt )
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

void toHeapList( void* pnt )
{
   toHeapListAndReturnList( pnt );
}

heapList_t* newHeapListNode( heapList_t* prev )
{
   heapList_t* newNode = (heapList_t*)allocOffList( sizeof( heapList_t ) );
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
   heapList_t*  newTop = (heapList_t*)allocOffList( sizeof( heapList_t ) );

   newTop->pnt      = NULL;
   newTop->prev     = NULL;
   newTop->lastList = *top;
   *top             = newTop;
}

heapList_t* getHeapList( void )
{
   heapList_t** list = toHeapListAndReturnList( NULL );
   return *list;
}

heapList_t** getHeapListPtr( void )
{
   heapList_t** list = toHeapListAndReturnList( NULL );
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

void* allocate( size_t size )
{
   void* returnVal = allocOffList( size );
   toHeapList( returnVal );
   return returnVal;
}

void* callocate( size_t num, size_t size )
{
   void* returnVal = callocOffList( num, size );
   toHeapList( returnVal );
   return returnVal;
}


void* callocOffList(size_t num, size_t size)
{
   void* returnVal = NULL;
   if( ( returnVal = calloc( num, size ) ) == NULL ) {
      fprintf( stderr, "%s", "Failed to allocate memory" );
      exit( 1 );
   }
   return returnVal;
}

void* allocOffList(size_t size)
{
   void* returnVal = NULL;
   if((returnVal = malloc(size)) == NULL) {
      fprintf( stderr, "%s", "Failed to allocate memory" );
      exit( 1 );
   }
   return returnVal;
}
