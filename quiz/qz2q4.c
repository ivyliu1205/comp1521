#include <stdio.h>

int main (){
    int x = 5, *z = &x;
    *z = *z + 3;
    z++;
    x++;
    printf ("x: %d\n",x);
}
