# Autofree

This library was written by me as part of the C Programming unit at Bristol University. It is designed to simplify the process of managing memory in C.

Calls to `malloc()` are replaced via the C Preprocessor by a function that calls `malloc()`, then adds the memory address to an internal data structure.

This data structure is initialised with a call to `newHeapList()` and is series of linked lists which are each chained together by their initial node. This way, every call to `malloc()` adds a pointer to the most recent chain, which can then be iterated and deallocated using `freeHeapList()`. In order to simplify this process further, `newHeapList()` and `freeHeapList()` can be implicitly called using a `AUTOFREE` block as shown below:

```
int main()
{
   AUTOFREE {
      char* foo = malloc(20);
      char* bar = malloc(25);
   }
}
```
In the above example, `foo` and `bar` will be automatically deallocated when the containing `AUTOFREE` block exits.

It should be noted that this library does NOT at this stage handle calls to `reallocate()`
