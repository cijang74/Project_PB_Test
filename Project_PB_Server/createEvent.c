#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#define START_EID 0

// 이벤트 생성하는 코드 
int scan_event(FILE* fp)
{
    struct event rec;

    printf("이벤트 ID : ");
    scanf("%d", &rec.event_id);
    while(getchar() != '\n');       //버퍼 비우기

    printf("이벤트 스토리 입력\n");
    if(fgets(rec.story, sizeof(rec.story), stdin) != NULL)
    {
        size_t len = strlen(rec.story);
        if(len > 0 && rec.story[len - 1] == '\n') rec.story[len - 1] = '\0';        //입력 받을 때 줄 바꿈까지 입력 받으므로 줄 바꿈 제거하고 저장
    }

    printf("선택지 개수 입력 : ");
    scanf("%d", &rec.choice_num);
    while(getchar() != '\n');

    for(int i = 1; i <= rec.choice_num; i++)        //선택지 및 보상 입력
    {
        if(i == 1)
        {
            printf("선택지 %d 스토리 입력\n", i);
            if(fgets(rec.select_1.choice, sizeof(rec.select_1.choice), stdin) != NULL)
            {
                size_t len = strlen(rec.select_1.choice);
                if(len > 0 && rec.select_1.choice[len - 1] == '\n') rec.select_1.choice[len - 1] = '\0';
            }
            printf("선택지 %d 결과 입력\n", i);
            if(fgets(rec.select_1.result, sizeof(rec.select_1.result), stdin) != NULL)
            {
                size_t len = strlen(rec.select_1.result);
                if(len > 0 && rec.select_1.result[len - 1] == '\n') rec.select_1.result[len - 1] = '\0';
            }
            printf("선택지 %d 보상 입력\n", i);
            printf("exp  HP  공격력  방어력  속도  스킬id(얻는 스킬이 없는 경우 -1)\n");
            if(scanf("%d %d %d %d %d %d", &rec.select_1.prices.exp, &rec.select_1.prices.HP, &rec.select_1.prices.AP, 
                                        &rec.select_1.prices.DP, &rec.select_1.prices.SP, &rec.select_1.prices.skill) != 6) return 0;
            while(getchar() != '\n');
        }

        else if(i == 2)
        {
            printf("선택지 %d 스토리 입력\n", i);
            if(fgets(rec.select_2.choice, sizeof(rec.select_2.choice), stdin) != NULL)
            {
                size_t len = strlen(rec.select_2.choice);
                if(len > 0 && rec.select_2.choice[len - 1] == '\n') rec.select_2.choice[len - 1] = '\0';
            }
            printf("선택지 %d 결과 입력\n", i);
            if(fgets(rec.select_2.result, sizeof(rec.select_2.result), stdin) != NULL)
            {
                size_t len = strlen(rec.select_2.result);
                if(len > 0 && rec.select_2.result[len - 1] == '\n') rec.select_2.result[len - 1] = '\0';
            }
            printf("선택지 %d 보상 입력\n", i);
            printf("exp  HP  공격력  방어력  속도  스킬id(얻는 스킬이 없는 경우 -1)\n");
            if(scanf("%d %d %d %d %d %d", &rec.select_2.prices.exp, &rec.select_2.prices.HP, &rec.select_2.prices.AP, 
                                        &rec.select_2.prices.DP, &rec.select_2.prices.SP, &rec.select_2.prices.skill) != 6) return 0;
            while(getchar() != '\n');
        }
        
        else if(i == 3)
        {
            printf("선택지 %d 스토리 입력\n", i);
            if(fgets(rec.select_3.choice, sizeof(rec.select_3.choice), stdin) != NULL)
            {
                size_t len = strlen(rec.select_3.choice);
                if(len > 0 && rec.select_3.choice[len - 1] == '\n') rec.select_3.choice[len - 1] = '\0';
            }
            printf("선택지 %d 결과 입력\n", i);
            if(fgets(rec.select_3.result, sizeof(rec.select_3.result), stdin) != NULL)
            {
                size_t len = strlen(rec.select_3.result);
                if(len > 0 && rec.select_3.result[len - 1] == '\n') rec.select_3.result[len - 1] = '\0';
            }
            printf("선택지 %d 보상 입력\n", i);
            printf("exp  HP  공격력  방어력  속도  스킬id(얻는 스킬이 없는 경우 -1)\n");
            if(scanf("%d %d %d %d %d %d", &rec.select_3.prices.exp, &rec.select_3.prices.HP, &rec.select_3.prices.AP, 
                                        &rec.select_3.prices.DP, &rec.select_3.prices.SP, &rec.select_3.prices.skill) != 6) return 0;
            while(getchar() != '\n');
        }

        else if(i == 4)
        {
            printf("선택지 %d 스토리 입력\n", i);
            if(fgets(rec.select_4.choice, sizeof(rec.select_4.choice), stdin) != NULL)
            {
                size_t len = strlen(rec.select_4.choice);
                if(len > 0 && rec.select_4.choice[len - 1] == '\n') rec.select_4.choice[len - 1] = '\0';
            }
            printf("선택지 %d 결과 입력\n", i);
            if(fgets(rec.select_4.result, sizeof(rec.select_4.result), stdin) != NULL)
            {
                size_t len = strlen(rec.select_4.result);
                if(len > 0 && rec.select_4.result[len - 1] == '\n') rec.select_4.result[len - 1] = '\0';
            }
            printf("선택지 %d 보상 입력\n", i);
            printf("exp  HP  공격력  방어력  속도  스킬id(얻는 스킬이 없는 경우 -1)\n");
            if(scanf("%d %d %d %d %d %d", &rec.select_4.prices.exp, &rec.select_4.prices.HP, &rec.select_4.prices.AP, 
                                        &rec.select_4.prices.DP, &rec.select_4.prices.SP, &rec.select_4.prices.skill) != 6) return 0;
            while(getchar() != '\n');
        }

        else if(i == 5)
        {
            printf("선택지 %d 스토리 입력\n", i);
            if(fgets(rec.select_5.choice, sizeof(rec.select_5.choice), stdin) != NULL)
            {
                size_t len = strlen(rec.select_5.choice);
                if(len > 0 && rec.select_5.choice[len - 1] == '\n') rec.select_5.choice[len - 1] = '\0';
            }
            printf("선택지 %d 결과 입력\n", i);
            if(fgets(rec.select_5.result, sizeof(rec.select_5.result), stdin) != NULL)
            {
                size_t len = strlen(rec.select_5.result);
                if(len > 0 && rec.select_5.result[len - 1] == '\n') rec.select_5.result[len - 1] = '\0';
            }
            printf("선택지 %d 보상 입력\n", i);
            printf("exp  HP  공격력  방어력  속도  스킬id(얻는 스킬이 없는 경우 -1)\n");
            if(scanf("%d %d %d %d %d %d", &rec.select_5.prices.exp, &rec.select_5.prices.HP, &rec.select_5.prices.AP, 
                                        &rec.select_5.prices.DP, &rec.select_5.prices.SP, &rec.select_5.prices.skill) != 6) return 0;
            while(getchar() != '\n');
        }
    }
    fseek(fp, rec.event_id * sizeof(rec), SEEK_SET);
    fwrite(&rec, sizeof(rec), 1, fp);

    return 1;
}

int main(int argc, char *argv[])
{
    char c;

    FILE *fp;

    if ((fp = fopen("eventDex", "ab")) == NULL ) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(1);
    }


    do{
        if(scan_event(fp) == 0) break;
        
        printf("계속하겠습니까? (Y/N)");
		scanf(" %c", &c);
    } while(c == 'Y');
}