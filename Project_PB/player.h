// 플레이어 정보 구조체 

#ifndef PLAYER_H
#define PLAYER_H

#include "monster.h"

struct player
{
    int flag; // [0] 상태 플래그 (데이터 저장 여부)
    int playerID; // [1]
    int processID; // [2]
    int isServerRunning; // [3] 서버 실행 여부
    int isMyTurn; // [4]
    int initailized; // [5] 초기화 완료 여부
    
    // 김재훈이 추가한 변수들
    int is_dead; // [6] 죽었는지 판단하는 변수
    int is_battle_end; // [7] 배틀이 끝났는지 판단하는 변수
    int is_wined; // [8] 총 이긴 횟수를 저장하는 변수
    // 최근 선택한 스킬 종류를 저장하는 변수도 만들어야 함...
    struct monster selectedMonster;
};

#endif