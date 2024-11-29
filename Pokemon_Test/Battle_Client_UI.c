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

#define MAXLINE 100

void Devide_Team(int who_am_i);

void player_turn_attack(int who_am_i, int* shmp, int* shmp2); // 플레이어 공격 함수

void waiting_opponent(int who_am_i, int* shmp, int* shmp2); // 상대 플레이어 대기 함수

void Reset_Shm(int* shmp, int* shmp2);

void Print_Battle_Begine(int* shmp, int* shmp2);

int main(int argc, char* argv[])
{
	int answer = 0;
	int who_am_i = 0;

	int status, child;

	// 전달받은 인자값 (who_am_i)를 다시 정수화 하여 해당 코드 변수에 저장
	// 예외처리
	if (argc < 2)
	{
		printf("함수 인자값 및 함수 실행 실패");
		return 0;
	}

	who_am_i = atoi(argv[1]);
	
	Devide_Team(who_am_i);

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

void waiting_opponent(int who_am_i, int* shmp, int* shmp2)
{
	// 상대 플레이어의 선택 기다리기
	// 내 턴이 아닐때는 상대 기다리기

	int answer = 0;
	char buffer[MAXLINE];

	if (shmp[4] == 0)
	{
		printf("[Battle Manager]: 상대의 결정을 기다리는중..\n");

		while (shmp2[4] == 1)
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

void Devide_Team(int who_am_i)
// pid를 입력받고 조를 나눠 싸우게 만들어줄 수 있도록 하게 해주는 함수
{
	int shmid, shmid2, shmid3, shmid4, checkid;
	key_t key, key2, key3, key4;

	int* shmp; // p1 공유 메모리 저장 공간
	int* shmp2; // p2 공유 메모리 저장 공간
	int* checkp; // 체크용 공유 메모리 저장 공간

	// 흐름 판단에서 사용될 변수
	int winner_count = 0;

	// 키값(키 정보) 설정
	key = ftok("Player_file", 75);
	key2 = ftok("Player2_file", 76);
	key3 = ftok("Player3_file", 77);
	key4 = ftok("Player4_file", 78);

	// 공유메모리 접근
	shmid = shmget(key, 10 * sizeof(int), 0); // 플레이어 1
	shmid2 = shmget(key2, 10 * sizeof(int), 0); // 플레이어 2
	shmid3 = shmget(key3, 10 * sizeof(int), 0); // 플레이어 3
	shmid4 = shmget(key4, 10 * sizeof(int), 0); // 플레이어 4

	// 예외처리
	if (shmid == -1 || shmid2 == -1)
	{
		perror("shmget1");
		exit(1);
	}

	if (shmid2 == -1 || shmid3 == -1)
	{
		perror("shmget2");
		exit(1);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 나중에 이름 바꾸기: shmp -> player, shmp2 -> opponent
	if (who_am_i == 1)
	{
		// 공유메모리를 해당 프로세스에 부착
		shmp = (int*)shmat(shmid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	}

	if (who_am_i == 2)
	{
		// 공유메모리를 해당 프로세스에 부착
		shmp = (int*)shmat(shmid2, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	}

	if (who_am_i == 3)
	{
		// 공유메모리를 해당 프로세스에 부착
		shmp = (int*)shmat(shmid3, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	}

	if (who_am_i == 4)
	{
		// 공유메모리를 해당 프로세스에 부착
		shmp = (int*)shmat(shmid4, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 2명 생존했을 때 상대를 정하는 블럭////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	checkid = shmget(key, 10 * sizeof(int), 0); // 플레이어 1 체크
	checkp = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	if (checkp[7] == 1) // is_win
	{
		winner_count++;
		if (winner_count == 2)
		{
			shmp2 = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}
	}

	checkid = shmget(key2, 10 * sizeof(int), 0); // 플레이어 2 체크
	checkp = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	if (checkp[7] == 1) // is_win
	{
		winner_count++;
		if (winner_count == 2)
		{
			shmp2 = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}
	}

	checkid = shmget(key3, 10 * sizeof(int), 0); // 플레이어 3 체크
	checkp = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	if (checkp[7] == 1) // is_win
	{
		winner_count++;
		if (winner_count == 2)
		{
			shmp2 = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}
	}

	checkid = shmget(key4, 10 * sizeof(int), 0); // 플레이어 4 체크
	checkp = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	if (checkp[7] == 1) // is_win
	{
		winner_count++;
		if (winner_count == 2)
		{
			shmp2 = (int*)shmat(checkid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 4명 생존했을 때 상대를 정하는 블럭////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (winner_count < 2) // 4명 생존
	{
		if (who_am_i == 1)
		{
			// p1 vs p2
			shmp2 = (int*)shmat(shmid2, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}

		if (who_am_i == 2)
		{
			// p2 vs p1
			shmp2 = (int*)shmat(shmid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}

		if (who_am_i == 3)
		{
			// p3 vs p4
			shmp2 = (int*)shmat(shmid4, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}

		if (who_am_i == 4)
		{
			// p4 vs p3
			shmp2 = (int*)shmat(shmid3, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Reset_Shm(shmp, shmp2);
	Print_Battle_Begine(shmp, shmp2);

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

void Reset_Shm(int* shmp, int* shmp2)
{
	int pid1;
	int child, status;
	pid1 = fork(); // 자식 프로세스 생성
	if (pid1 == 0)
	{
		// 상대경로 fork파일을 실행
		execl("./UpdateShm", "./UpdateShm", NULL);
		exit(1);
	}
	child = wait(&status);
	return;
}

void Print_Battle_Begine(int* shmp, int* shmp2)
{
	printf("\n[Battle Manager]: || 포켓몬 배틀 시작! ||\n");

	printf("P1 shm 정보: [0]| hp: %d, [1]| speed: %d, [2]| attack: %d, [3]| is_dead: %d, [4]| is_my_turn: %d, [5]| is_battle_End: %d, [6]| ID: %d, [7]| win: %d\n",
		shmp[0], shmp[1], shmp[2], shmp[3], shmp[4], shmp[5], shmp[6], shmp[7]);

	printf("P2 shm 정보: [0]| hp: %d, [1]| speed: %d, [2]| attack: %d, [3]| is_dead: %d, [4]| is_my_turn: %d, [5]| is_battle_End: %d, [6]| ID: %d, [7]| win: %d\n\n",
		shmp2[0], shmp2[1], shmp2[2], shmp2[3], shmp2[4], shmp2[5], shmp2[6], shmp2[7]);

	return;
}