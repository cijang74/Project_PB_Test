#include <stdio.h>
#include <stdlib.h>
#include "monster.h" // 몬스터 스텟 구조 저장 헤더파일 

struct monster check_monster(int mid, FILE* fp)
{
    // 이진파일을 읽어와서 특정 ID의 포켓몬 정보를 printf해주는 함수
    struct monster rec;

    // 몬스터 ID로 이진파일에 저장된 값들 에서 읽어올 시작 위치 정하고
    fseek(fp, mid *sizeof(rec), SEEK_SET);

    // 시작 위치에서 rec사이즈만큼 1블록 읽은 값을 rec에 저장 -> rec 구조체에 포켓몬 정보 입력됨
    if (fread(&rec,  sizeof(rec),  1,  fp) > 0)
    {
        // 포켓몬 정보 출력
        printf("몬스터ID : %d  이름 : %s  속성 : %s  레벨 : %s\n", rec.mid, rec.monster_name, rec.property, rec.stats.exp);
        printf("HP : %d  공격력 : %d  방어력 : %d  속도 : %d\n",rec.stats.HP, rec.stats.attackPower, rec.stats.defensePower, rec.stats.speed);
        return rec;
    }
    else printf("레코드 %d 없음\n", mid);
    
}


int main(int argc, char *argv[])
{
    char c;
    int mid;
    FILE *fp;

    // 예외처리
    if ((fp = fopen("monsterDex", "rb")) == NULL ) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    do 
    {    
        // 몬스터의 ID를 입력받고 check_monster함수 실행
        printf("검색할 몬스터의 MID 입력: ");

        if (scanf("%d", &mid) == 1) check_monster(mid, fp);
        else printf("입력 오류");

        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');

    fclose(fp);
    exit(0);
}