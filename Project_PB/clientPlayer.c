#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    // 포켓몬 공유메모리
    struct pokemon* shmaddr_pokemon;
    key_t key_pokemon;
    int shmid_pokemon;

    key_pokemon = ftok("/home/g_202111097/teamProject/포켓몬공유메모리", 1); // 포켓몬 공유메모리 키
    shmid_pokemon = shmget(key_pokemon, 1, IPC_CREAT | 0644);

    // 예외처리
    if (shmid_pokemon == -1)
    {
        perror("shmget");
        exit(1);
    }

    shmaddr_pokemon = (char*)shmat(shmid_pokemon, NULL, 0); // 포켓몬 공유메모리를 해당 프로세스에 부착

	printf("배틀 시작\n");

    if (1) // 만약 플레이어 1번의 포켓몬 스피드가 플레이어 2번의 포켓몬 스피드 보다 크다면)
    {
        
    }
}