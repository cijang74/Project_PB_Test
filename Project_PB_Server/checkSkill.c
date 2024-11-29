#include <stdio.h>
#include <stdlib.h>
#include "skill.h" // 스킬 종류 구조체 저장된 헤더파일 

void check_attackSkill(FILE* fp, struct attackSkill rec_AS)
{
    // 공격 스킬의 정보 출력
    if (fread(&rec_AS,  sizeof(rec_AS),  1,  fp) > 0) 
    {
        printf("스킬 ID : %d  스킬이름 : %s  타입 : %s\n", rec_AS.sid, rec_AS.skill_name, "공격");
        printf("데미지 : %d  속성 : %s\n", rec_AS.skill_damage, rec_AS.property);
    }
}

void check_buffSkill(FILE* fp, struct buffSkill rec_BS)
{
    // 버프 스킬의 정보 출력
    if (fread(&rec_BS,  sizeof(rec_BS),  1,  fp) > 0) 
    {
        printf("스킬 ID : %d 이름 : %s 종류 : %s\n", rec_BS.sid, rec_BS.skill_name, "버프");

        // 버프 종류| 1: 공격력 2: 방어력 3: 공격력 + 방어력 4: 속도 5: 공격력 + 속도 6: 방어력 + 속도
        // 버프 종류| 7: 공격력 + 방어력 + 속도
        if(rec_BS.buff_type == 1) 
        {
            printf("버프 종류 : 공격력\n");
            printf("공격력 증가량 : %d", rec_BS.attack_up_value);
        }
        if(rec_BS.buff_type == 2)
        {
            printf("버프 종류 : 방어력\n");
            printf("방어력 증가량 : %d", rec_BS.defense_up_value);
        }
        if(rec_BS.buff_type == 3)
        {
            printf("버프 종류 : 공격력 + 방어력\n");
            printf("공격력 증가량 : %d  방어력 증가량 : %d", rec_BS.attack_up_value, rec_BS.defense_up_value);
        }
        if(rec_BS.buff_type == 4)
        {
            printf("버프 종류 : 속도\n");
            printf("속도 증가량 : %d", rec_BS.speed_up_value);
        }
        if(rec_BS.buff_type == 5)
        {
            printf("버프 종류 : 공격력 + 속도\n");
            printf("공격력 증가량 : %d  속도 증가량 : %d", rec_BS.attack_up_value, rec_BS.defense_up_value);
        }
        if(rec_BS.buff_type == 6)
        {
            printf("버프 종류 : 방어력 + 속도\n");
            printf("방어력 증가량 : %d  속도 증가량 : %d", rec_BS.defense_up_value, rec_BS.speed_up_value);
        }
        if(rec_BS.buff_type == 7)
        {
            printf("버프 종류 : 공격력 + 방어력 + 속도\n");
            printf("공격력 증가량 : %d  방어력 증가량 : %d  속도 증가량 : %d", rec_BS.attack_up_value, rec_BS.defense_up_value, rec_BS.speed_up_value);
        }
    }
}

void check_debuffSkill(FILE* fp, struct debuffSkill rec_DS)
{
    // 디버프 스킬의 정보 출력
    if (fread(&rec_DS,  sizeof(rec_DS),  1,  fp) > 0) 
    {
        printf("스킬 ID : %d 이름 : %s 종류 : %s\n", rec_DS.sid, rec_DS.skill_name, "디버프");

        // 디버프 종류| 1: 공격력 2: 방어력 3: 공격력 + 방어력 4: 속도 5: 공격력 + 속도 6: 방어력 + 속도
        // 디버프 종류| 7: 공격력 + 방어력 + 속도
        if(rec_DS.debuff_type == 1) 
        {
            printf("디버프 종류 : 공격력\n");
            printf("공격력 감소량 : %d", rec_DS.attack_down_value);
        }
        if(rec_DS.debuff_type == 2)
        {
            printf("디버프 종류 : 방어력\n");
            printf("방어력 감소량 : %d", rec_DS.defense_down_value);
        }
        if(rec_DS.debuff_type == 3)
        {
            printf("디버프 종류 : 공격력 + 방어력\n");
            printf("공격력 감소량 : %d  방어력 감소량 : %d", rec_DS.attack_down_value, rec_DS.defense_down_value);
        }
        if(rec_DS.debuff_type == 4)
        {
            printf("디버프 종류 : 속도\n");
            printf("속도 감소량 : %d", rec_DS.speed_down_value);
        }
        if(rec_DS.debuff_type == 5)
        {
            printf("디버프 종류 : 공격력 + 속도\n");
            printf("공격력 감소량 : %d  속도 감소량 : %d", rec_DS.attack_down_value, rec_DS.defense_down_value);
        }
        if(rec_DS.debuff_type == 6)
        {
            printf("디버프 종류 : 방어력 + 속도\n");
            printf("방어력 감소량 : %d  속도 감소량 : %d", rec_DS.defense_down_value, rec_DS.speed_down_value);
        }
        if(rec_DS.debuff_type == 7)
        {
            printf("디버프 종류 : 공격력 + 방어력 + 속도\n");
            printf("공격력 감소량 : %d  방어력 감소량 : %d  속도 감소량 : %d", rec_DS.attack_down_value, rec_DS.defense_down_value, rec_DS.speed_down_value);
        }
    }
}

void check_healSkill(FILE* fp, struct healSkill rec_HS)
{
    // 힐 스킬의 정보 출력
    if (fread(&rec_HS,  sizeof(rec_HS),  1,  fp) > 0) 
    {
        printf("스킬 ID : %d  스킬이름 : %s  타입 : %s  힐량 : %d\n", rec_HS.sid, rec_HS.skill_name, "힐", rec_HS.heal_value);
    }
}


void check_skill(FILE* fp)
{
    // 스킬 sid를 입력받아 해당 스킬 확인시켜주기
    struct attackSkill rec_AS;
    struct buffSkill rec_BS;
    struct debuffSkill rec_DS;
    struct healSkill rec_HS;

    int sid;

    printf("검색할 스킬의 SID 입력: ");

    // 스킬ID| 0~99: 공격스킬, 100~199: 버프스킬, 200~299: 디버프스킬, 300~399 힐스킬
    if (scanf("%d", &sid) == 1) {
        if(sid % 100 == ATTACKSKILL)
        {
            fseek(fp, sid * sizeof(rec_AS), SEEK_SET);
            check_attackSkill(fp, rec_AS);
        }

        fseek(fp, START_ATTACKSKILL_ID * sizeof(rec_AS), SEEK_SET);

        if(sid % 100 == BUFFSKILL)
        {
            fseek(fp, (sid - START_BUFFSKILL_ID) * sizeof(rec_BS), SEEK_CUR);
            check_buffSkill(fp, rec_BS);
        }

        fseek(fp, (START_BUFFSKILL_ID - START_ATTACKSKILL_ID) * sizeof(rec_BS), SEEK_CUR);

        if(sid % 100 == DEBUFFSKILL)  
        {
            fseek(fp, (sid - START_BUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);
            check_debuffSkill(fp, rec_DS);
        }

        fseek(fp, (START_DEBUFFSKILL_ID - START_BUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);

        if(sid % 100 == HEALSKILL)
        {
            fseek(fp, (sid - START_DEBUFFSKILL_ID) * sizeof(rec_HS), SEEK_CUR);
            check_healSkill(fp, rec_HS);
        }
    }
    // 예외처리
    else printf("입력 오류");
}



int main(int argc, char *argv[])
{
    char c;
    FILE *fp;

    // 예외처리
    if ((fp = fopen("skillDex", "rb")) == NULL ) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    // N을 입력받을때까지 스킬 체크 함수 돌기
    do {
        check_skill(fp);

        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');

    fclose(fp);
    exit(0);
}