#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

void insertBinary(struct event rec, FILE* fpb)
{
    fseek(fpb, rec.event_id * sizeof(rec), SEEK_SET);
    fwrite(&rec, sizeof(rec), 1, fpb);
}

int main()
{
    FILE *fpt, *fpb;
    char line[MAX_STORY_LENGTH];
    int eid = -1;
    int lineCount = 0;
    char *prices;
    int n[5];
    int count = 0;

    struct event rec;

    if((fpt = fopen("eventDex.txt", "r")) == NULL)
    {
        perror("fopen");
        exit(1);
    }
    if((fpb = fopen("eventDex", "wb")) == NULL)
    {
        perror("fopen");
        exit(2);
    }


    while (fgets(line, sizeof(line), fpt) != NULL)
    {
        if(strcmp(line, "\r\n") == 0)
        {
            if(eid != -1)
            {
                rec.event_id = eid;
                rec.choice_num = (lineCount - 1) / 3;
                insertBinary(rec, fpb);

                lineCount = 0;
            }
            eid++;
        }
        else if(eid != -1)      //첫 줄 제외
        {
            if(lineCount == 0)
            {
                rec.event_id = eid;
                strcpy(rec.story, line);
                
            }
            else if(lineCount == 1)
            {
                strcpy(rec.select_1.choice, line);
            }
            else if(lineCount == 2)
            {
                strcpy(rec.select_1.result, line);
            }
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

            else if(lineCount == 4)
            {
                strcpy(rec.select_2.choice, line);
            }
            else if(lineCount == 5)
            {
                strcpy(rec.select_2.result, line);
            }
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

            else if(lineCount == 7)
            {
                strcpy(rec.select_3.choice, line);
            }
            else if(lineCount == 8)
            {
                strcpy(rec.select_3.result, line);
            }
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

            else if(lineCount == 10)
            {
                strcpy(rec.select_4.choice, line);
            }
            else if(lineCount == 11)
            {
                strcpy(rec.select_4.result, line);
            }
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
            
            else if(lineCount == 13)
            {
                strcpy(rec.select_5.choice, line);
            }
            else if(lineCount == 14)
            {
                strcpy(rec.select_5.result, line);
            }
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
        }
        memset(line, 0, sizeof(line));
    }
    return 0;
}