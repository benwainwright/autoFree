typedef enum AUTOFREE_STATUS {
   FINISH   = 0,
   CONTINUE = 1
} autoFreeStatus_t;

autoFreeStatus_t startAutoFree( );
autoFreeStatus_t endAutoFree( );

#define AUTOFREE                                                 \
   for( int _iAutoFree = 0;                                      \
        ( _iAutoFree < 1 && startAutoFree( ) ) || endAutoFree(); \
        _iAutoFree++)

