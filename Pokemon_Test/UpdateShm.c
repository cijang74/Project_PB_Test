#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 구조체 공유메모리 만들기 귀찮아서 땜빵용으로 정수 배열 공유 메모리 만듦
int main()
{
	struct player* player;
	int shmid;
	key_t key;

	key = ftok("main", 10597); // 키값(키 정보) 설정

	// 플레이어 공유 메모리 접근
	shmid = shmget(key, sizeof(struct player) * 4, 0); // 플레이어
	if (shmid == -1) 
	{
		perror("공유 메모리 접근 실패.");
		exit(1);
	}

	shmp = (int*)shmat(shmid, NULL, 0); // 해당 프로세스에 플레이어 공유 메모리 부착

    // 공유메모리 주소를 통해 공유메모리에 값 넣기
	shmp[0] = 10; // hp
	shmp[1] = 5; // speed
	shmp[2] = 3; // attack
	shmp[3] = 0; // 죽었는지 판단

	shmp2[0] = 6;
	shmp2[1] = 1;
	shmp2[2] = 3;
	shmp2[3] = 0; // 죽었는지 판단

	shmp3[0] = 6;
	shmp3[1] = 4;
	shmp3[2] = 3;
	shmp3[3] = 0; // 죽었는지 판단

	shmp4[0] = 7;
	shmp4[1] = 2;
	shmp4[2] = 3;
	shmp4[3] = 0; // 죽었는지 판단

	//// 내 턴인지 판단하는 변수
	//shmp[4] = 0;
	//shmp2[4] = 0;
	//shmp3[4] = 0;
	//shmp4[4] = 0;

	// 현재 배틀이 끝났는지 판단하는 변수
	shmp[5] = 0;
	shmp2[5] = 0;
	shmp3[5] = 0;
	shmp4[5] = 0;

	// 플레이어 아이디를 저장하는 변수
	shmp[6] = 1;
	shmp2[6] = 2;
	shmp3[6] = 3;
	shmp4[6] = 4;

	// 이긴 횟수를 저장하는 변수
	shmp[7] = 0;
	shmp2[7] = 0;
	shmp3[7] = 0;
	shmp4[7] = 0;

    printf("\nshmid: %d\n", shmid);
    printf("hp: %d\n", shmp[0]);
    printf("speed: %d\n", shmp[1]);
    printf("attack: %d\n", shmp[2]);
    printf("is_dead: %d\n", shmp[3]);
	printf("is_myturn: %d\n", shmp[4]);
	printf("is_battleEnd: %d\n", shmp[5]);
	printf("playerId: %d\n", shmp[6]);
	printf("is_Win: %d\n", shmp[7]);

	printf("\nshmid: %d\n", shmid2);
	printf("hp: %d\n", shmp2[0]);
	printf("speed: %d\n", shmp2[1]);
	printf("attack: %d\n", shmp2[2]);
	printf("is_dead: %d\n", shmp2[3]);
	printf("is_myturn: %d\n", shmp2[4]);
	printf("is_battleEnd: %d\n", shmp2[5]);
	printf("playerId: %d\n", shmp2[6]);
	printf("is_Win: %d\n", shmp2[7]);

	printf("\nshmid: %d\n", shmid3);
	printf("hp: %d\n", shmp3[0]);
	printf("speed: %d\n", shmp3[1]);
	printf("attack: %d\n", shmp3[2]);
	printf("is_dead: %d\n", shmp3[3]);
	printf("is_myturn: %d\n", shmp3[4]);
	printf("is_battleEnd: %d\n", shmp3[5]);
	printf("playerId: %d\n", shmp3[6]);
	printf("is_Win: %d\n", shmp3[7]);

	printf("\nshmid: %d\n", shmid4);
	printf("hp: %d\n", shmp4[0]);
	printf("speed: %d\n", shmp4[1]);
	printf("attack: %d\n", shmp4[2]);
	printf("is_dead: %d\n", shmp4[3]);
	printf("is_myturn: %d\n", shmp4[4]);
	printf("is_battleEnd: %d\n", shmp4[5]);
	printf("playerId: %d\n", shmp4[6]);
	printf("is_Win: %d\n", shmp4[7]);

	shmdt(shmp);
	shmdt(shmp2);
	shmdt(shmp3);
	shmdt(shmp4);

	exit(0);
}