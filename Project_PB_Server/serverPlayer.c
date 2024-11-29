#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// 배틀씬에서 서로의 플레이어가 상호작용 할 때 파이프를 만들고 배틀을 관리하는 서버 프로세스

void make_twoway_pipe()         //파이프 이름 겹치지 않도록 A조와 B조 구분 필요 
{
    // A조 배틀 파이프 2개 생성 할것.
    unlink("./battlefifo1"); // 클라이언트 -> 서버
    unlink("./battlefifo2"); // 서버 -> 클라이언트

    // B조 배틀 파이프 2개 생성 할것.
    unlink("./battlefifo3"); // 클라이언트 -> 서버
    unlink("./battlefifo4"); // 서버 -> 클라이언트
    
    // 예외처리
    if(mkfifo("./battlefifo1", 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }
    if(mkfifo("./battlefifo2", 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }
    if (mkfifo("./battlefifo3", 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }
    if (mkfifo("./battlefifo4", 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }
}

int main()
{
    int fd1, fd2, fd3, fd4, n;

    // 플레이어 공유메모리
    struct player* shmaddr_player;
    key_t key_player;
    int shmid_player;

    // 포켓몬 공유메모리
    struct pokemon* shmaddr_pokemon;
    key_t key_pokemon;
    int shmid_pokemon;

    int player[4][2];               //플레이어 아이디 + 프로세스 아이디

    int accessCount = 0;

    key_player = ftok("/home/g_202111097/teamProject/keyServerShm_1", 1); // 플레이어 공유메모리 키 (player[id][프로세스 아이디])
    shmid_player = shmget(key_player, 1, IPC_CREAT | 0644);

    // 예외처리
    if (shmid_player == -1)
    {
        perror("shmget");
        exit(1);
    }

    shmaddr_player = (char*)shmat(shmid_pokemon, NULL, 0); // 플레이어 공유메모리를 해당 프로세스에 부착

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    key_pokemon = ftok("/home/g_202111097/teamProject/포켓몬공유메모리", 1); // 포켓몬 공유메모리 키
    shmid_pokemon = shmget(key_pokemon, 1, IPC_CREAT | 0644);

    // 예외처리
    if (shmid_pokemon == -1)
    {
        perror("shmget");
        exit(1);
    }

    shmaddr_pokemon = (char*)shmat(shmid_player, NULL, 0); // 포켓몬 공유메모리를 해당 프로세스에 부착

    make_twoway_pipe(); // 파이프 생성

    // A조 배틀 파이프 2개열기
    fd1 = open("./battlefifo1", O_RDONLY); // 클라이언트 -> 서버
    fd2 = open("./battlefifo2", O_WRONLY); // 서버 -> 클라이언트

    // B조 배틀 파이프 2개 열기
    fd3 = open("./battlefifo3", O_RDONLY); // 클라이언트 -> 서버
    fd4 = open("./battlefifo4", O_WRONLY); // 서버 -> 클라이언트
    
}