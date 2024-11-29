#include <stdio.h>
#include <stdlib.h>
#include "skill.h"

// 스킬 수정하는 코드 
int update_attackSkill(FILE* fp, struct attackSkill rec_AS)
{
    printf("현재 스킬 ID : %6d 이름 : %4s 종류 : %4s\n", rec_AS.sid, rec_AS.skill_name, "공격");
    printf("새로운 이름 입력 : ");
    scanf("%s", &rec_AS.skill_name);

    printf("\n공격형 스킬\n");
    printf("현재 데미지 : %3d 스킬 속성 : %3s\n", rec_AS.skill_damage, rec_AS.property);
    
    printf("새로운 공격 스킬 입력\n데미지  스킬속성\n");
    if(scanf("%d %s",&rec_AS.skill_damage, &rec_AS.property) != 2) return 0;
    fwrite(&rec_AS, sizeof(rec_AS), 1, fp);

    return 1;
}

int update_buffSkill(FILE* fp, struct buffSkill rec_BS)
{
    printf("현재 스킬 ID : %6d 이름 : %4s 종류 : %4s\n", rec_BS.sid, rec_BS.skill_name, "버프");

    printf("새로운 이름 입력 : ");
    scanf("%s", &rec_BS.skill_name);


    printf("\n버프 스킬\n");
    if(rec_BS.buff_type == 1) printf("현재 버프 종류 : 공격력\n");
    if(rec_BS.buff_type == 2) printf("현재 버프 종류 : 방어력\n");
    if(rec_BS.buff_type == 3) printf("현재 버프 종류 : 공격력 + 방어력\n");
    if(rec_BS.buff_type == 4) printf("현재 버프 종류 : 속도\n");
    if(rec_BS.buff_type == 5) printf("현재 버프 종류 : 공격력 + 속도\n");
    if(rec_BS.buff_type == 6) printf("현재 버프 종류 : 방어력 + 속도\n");
    if(rec_BS.buff_type == 7) printf("현재 버프 종류 : 공격력 + 방어력 + 속도\n");


    printf("새로운 버프 종류 입력 : ");
    scanf("%d",&rec_BS.buff_type);

    if(rec_BS.buff_type == 1){
        printf("공격력 증가량 입력 : ");
        scanf("%d", &rec_BS.attack_up_value);
    }
    if(rec_BS.buff_type == 2){
        printf("방어력 증가량 입력 : ");
        scanf("%d", &rec_BS.defense_up_value);
    }
    if(rec_BS.buff_type == 3){
        printf("증가량 입력\n공격력 방어력");
        if(scanf("%d %d", &rec_BS.attack_up_value, &rec_BS.defense_up_value) != 2) return 0;
    }
    if(rec_BS.buff_type == 4){
        printf("속도 증가량 입력 : ");
        scanf("%d", &rec_BS.speed_up_value);
    }
    if(rec_BS.buff_type == 5){
        printf("증가량 입력\n공격력 속도");
        if(scanf("%d %d", &rec_BS.attack_up_value, &rec_BS.speed_up_value) != 2) return 0;
    }
    if(rec_BS.buff_type == 6){
        printf("증가량 입력\n방어력 속도");
        if(scanf("%d %d", &rec_BS.defense_up_value, &rec_BS.speed_up_value) != 2) return 0;
    }
    if(rec_BS.buff_type == 7){
        printf("증가량 입력\n공격력 방어력 속도");
        if(scanf("%d %d", &rec_BS.attack_up_value, &rec_BS.defense_up_value, &rec_BS.speed_up_value) != 3) return 0;
    }
    fwrite(&rec_BS, sizeof(rec_BS), 1, fp);

    return 1;
}

int update_debuffSkill(FILE* fp, struct debuffSkill rec_DS)
{
    printf("현재 스킬 ID : %6d 이름 : %4s 종류 : %4s\n", rec_DS.sid, rec_DS.skill_name, "디버프");

    printf("새로운 이름 입력 : ");
    scanf("%s", &rec_DS.skill_name);


    printf("\n디버프 스킬\n");
    if(rec_DS.debuff_type == 1) printf("현재 디버프 종류 : 공격력\n");
    if(rec_DS.debuff_type == 2) printf("현재 디버프 종류 : 방어력\n");
    if(rec_DS.debuff_type == 3) printf("현재 디버프 종류 : 공격력 + 방어력\n");
    if(rec_DS.debuff_type == 4) printf("현재 디버프 종류 : 속도\n");
    if(rec_DS.debuff_type == 5) printf("현재 디버프 종류 : 공격력 + 속도\n");
    if(rec_DS.debuff_type == 6) printf("현재 디버프 종류 : 방어력 + 속도\n");
    if(rec_DS.debuff_type == 7) printf("현재 디버프 종류 : 공격력 + 방어력 + 속도\n");

    printf("새로운 디버프 종류 입력 : ");
    scanf("%d",&rec_DS.debuff_type);

    if(rec_DS.debuff_type == 1){
        printf("공격력 감소량 입력 : ");
        scanf("%d", &rec_DS.attack_down_value);
    }
    if(rec_DS.debuff_type == 2){
        printf("방어력 감소량 입력 : ");
        scanf("%d", &rec_DS.defense_down_value);
    }
    if(rec_DS.debuff_type == 3){
        printf("감소량 입력\n공격력 방어력");
        if(scanf("%d %d", &rec_DS.attack_down_value, &rec_DS.defense_down_value) != 2) return 0;
    }
    if(rec_DS.debuff_type == 4){
        printf("속도 감소량 입력 : ");
        scanf("%d", &rec_DS.speed_down_value);
    }
    if(rec_DS.debuff_type == 5){
        printf("감소량 입력\n공격력 속도");
        if(scanf("%d %d", &rec_DS.attack_down_value, &rec_DS.speed_down_value) != 2) return 0;
    }
    if(rec_DS.debuff_type == 6){
        printf("감소량 입력\n방어력 속도");
        if(scanf("%d %d", &rec_DS.defense_down_value, &rec_DS.speed_down_value) != 2) return 0;
    }
    if(rec_DS.debuff_type == 7){
        printf("감소량 입력\n공격력 방어력 속도");
        if(scanf("%d %d", &rec_DS.attack_down_value, &rec_DS.defense_down_value, &rec_DS.speed_down_value) != 3) return 0;
    }
    fwrite(&rec_DS, sizeof(rec_DS), 1, fp);
    
    return 1;
}

void update_healSkill(FILE* fp, struct healSkill rec_HS)
{
    printf("스킬 ID : %6d 이름 : %4s 종류 : %4s\n", rec_HS.sid, rec_HS.skill_name, "힐");

    printf("새로운 이름 입력 : ");
    scanf("%s", &rec_HS.skill_name);


    printf("\n힐 스킬\n");
    printf("현재 힐량 : %3s\n", rec_HS.heal_value);

    printf("새로운 힐량 입력 : ");
    scanf("%d %s",&rec_HS.heal_value);

    fwrite(&rec_HS, sizeof(rec_HS), 1, fp);
}



int update_skill(FILE* fp)      //scan_monster처럼 scan_skill만드려면 스킬 구조체 종류별로 4개 다보내야해서 그냥 update_skill안에 넣었습니다
{
    struct attackSkill rec_AS;
    struct buffSkill rec_BS;
    struct debuffSkill rec_DS;
    struct healSkill rec_HS;
    
	int sid;
    int fread_return;           //제대로 읽었는지 확인하는 변수

    printf("수정할 스킬의 ID : ");
    if (scanf("%d", &sid) == 1)
    {
        if(sid % 100 == 0)          //공격형
        {
            fseek(fp, sid * sizeof(rec_AS), SEEK_SET);
            fread_return = fread(&rec_AS, sizeof(rec_AS), 1, fp);
            fseek(fp, -sizeof(rec_AS), SEEK_CUR);
        }
        fseek(fp, START_ATTACKSKILL_ID * sizeof(rec_AS), SEEK_SET);                         //위치 +100(공격스킬 크기)

        if(sid % 100 == 1)     //버프
        {
            fseek(fp, (sid - START_BUFFSKILL_ID) * sizeof(rec_BS), SEEK_CUR);               //위치 +(SID - 100)(버프스킬 크기)
            fread_return = fread(&rec_BS, sizeof(rec_BS), 1, fp);
            fseek(fp, -sizeof(rec_BS), SEEK_CUR);
        }
        fseek(fp, (START_BUFFSKILL_ID - START_ATTACKSKILL_ID) * sizeof(rec_BS), SEEK_CUR);  //위치 +100(버프스킬 크기)

        if(sid % 100 == 2)     //디버프
        {
            fseek(fp, (sid - START_DEBUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);             //위치 +(SID - 200)(디버프스킬 크기)
            fread_return = fread(&rec_DS, sizeof(rec_DS), 1, fp);
            fseek(fp, -sizeof(rec_DS), SEEK_CUR);
        }
        fseek(fp, (START_DEBUFFSKILL_ID - START_BUFFSKILL_ID) * sizeof(rec_DS), SEEK_CUR);  //위치 +100(디버프스킬 크기)
        
        if(sid % 100 == 3)     //힐
        {
            fseek(fp, (sid - START_HEALSKILL_ID) * sizeof(rec_HS), SEEK_CUR);                   //위치 +(SID - 300)(힐스킬 크기)
            fread_return = fread(&rec_HS, sizeof(rec_HS), 1, fp);
            fseek(fp, -sizeof(rec_HS), SEEK_CUR);
        }
        else printf("부적절한 ID입니다.");
        
        
        if (fread_return > 0)
        {
            if(sid % 100 == ATTACKSKILL)
            {
                if(update_attackSkill(fp, rec_AS) == 0) return 0;
            }


            else if(sid % 100 == BUFFSKILL)
            {
                if(update_buffSkill(fp, rec_BS) == 0) return 0;
            }


            else if(sid % 100 == DEBUFFSKILL)
            {
                if(update_debuffSkill(fp, rec_DS) == 0) return 0;                
            }


            else if(sid % 100 == HEALSKILL)
            {
                update_healSkill(fp, rec_HS);
            }
        }
        else printf("레코드 %d 없음\n", sid);
    }
    else printf("입력오류\n");
}



int main(int argc, char *argv[])
{
	char c;
	FILE *fp;
	
	if ((fp = fopen("skillDex", "rb+")) == NULL)
	{
		fprintf(stderr, "파일 열기 오류\n");
		exit(2);
	}
	
	do {
        if(update_skill(fp) == 0) break;

		printf("계속하겠습니까? (Y/N)");
		scanf(" %c", &c);
	} while (c == 'Y');
	fclose(fp);
	exit(0);
}
