#include <stdio.h>

struct some_struct1 {
    short _start;
    int foo;
};

struct some_struct2 {
    short _start;
    int foo;
    long bar;
};

struct some_struct1 new_some_struct1(int foo)
{
    return (struct some_struct1){ ._start = 1, .foo = foo };
}

struct some_struct2 new_some_struct2(int foo, long bar)
{
    return (struct some_struct2){ ._start = 2, .foo = foo, .bar = bar };
}

void print_some_struct(void *data)
{
    if((*(struct some_struct1 *)data)._start == 1) {
        struct some_struct1 _copy = *(struct some_struct1 *)data;
        printf("some_struct1! foo=%d\n", _copy.foo);
    } else if((*(struct some_struct2 *)data)._start == 2) {
        struct some_struct2 _copy = *(struct some_struct2 *)data;
        printf("some_struct2! foo=%d bar=%ld\n", _copy.foo, _copy.bar);
    } else {
        printf("Unsupported\n");
    }
}

int main()
{
    struct some_struct1 s1 = new_some_struct1(5);
    struct some_struct2 s2 = new_some_struct2(5, 4);
    int unsupported_val = 5;
    print_some_struct(&s1);
    print_some_struct(&s2);
    print_some_struct(&unsupported_val);
}
