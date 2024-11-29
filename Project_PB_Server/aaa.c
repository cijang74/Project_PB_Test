#include <stdio.h>
#include <stdlib.h>
#include "event.h"

#define EVENT_SIZE 20108 // 구조체 크기 계산에 따라 설정

int main() {
    FILE *fp;
    struct event ev;

    if ((fp = fopen("eventDex", "rb")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while (fread(&ev, EVENT_SIZE, 1, fp) == 1) {
        printf("Event ID: %d\n", ev.event_id);
        printf("Choice Num: %d\n", ev.choice_num);
        printf("Story: %s\n", ev.story);
        printf("Choice 1: %s -> Result: %s\n", ev.select_1.choice, ev.select_1.result);
        printf("Prices: %d %d %d %d %d", ev.select_1.prices.HP, ev.select_1.prices.AP, ev.select_1.prices.DP, ev.select_1.prices.SP, ev.select_1.prices.skill);
        // 필요에 따라 추가 선택지 출력 가능
        index++;
    }

    fclose(fp);
    return 0;
}
