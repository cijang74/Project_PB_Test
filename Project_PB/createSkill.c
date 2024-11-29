#include <stdio.h>
#include <stdlib.h>
#include "skill.h"
#define START_SID 0

// 스킬을 생성하는 코드 

int create_attackSkill(FILE* fp, struct attackSkill rec_AS)
{
    // 공격 스킬 ID, 스킬 이름, 데미지, 속성을 입력받아 공격스킬 구조체에 저장
    printf("%3s %15s\n", "스킬ID", "스킬 이름");
    if(scanf("%d %s", &rec_AS.sid, &rec_AS.skill_name) != 2) return 0;

    printf("데미지  속성\n");
    if(scanf("%d %s", &rec_AS.skill_damage, &rec_AS.property) != 2) return 0;

    fseek(fp, rec_AS.sid * sizeof(rec_AS), SEEK_SET);   //위치 +(SID)(공격스킬 크기)
    fwrite(&rec_AS, sizeof(rec_AS), 1, fp);

    return 1;
}

int create_buffSkill(FILE* fp, struct buffSkill rec_BS)
{
    // 버프 스킬 정보를 입력받아 버프스킬 구조체에 저장
    printf("스킬ID  스킬 이름\n");
    if(scanf("%d %s", &rec_BS.sid, &rec_BS.skill_name) != 2) return 0;

    printf("버프 타입 (1: 공격력, 2: 방어력, 3: 속도, 4: 공격력 + 방어력, 5: 공격력 + 속도, 6: 방어력 + 속도, 7: 전부)\n");   //원래 속도 = 4, 공+방 = 3이므로 이후에 둘 변환
    if(scanf("%d", &rec_BS.buff_type) != 1) return 0;
        
    if(rec_BS.buff_type == ATTACK){
        printf("공격력 증가량 입력 :");
        if(scanf("%d", &rec_BS.attack_up_value) != 1) return 0;
    }
    else if(rec_BS.buff_type == DEFENSE){
        printf("방어력 증가량 입력 :");
        if(scanf("%d", &rec_BS.defense_up_value) != 1) return 0;
    }
    else if(rec_BS.buff_type == 3){
        rec_BS.buff_type = SPEED;
        printf("속도 증가량 입력 :");
        if(scanf("%d", &rec_BS.speed_up_value) != 1) return 0;
    }
    else if(rec_BS.buff_type == 4){
        rec_BS.buff_type = ATTACK + DEFENSE;
        printf("버프 수치 입력\n%5d %5d\n", "공격력", "방어력");
        if(scanf("%d %d", &rec_BS.attack_up_value, &rec_BS.defense_up_value) != 2) return 0;
    }
    else if(rec_BS.buff_type == ATTACK + SPEED){
        printf("버프 수치 입력\n%5d %5d\n", "공격력", "속도");
        if(scanf("%d %d", &rec_BS.attack_up_value, &rec_BS.speed_up_value) != 2) return 0;
    }
    else if(rec_BS.buff_type == DEFENSE + SPEED){
        printf("버프 수치 입력\n%5d %5d", "방어력", "속도");
        if(scanf("%d %d", &rec_BS.defense_up_value, &rec_BS.speed_up_value) != 2) return 0;
    }
    else if(rec_BS.buff_type == ATTACK + DEFENSE + SPEED){
        printf("버프 수치 입력\n%5d %5d %5d", "공격력", "방어력", "속도");
        if(scanf("%d %d %d", &rec_BS.attack_up_value, &rec_BS.defense_up_value, &rec_BS.speed_up_value) != 3) return 0;
    }

    fseek(fp, (rec_BS.sid - START_BUFFSKILL_ID) * sizeof(rec_BS), SEEK_CUR);    //위치 +(SID - 100)(버프스킬 크기)
    fwrite(&rec_BS, sizeof(rec_BS), 1, fp);

    return 1;
}

int create_debuffSkill(FILE* fp, struct debuffSkill rec_DS)
{
    // 디버프스킬 정보를 입력받아 디버프스킬 구조체에 저장
    printf("스킬ID  스킬 이름\n");
        if(scanf("%d %s", &rec_DS.sid, &rec_DS.skill_name) != 2) return 0;

        printf("디버프 타입 (1: 공격력, 2: 방어력, 3: 속도, 4: 공격력 + 방어력, 5: 공격력 + 속도, 6: 방어력 + 속도, 7: 전부)\n");
        if(scanf("%d", &rec_DS.debuff_type) != 1) return 0;
            
        if(rec_DS.debuff_type == ATTACK)
        {
            printf("공격력 감소량 입력 : ");
            if(scanf("%d", &rec_DS.attack_down_value) != 1) return 0;
        }
        else if(rec_DS.debuff_type == DEFENSE)
        {
            printf("방어력 감소량 입력 : ");
            if(scanf("%d", &rec_DS.defense_down_value) != 1) return 0;
        }
        else if(rec_DS.debuff_type == 3)
        {
            rec_DS.debuff_type = SPEED;
            printf("속도 감소량 입력 : ");
            if(scanf("%d", &rec_DS.speed_down_value) != 1) return 0;
        }
        else if(rec_DS.debuff_type == 4)
        {
            rec_DS.debuff_type = ATTACK + DEFENSE;
            printf("디버프 수치 입력\n%5d %5d", "공격력", "방어력");
            if(scanf("%d %d", &rec_DS.attack_down_value, &rec_DS.defense_down_value) != 2) return 0;
        }
        else if(rec_DS.debuff_type == ATTACK + SPEED)
        {
            printf("디버프 수치 입력\n%5d %5d", "공격력", "속도");
            if(scanf("%d %d", &rec_DS.attack_down_value, &rec_DS.speed_down_value) != 2) return 0;
        }
        else if(rec_DS.debuff_type == DEFENSE + SPEED)
        {
            printf("디버프 수치 입력\n%5d %5d", "방어력", "속도");
            if(scanf("%d %d", &rec_DS.defense_down_value, &rec_DS.speed_down_value) != 2) return 0;
        }
        else if(rec_DS.debuff_type == ATTACK + DEFENSE + SPEED)
        {
            printf("디버프 수치 입력\n%5d %5d %5d", "공격력", "방어력", "속도");
            if(scanf("%d %d %d", &rec_DS.attack_down_value, &rec_DS.defense_down_value, &rec_DS.speed_down_value) != 3) return 0;
        }

        fseek(fp, (rec_DS.sid - START_DEBUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);          //위치 +(SID - 200)(디버프스킬 크기)
        fwrite(&rec_DS, sizeof(rec_DS), 1, fp);

        return 1;
}

int create_healSkill(FILE* fp, struct healSkill rec_HS)
{
    // 힐스킬 정보를 입력받아 힐스킬 구조체에 저장
    printf("스킬ID  스킬 이름\n");
    if(scanf("%d %s", &rec_HS.sid, &rec_HS.skill_name) != 2) return 0;

    printf("힐량 입력 : ");
    if(scanf("%d", &rec_HS.heal_value) != 1) return 0;

    fseek(fp, ((rec_HS.sid - START_HEALSKILL_ID) * sizeof(rec_HS)), SEEK_CUR);          //위치 +(SID - 300)(힐스킬 크기)
    fwrite(&rec_HS, sizeof(rec_HS), 1, fp);

    return 1;
}

int create_skill(FILE* fp)
{    
    // 스킬종류를 입력받아 종류별 스킬 생성함수를 실행시켜주는 함수
    struct attackSkill rec_AS;
    struct buffSkill rec_BS;
    struct debuffSkill rec_DS;
    struct healSkill rec_HS;

    int skill_type;

    printf("스킬 종류 (0 : 공격, 1 : 버프, 2 : 디버프, 3 : 힐) : ");
    scanf("%d", &skill_type);

    if(skill_type == ATTACKSKILL)       //공격 스킬
    {        
        if(create_attackSkill(fp, rec_AS) == 0) return 0;
    }

    fseek(fp, START_BUFFSKILL_ID * sizeof(rec_AS), SEEK_SET);                   //위치 +100(공격스킬 크기)

    if(skill_type == BUFFSKILL)         //버프 스킬
    {        
        if(create_buffSkill(fp, rec_BS) == 0) return 0;
    }

    fseek(fp, (START_DEBUFFSKILL_ID - START_BUFFSKILL_ID) * sizeof(rec_BS), SEEK_CUR);  //위치 +100(버프스킬 크기)

    if(skill_type == DEBUFFSKILL)       //디버프 스킬
    {        
        if(create_debuffSkill(fp, rec_DS) == 0) return 0;
    }

    fseek(fp, (START_HEALSKILL_ID - START_DEBUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);      //위치 +100(디버프스킬 크기)

    if(skill_type == 3)                 //힐 스킬
    {        
        if(create_healSkill(fp, rec_HS) == 0) return 0;
    }

    return 1;
}


int main(int argc, char* argv[])
{
    char c;
	FILE *fp;

	fp = fopen("skillDex", "wb");

    // 예외처리
    if ((fp = fopen("skillDex", "rb")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    // 사용자로부터 N을 입력받을때 까지 스킬 생성 함수 계속 실행
    do{
        if(create_skill(fp) == 0) break;

		printf("계속하겠습니까? (Y/N)");
		scanf(" %c", &c);
	} while (c == 'Y');

	fclose(fp);
	exit(0);
}