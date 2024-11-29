#define MAX_STORY_LENGTH 100
#define MAX_TEXT_LENGTH 100
#define MAX_NORMALEVENT_NUM 5

// 이벤트 종류 헤더파일 
struct price
{
    int HP;
    int AP;
    int DP;
    int SP;
    int skill;
};

struct select
{
    char choice[MAX_TEXT_LENGTH];
    char result[MAX_TEXT_LENGTH];
    struct price prices;
};


struct event
{
    int event_id;
    int choice_num;
    char story[MAX_STORY_LENGTH];

    struct select select_1;
    struct select select_2;
    struct select select_3;
    struct select select_4;
    struct select select_5;
};