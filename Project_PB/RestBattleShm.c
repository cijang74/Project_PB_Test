#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "player.h"
#include "monster.h"

// 서 땜빵용으로 공유 메모리 만듦
int main()
{
	int shmid;
	key_t key;

	struct player* shmp; // p1 공유 메모리 저장 공간

	// 키값(키 정보) 설정
	key = ftok("main", 1);

	//공유 메모리 접근
	shmid = shmget(key, sizeof(struct player) * 4, IPC_CREAT | IPC_EXCL | 0644);
	if (shmid == -1) {
		perror("공유 메모리 생성 실패.");
		shmid = shmget(key, sizeof(struct player) * 4, 0);
		if (shmid == -1) {
			perror("존재하는 공유 메모리 없음.");
			exit(1);
		}
	}

	// 접근 예외처리
	if (shmid == -1)
	{
		perror("공유 메모리 접근 실패.");
		exit(1);
	}

	// 해당 프로세스에 플레이어 공유 메모리 부착
	shmp = (struct player*)shmat(shmid, NULL, 0);

	// 배틀에서 사용되는 변수들 전부 초기화
	for (int i = 0; i < 4; i++)
	{
		shmp[i].playerID = i + 1;
		shmp[i].is_dead = 0;
		shmp[i].isMyTurn = 0;
		shmp[i].is_battle_end = 0;
		shmp[i].is_wined = 0;

		shmp[i].selectedMonster.stats.attackPower = 2;
		shmp[i].selectedMonster.stats.HP = 8;
		shmp[i].selectedMonster.stats.speed = 7 - i;
		shmp[i].selectedMonster.stats.defensePower = 3;

		printf("\nplayerID: %d\n", shmp[i].playerID);
		printf("processID: %d\n", i);
		printf("is_dead: %d\n", shmp[i].is_dead);
		printf("is_myturn: %d\n", shmp[i].isMyTurn);
		printf("is_battleEnd: %d\n", shmp[i].is_battle_end);
		printf("is_Win: %d\n", shmp[i].is_wined);

		printf("attackPower: %d\n", shmp[i].selectedMonster.stats.attackPower);
		printf("HP: %d\n", shmp[i].selectedMonster.stats.HP);
		printf("speed: %d\n", shmp[i].selectedMonster.stats.speed);
		printf("defensePower: %d\n", shmp[i].selectedMonster.stats.defensePower);
	}

	shmdt(shmp);

	exit(0);
}