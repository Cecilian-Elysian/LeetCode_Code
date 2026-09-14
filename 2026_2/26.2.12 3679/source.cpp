#include <stdio.h>
#include <stdlib.h>

int minArrivalsToDiscard(int* arrivals, int arrivalsSize, int w, int m) {
    int* kept = (int*)calloc(arrivalsSize, sizeof(int));
    int* cnt = (int*)calloc(100001, sizeof(int));
    int* queue = (int*)malloc(arrivalsSize * sizeof(int));
    int head = 0, tail = 0;
    int discarded = 0;

    for (int i = 0; i < arrivalsSize; i++) {
        while (head < tail && queue[head] < i - w + 1) {
            cnt[arrivals[queue[head]]]--;
            head++;
        }
        if (cnt[arrivals[i]] >= m) {
            discarded++;
        } else {
            cnt[arrivals[i]]++;
            queue[tail++] = i;
        }
    }
    free(kept);
    free(cnt);
    free(queue);
    return discarded;
}

int main() {
    int a1[] = {1, 2, 1, 3, 1};
    printf("%d\n", minArrivalsToDiscard(a1, 5, 4, 2));
    int a2[] = {1, 2, 3, 3, 3, 4};
    printf("%d\n", minArrivalsToDiscard(a2, 6, 3, 2));
    return 0;
}
