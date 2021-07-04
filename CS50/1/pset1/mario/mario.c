#include <stdio.h>

int main(void) {
    int height;
    do {
    printf("Height: ");
    scanf("%i", &height);
    } while (height < 1 || height > 20);

    for (int i = 1; i <= height; ++i) {
        for (int j = i; j < height; ++j) {
            putchar(' ');
        }

        for (int k = height-i; k < height; k++) {
            putchar('#');
        }

        printf("  ");

        for (int kk = height-i; kk < height; kk++) {
            putchar('#');
        }
        printf("\n");
    }
}
