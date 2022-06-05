/*
Experiment to find out what happens when print's argument string contains \c,
where c is some character not listet above.
*/

#include <stdio.h>

int main(void) {
    printf("hello, ");
    printf("world");
    printf("\n");


   printf("Hallo %c\n");


}
