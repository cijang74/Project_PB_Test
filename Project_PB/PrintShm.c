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

// 구조체 공유메모리 만들기 귀찮아서 땜빵용으로 정수 배열 공유 메모리 만듦
int main()
{
	int shmid;
	key_t key;

	struct player* shmp; // p1 공유 메모리 저장 공간

	// 키값(키 정보) 설정
	key = ftok("main", 10597);

	//공유 메모리 접근
	shmid = shmget(key, sizeof(struct player) * 4, 0); // 플레이어

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
		printf("\nprocessID: %d\n", i + 1);
		printf("is_dead: %d\n", shmp[i].is_dead);
		printf("is_myturn: %d\n", shmp[i].isMyTurn);
		printf("is_battleEnd: %d\n", shmp[i].is_battle_end);
		printf("is_Win: %d\n", shmp[i].is_wined);
	}

	shmdt(shmp);

	exit(0);
}