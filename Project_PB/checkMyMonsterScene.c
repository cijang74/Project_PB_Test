#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "monster.h" // 몬스터 스텟 구조 저장 헤더파일 
#include "player.h"

void checkMyMonster(int receivedPlayerID)
{
    key_t key = ftok("main", 10597);
    int shmid = shmget(key, sizeof(struct player) * 4, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget 실패");
        exit(1);
    }

    struct player* shmaddr = (struct player*)shmat(shmid, NULL, 0);
    if (shmaddr == (void*)-1)
    {
        perror("shmat 실패");
        exit(1);
    }
    printf("\n");
    printf("이름  속성\n");
    printf("-----------------------------------------------------\n");
    printf("%-5s %-5s\n", shmaddr[receivedPlayerID].selectedMonster.monster_name, shmaddr[receivedPlayerID].selectedMonster.property);
    printf("레벨    경험치    체력    공격력    방어력    스피드\n");
    printf("-----------------------------------------------------\n");
    printf("%-8d %-8d %-8d %-8d %-8d %-8d\n", shmaddr[receivedPlayerID].selectedMonster.stats.level, shmaddr[receivedPlayerID].selectedMonster.stats.exp,
        shmaddr[receivedPlayerID].selectedMonster.stats.HP, shmaddr[receivedPlayerID].selectedMonster.stats.attackPower,
        shmaddr[receivedPlayerID].selectedMonster.stats.defensePower, shmaddr[receivedPlayerID].selectedMonster.stats.speed);
    printf("스킬\n");
}


int main(int argc, char* argv[])
{
    int receivedPlayerID = atoi(argv[1]);

    checkMyMonster(receivedPlayerID);

    exit(0);
}
