#include <stdio.h>
#include <stdlib.h>
#include "monster.h"

void updateMonster(FILE* fp, struct monster rec)
{
	// 블록 읽어오는 위치 설정하여 알맞은 ID의 포켓몬 정보 읽어오고 데이터 업데이트하는 함수 
	fseek(fp, rec.mid * sizeof(rec), SEEK_SET);
	fwrite(&rec, sizeof(rec), 1, fp);
}

void updateMonsterHP(FILE* fp, int mid, int HP)
{
	// HP값 인자로 받아 포켓몬 정보 수정
	struct monster rec;

	fseek(fp, mid * sizeof(rec), SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);

	rec.stats.HP = HP;

	fseek(fp, -sizeof(rec), SEEK_CUR);
	fwrite(&rec, sizeof(rec), 1, fp);
}

void updateMonsterStats(FILE* fp, int mid, int AP, int DP, int SP)
{
	// 스테이터스값 인자로 받아 포켓몬 정보 수정
	struct monster rec;

	fseek(fp, mid * sizeof(rec), SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);

	if(AP != 0) rec.stats.attackPower = AP;
	if(DP != 0) rec.stats.defensePower = DP;
	if(SP != 0) rec.stats.speed = SP;
	
	fseek(fp, -sizeof(rec), SEEK_CUR);
	fwrite(&rec, sizeof(rec), 1, fp);
}

void updateMonsterLV(FILE* fp, int mid, int exp)
{
	// 경험치 인자로 받아 포켓몬 정보 수정
	struct monster rec;

	fseek(fp, mid * sizeof(rec), SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);

	rec.stats.exp += exp;	//레벨과 필요 경험치량에 따라 레벨 오르는 정도 수정하면 될 듯

	fseek(fp, -sizeof(rec), SEEK_CUR);
	fwrite(&rec, sizeof(rec), 1, fp);
}

int updateMonsterSkills(FILE* fp, int mid, int sid)
{
	// 스킬 아이디를 인자로 받아서 포켓몬 스킬 정보 수정
	struct monster rec;

	fseek(fp, mid * sizeof(rec), SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);

	if(rec.skills.skill_2_ID == -1) rec.skills.skill_2_ID = sid;
	else if(rec.skills.skill_3_ID == -1) rec.skills.skill_3_ID = sid;
	else if(rec.skills.skill_4_ID == -1) rec.skills.skill_4_ID = sid;
	else return -1;

	fseek(fp, -sizeof(rec), SEEK_CUR);
	fwrite(&rec, sizeof(rec), 1, fp);

	return 0;
}


int scanMonster(FILE* fp, struct monster rec)
{
	// 몬스터 데이터 수정
	int mid;

	printf("수정할 몬스터의 ID : ");
		if (scanf("%d", &mid) == 1)
		{
			fseek(fp, mid * sizeof(rec), SEEK_SET);
			if (fread(&rec, sizeof(rec), 1, fp) > 0)
			{
				printf("몬스터 ID : %3d   이름 : %4s   속성 : %4s\n", rec.mid, rec.monster_name, rec.property);
				printf("새로운 이름 입력 : ");
				scanf("%s", &rec.monster_name);
				printf("새로운 속성 입력 : ");
				scanf("%s", &rec.property);

                printf("\n현재 스탯\n");
                printf("HP : %3d   공격력 : %3d   방어력 : %3d   속도 : %3d\n", rec.stats.HP, rec.stats.attackPower, rec.stats.defensePower, rec.stats.speed);
                printf("새로운 스탯 입력\n%3s %10s %10s %7s\n", "HP", "공격력", "방어력", "속도");
                if(scanf("%d %d %d %d",&rec.stats.HP, &rec.stats.attackPower, &rec.stats.defensePower, &rec.stats.speed) == 4){
					return 1;
                }
            }
            else printf("레코드 %d 없음\n", mid);
		}
		else printf("입력오류\n");
		return 0;
}


int main(int argc, char *argv[])
{
	char c;
	FILE *fp;
	struct monster rec;
	
	// 예외처리
	if ((fp = fopen("monsterDex", "rb+")) == NULL)
	{
		fprintf(stderr, "파일 열기 오류\n");
		exit(2);
	}
	
	// 몬스터 수정해주고 계속 업데이트
	do {
		if(scanMonster(fp, rec) == 1) updateMonster(fp, rec);

		printf("계속하겠습니까? (Y/N)");
		scanf(" %c", &c);
	} while (c == 'Y');

	fclose(fp);
	exit(0);
}
