#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "event.h"
#include "player.h"
#define TOTAL_GROWING_DATE 4

// 성장 씬 함수 
struct player *shmaddr;

void add_skill(int playerID, struct price add)
{
    struct monsterSkill *rec = &shmaddr[playerID].selectedMonster.skills;
    if (rec->skill_2_ID = -1) rec->skill_2_ID = add.skill;
    else if (rec->skill_3_ID = -1) rec->skill_3_ID = add.skill;
    else if (rec->skill_4_ID = -1) rec->skill_4_ID = add.skill;
}

void add_price(int playerID, struct price add)      //보상 추가
{
    if(add.skill != -1)
    {
        add_skill(playerID, add);
        return;
    }
    struct monsterStats *rec = &shmaddr[playerID].selectedMonster.stats;
    rec->attackPower += add.AP;
    rec->defensePower += add.DP;
    rec->HP += add.HP;
    rec->speed += add.SP;
}

struct event scan_event(FILE* fp, int target_eid)
{
    struct event rec;

    int eid = -1;

    char* prices;
    int n[5];
    int count = 0;
    int lineCount = 0;
    char line[MAX_STORY_LENGTH];

    while (fgets(line, MAX_STORY_LENGTH, fp) != NULL) {
        if(strcmp(line, "\r\n") == 0) 
        {
            eid++;
            if (eid == target_eid) break;
        }
        memset(line, 0, sizeof(line));
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if(strcmp(line, "\r\n") == 0)
        {
            rec.choice_num = (lineCount - 1) / 3;
            return rec;
        }
        if(lineCount == 0)
        {
            rec.event_id = eid;
            strcpy(rec.story, line);
        }
        else if(lineCount == 1) strcpy(rec.select_1.choice, line);
        else if(lineCount == 2) strcpy(rec.select_1.result, line);
        else if(lineCount == 3)
        {
            prices = strtok(line, " ");
            while(prices != NULL)
            {
                n[count++] = atoi(prices);
                prices = strtok(NULL, " ");
            }
            rec.select_1.prices.HP = n[0];
            rec.select_1.prices.AP = n[1];
            rec.select_1.prices.DP = n[2];
            rec.select_1.prices.SP = n[3];
            rec.select_1.prices.skill = n[4];
        }

        else if(lineCount == 4) strcpy(rec.select_2.choice, line);
        else if(lineCount == 5) strcpy(rec.select_2.result, line);
        else if(lineCount == 6)
        {
            prices = strtok(line, " ");
            while(prices != NULL)
            {
                n[count++] = atoi(prices);
                prices = strtok(NULL, " ");
            }
            rec.select_2.prices.HP = n[0];
            rec.select_2.prices.AP = n[1];
            rec.select_2.prices.DP = n[2];
            rec.select_2.prices.SP = n[3];
            rec.select_2.prices.skill = n[4];
        }

        else if(lineCount == 7) strcpy(rec.select_3.choice, line);
        else if(lineCount == 8) strcpy(rec.select_3.result, line);
        else if(lineCount == 9)
        {
            prices = strtok(line, " ");
            while(prices != NULL)
            {
                n[count++] = atoi(prices);
                prices = strtok(NULL, " ");
            }
            rec.select_3.prices.HP = n[0];
            rec.select_3.prices.AP = n[1];
            rec.select_3.prices.DP = n[2];
            rec.select_3.prices.SP = n[3];
            rec.select_3.prices.skill = n[4];
        }

        else if(lineCount == 10) strcpy(rec.select_4.choice, line);
        else if(lineCount == 11) strcpy(rec.select_4.result, line);
        else if(lineCount == 12)
        {
            prices = strtok(line, " ");
            while(prices != NULL)
            {
                n[count++] = atoi(prices);
                prices = strtok(NULL, " ");
            }
            rec.select_4.prices.HP = n[0];
            rec.select_4.prices.AP = n[1];
            rec.select_4.prices.DP = n[2];
            rec.select_4.prices.SP = n[3];
            rec.select_4.prices.skill = n[4];
        }
        
        else if(lineCount == 13) strcpy(rec.select_5.choice, line);
        else if(lineCount == 14) strcpy(rec.select_5.result, line);
        else if(lineCount == 15)
        {
            prices = strtok(line, " ");
            while(prices != NULL)
            {
                n[count++] = atoi(prices);
                prices = strtok(NULL, " ");
            }
            rec.select_5.prices.HP = n[0];
            rec.select_5.prices.AP = n[1];
            rec.select_5.prices.DP = n[2];
            rec.select_5.prices.SP = n[3];
            rec.select_5.prices.skill = n[4];
        }

        count = 0;
        lineCount++;

        memset(line, 0, sizeof(line));
        printf("%s", line);
    }
}

void trigger_event(FILE* fp, int playerID, int eid)       
{
    struct event rec = scan_event(fp, eid);
    int selected;

    fseek(fp, eid * sizeof(rec), SEEK_SET);
    fread(&rec, sizeof(rec),  1,  fp);
    printf("%s\n", rec.story);

    for(int i = 0; i < rec.choice_num; i++)
    {
        if(i == 0) printf("%s\n", rec.select_1.choice);
        else if(i == 1) printf("%s\n", rec.select_2.choice);
        else if(i == 2) printf("%s\n", rec.select_3.choice);
        else if(i == 3) printf("%s\n", rec.select_4.choice);
        else if(i == 4) printf("%s\n", rec.select_5.choice);
    }

    printf("원하는 선택지를 고르세요(1 ~ %d) : ", rec.choice_num);
    scanf("%d", &selected);
    if(selected == 1) 
    {
        printf("%s\n", rec.select_1.result);
        add_price(playerID, rec.select_1.prices);
    }
    else if(selected == 2) 
    {
        printf("%s\n", rec.select_2.result);
        add_price(playerID, rec.select_2.prices);
    }
    else if(selected == 3)
    {
        printf("%s\n", rec.select_3.result);
        add_price(playerID, rec.select_3.prices);
    }
    else if(selected == 4)
    {
        printf("%s\n", rec.select_1.result);
        add_price(playerID, rec.select_4.prices);
    }
    else if(selected == 5)
    {
        printf("%s\n", rec.select_1.result);
        add_price(playerID, rec.select_5.prices);
    }
}

void* make_shared_memory()          //공유 메모리 생성 및 연결 
{
    int shmid;
    key_t key;

    key = ftok("main", 10597);
    shmid = shmget(key, sizeof(struct player) * 4, 0);
    if(shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    printf("shmid : %d", shmid);
    shmaddr = (struct player*)shmat(shmid, NULL, 0);
}

int main(int argc, char* argv[])
{
    int eid[TOTAL_GROWING_DATE];
    int specialEventCount = 0;
    int receivedPlayerID = atoi(argv[1]);
    
    FILE* fp;

    if ((fp = fopen("eventDex.txt", "r")) == NULL ) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(1);
    }

     make_shared_memory();

    for(int i = 0; i < TOTAL_GROWING_DATE; i++)
    {
        eid[i] = rand() % MAX_NORMALEVENT_NUM;
        /*
        for(int j = 0; j < i; j++)
        {
            if(eid[i] == eid[j]) 
            {
                if(specialEventCount < 4) eid[i] = MAX_NORMALEVENT_NUM + ++specialEventCount;      //같은 이벤트가 나오면 스페셜 이벤트로 전환(최대 7회)
            }
        }
        */
        
        trigger_event(fp, receivedPlayerID, eid[i]);
    }


}