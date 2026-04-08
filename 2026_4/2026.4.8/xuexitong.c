#include <stdio.h>

int prime(int m) {
    if (m <= 1) return 0;
    for (int i = 2; i * i <= m; i++) {
        if (m % i == 0) return 0;
    }
    return 1;
}

int main() {
    int count = 0;
    for (int i = 2; i <= 100; i++) {
        if (prime(i)) {
            printf("%6d", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    return 0;
}