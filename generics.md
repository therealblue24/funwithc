# Generics in C
## NOTE
This "solution" of generics in C will reduce type checking.
## Overview
For each struct you have put a member in it called `_start` like this:
```c
struct mystruct {
    short _start;
    int blah;
    long more_blah;
};
```
Then in the struct creation function set the _start value to a unique id for the struct:
```c
struct mystruct new() {
    struct mystruct ret = (struct mystruct){
        ._start = 1 /* unique id */,
        .blah = 5,
        .more_blah = 59023
    };
    return ret;
}
```
Then make your generic function using void pointers.
### Wait, What?
C, in C void pointers can turn into any real type--why this happens I don't know, but C++ doesn't implement this. 
Let's take this code:
```c
int *mydata = malloc(sizeof(int) * 5);
```
Let's pause. You may have asked once in your C programming lifetime why malloc can just adjust to any pointer type. That's because C has a builtin weapon-*i mean* generic type- `void`. Void by itself isn't generic, it means nothing, but `void*` is where things get real spicy. `void*` is a raw pointer with a weak type, and can be adjusted to any pointer.

### Why adjusted to any pointer?
Because the CPU doesn't know what typed pointers really are. Pointers (to put it simply): are just pieces of memory that point to memory. `void*` is just exactly that, as well as `int*`, `short*`, etc. All types of single-pointers are the same to the CPU-it's just that those typed pointers are there for type checking. So, C just straight up allows you to convert any typed pointer into a `void*` pointer. This can be abused in the wrong or right ways.

## So Let's do it
You can structure the generic function like this:
```c
void something(void *in) {
    if((*(struct mystruct*)in)._start == 1) {
        // handle struct mystruct
    } else if((*(struct mystruct2*)in)._start == 2) {
        // handle struct mystruct2
    }
    // blah
}
```
You may be wondering why these if statements look so ugly. Let's break it down:

### `(*(type*)val)`
This is simply a void pointer cast to another type cast. Except that there's an extra `*` to derefrence the type from a pointer to value. This is because we are storing the structs on stack (for demo.) For heap values, remove the extra derefrence.
### Why do we need to cast from `void*`?
Because the compiler doesn't know which struct fields are in a `void*`. Struct fields are abstractions to us humans.
## The Rest is obvious
The access to the field `_start` is the access to the ID of struct: which is our entrypoint to all of this. The rest is obvious.

## Wait! This isn't flexible!
And it isn't flexible. That's the point. Templates are abstractions (which can go real bad), and this isn't the best soloution in C for them. The other soloution abuses something called: macros.
