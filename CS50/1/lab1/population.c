#include <cs50.h>
#include <stdio.h>

int main(void) {
    int startSize, endSize, numYears = 0, llamasBorn, llamasDied;

    do {
        printf("Start size: ");
        scanf("%i", &startSize);
    } while (startSize < 9);

    do {
        printf("End size: ");
        scanf("%i", &endSize);
    } while (endSize < startSize);

    while (startSize < endSize) {
        llamasBorn = startSize / 3;
        llamasDied = startSize / 4;
        startSize += (llamasBorn - llamasDied);
        numYears++;
    }

    printf("Years: %i\n", numYears);
}
