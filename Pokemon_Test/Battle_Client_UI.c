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

#define MAXLINE 100

int start_hp;
int start_attack;
int start_defense;
int start_speed;

void Devide_Team(int playerID);

void player_turn_attack(int playerID, struct player* shmp); // 플레이어 공격 함수

void waiting_opponent(int playerID, struct player* shmp); // 상대 플레이어 대기 함수

void Reset_Shm(struct player* shmp);

void Print_Battle_Begine(struct player* shmp);

int main(int argc, char* argv[]) // 프로세스ID를 전달받음
{
	int answer = 0;
	int process_ID = 0;

	int status, child;

	// 전달받은 인자값 (process_ID)를 다시 정수화 하여 해당 코드 변수에 저장
	// 예외처리
	if (argc < 2)
	{
		printf("함수 인자값 및 함수 실행 실패");
		return 0;
	}

	process_ID = atoi(argv[1]);

	start_attack = shmp[i].selectedMonster.stats.attackPower;
	start_defense = shmp[i].selectedMonster.stats.defensePower;
	start_hp = shmp[i].selectedMonster.stats.HP;
	start_speed = shmp[i].selectedMonster.stats.speed;
	
	Devide_Team(process_ID);

	exit(0); // 다시 BattleManager로 돌아가기

	child = wait(&status);
}

void player_turn_attack(int who_am_i, int* shmp, int*shmp2)
{
	int answer = 0;
	char buffer[MAXLINE];

	printf("[Battle Manager]: || 당신의 턴! ||\n");
	printf("[Battle Manager]: 상대를 공격하시겠습니까?\n");
	printf("[Battle Manager]: 예: 1, 아니요: 0\n");

	// 사용자 입력 (gpt 수정부분)
	while (1) 
	{
		printf("[Battle Manager]: 입력: ");

		// 사용자 입력 받기
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) 
		{
			printf("\n[Battle Manager]: 입력 오류. 다시 입력해주세요.\n");
			printf("stdin 상태: EOF=%d\n", feof(stdin));
			exit(0);
		}

		// 입력 값 검증
		if (sscanf(buffer, "%d", &answer) != 1 || (answer != 0 && answer != 1)) 
		{ 
			printf("stdin 상태: EOF=%d\n", feof(stdin));
			exit(0);
		}

		break;
	}

	// 공격
	if (answer == 1)
	{
		// 공격 실행
		shmp2[0] -= shmp[2]; // 상대 포켓몬의 체력 감소
		printf("\n[Battle Manager]: || 공격결과 ||");
		printf("\n[Battle Manager]: 당신은 상대 포켓몬에게 %d의 피해를 입혔다.\n", shmp[2]);
		printf("[Battle Manager]: 상대 포켓몬의 체력은 %d로 줄어들었다.\n", shmp2[0]);
	}

	// 해당 공격으로 상대 플레이어의 체력이 0이 되는지 체크
	if (shmp2[0] <= 0)
	{
		shmp2[3] = 1; // isdead = 1;
		shmp[5] = 1; // is_battle_End = 1;
		shmp[7] = 1; // is_battle_End = 1;

		shmp[4] = 0;
		shmp2[4] = 1;

		printf("[Battle Manager]: 당신은 승리하였습니다. 메인 화면으로 돌아갑니까?\n");
		printf("[Battle Manager]: 예: 1, 아니요: 0\n");

		scanf("%d", &answer);
		printf("[Battle Manager]: 메인 화면으로 돌아갑니다..\n");

		return;
	}

	// 공격 후에는 상대 플레이어의 공격 함수 차례
	shmp[4] = 0;
	shmp2[4] = 1;
	printf("\n[Battle Manager]: || 상대 턴! ||\n");
	waiting_opponent(who_am_i, shmp, shmp2);
}

void waiting_opponent(int playerID, int processID, struct player* shmp)
//void waiting_opponent(int who_am_i, int* shmp, int* shmp2)
{
	// 상대 플레이어의 선택 기다리기
	// 내 턴이 아닐때는 상대 기다리기

	int answer = 0;
	char buffer[MAXLINE];

	if (shmp[processID].isMyTurn == 0) // 만약 내 턴이 아니라면
	{
		printf("[Battle Manager]: 상대의 결정을 기다리는중..\n");

		while (shmp2[4] == 1) // 여기까지 수정
		{
			sleep(1);
		}

		printf("[Battle Manager]: 상대는 당신의 포켓몬에게 %d의 피해를 입혔다.\n", shmp2[2]);
		printf("[Battle Manager]: 당신의 포켓몬의 체력은 %d로 줄어들었다.\n\n", shmp[0]);

		// 해당 공격으로 플레이어의 체력이 0이 되는지 체크
		if (shmp[0] <= 0)
		{
			shmp[3] = 1; // isdead = 1;
			shmp2[5] = 1; // is_battle_End = 1;
			shmp2[7] = 1; // is_battle_End = 1;

			return;
		}

		shmp[4] = 1; // is_myturn = 1으로 만들어 주기
		shmp2[4] = 0;

		player_turn_attack(who_am_i, shmp, shmp2);
	}
}

void Devide_Team(int processID) // process_ID를 전달받음
//조를 나눠 싸우게 만들어줄 수 있도록 하게 해주는 함수
{
	int shmid, checkid;
	key_t key;

	struct player* shmp; // p1 공유 메모리 저장 공간
	int* checkp; // 체크용 공유 메모리 저장 공간

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
	shmp = (int*)shmat(shmid, NULL, 0);

	int opponentID = 0;

	// 2명 생존했을 때 상대를 정하는 블럭////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (shmp[processID].is_wined == 1) // is_win
	{
		for (int i = 0; i < 4; i++)
		{
			if (shmp[i].is_wined == 1 && processID != i)
			{
				opponentID = i;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 4명 생존했을 때 상대를 정하는 블럭////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else // 4명 이상 생존하였을 때
	{
		if (processID + 1 == 1)
		{
			// p1 vs p2
			opponentID = 2;
		}

		if (processID + 1 == 2)
		{
			// p2 vs p1
			opponentID = 1;
		}

		if (processID + 1 == 3)
		{
			// p3 vs p4
			opponentID = 3;
		}

		if (processID + 1 == 4)
		{
			// p4 vs p3
			opponentID = 4;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Reset_Shm(shmp, processID, opponentID); // 공유 메모리 값들 중 배틀 관련 함수 초기화
	Print_Battle_Begine(shmp, processID, opponentID); // 배틀 문구 프린트

	// 각 포켓몬 스피드값 비교하여 선제턴 주기
	if (shmp[1] >= shmp2[1]) // 내 포켓몬이 상대 포켓몬보다 빠르면
	{
		shmp[4] = 1;
		shmp2[4] = 0;
	}

	if (shmp2[1] > shmp[1])
	{
		shmp[4] = 0;
		shmp2[4] = 1;
	}

	// 만약 플레이어의 턴이면 공격 기회 얻기
	if (shmp[4] == 1)
	{
		printf("\nDebug| p1 Speed: %d, p2 Speed: %d", shmp[1], shmp2[1]);
		player_turn_attack(who_am_i, shmp, shmp2);
	}

	//만약 플레이어의 턴이 아니면 기다리기
	else if (shmp[4] == 0)
	{
		waiting_opponent(who_am_i, shmp, shmp2);
	}

	printf("\n결과: shm[5]: %d, shm2[5]: %d\n", shmp[7], shmp2[7]);
	return;
}

void Reset_Shm(struct player* shmp, int processID, int opponentID)
{
	shmp[processID].isMyTurn = 0;
	shmp[processID].is_dead = 0;
	shmp[processID].is_battle_end = 0;

	shmp[processID].selectedMonster.stats.attackPower = start_attack;
	shmp[processID].selectedMonster.stats.defensePower = start_defense;
	shmp[processID].selectedMonster.stats.HP = start_hp;
	shmp[processID].selectedMonster.stats.speed = start_speed;

	return;
}

void Print_Battle_Begine(struct player* shmp, int processID, int opponentID)
{
	printf("\n[Battle Manager]: || 포켓몬 배틀 시작! ||\n");

	printf("P1 shm 정보: [0]| hp: %d, [1]| speed: %d, [2]| attack: %d, [3]| is_dead: %d, [4]| is_my_turn: %d, [5]| is_battle_End: %d, [6]| ID: %d, [7]| win: %d\n",
		shmp[0], shmp[1], shmp[2], shmp[3], shmp[4], shmp[5], shmp[6], shmp[7]);

	printf("P2 shm 정보: [0]| hp: %d, [1]| speed: %d, [2]| attack: %d, [3]| is_dead: %d, [4]| is_my_turn: %d, [5]| is_battle_End: %d, [6]| ID: %d, [7]| win: %d\n\n",
		shmp2[0], shmp2[1], shmp2[2], shmp2[3], shmp2[4], shmp2[5], shmp2[6], shmp2[7]);

	return;
}