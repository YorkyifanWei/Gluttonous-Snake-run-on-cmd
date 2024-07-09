/* definition */
#define BLACK 0x0// 黑色
#define BLUE 0x1// 蓝色
#define GREEN 0x2// 绿色
#define RESEDA 0x3 // 浅绿色
#define RED 0x4// 红色
#define PURPLE 0x5// 紫色
#define YELLOW 0x6// 黄色
#define WHITE 0x7// 白色
#define GREY 0x8// 灰色
#define BLUISH 0x9// 淡蓝色
#define ONDINE 0xA// 淡绿色
#define LIGHT_ONDINE 0xB// 淡浅绿色
#define REDDISH 0xC// 淡红色
#define LAVENDER 0xD// 淡紫色
#define FAINT_YELLOW 0xE// 淡黄色
#define GLOSS_WHITE 0xF// 亮白色
/* to locate the head of the snake */
typedef struct SnakeCoord_ {
    char name[20];
    _Bool alive;
    int x;// the location of the head of the snake
    int y;
    int t_x;// the location of the tail of the snake
    int t_y;
    int score;
    int speed;
    char direct;// 'u':upward; 'd':downward; 'l':leftward; 'r':rightward
} SnakeCoord;
typedef struct GameModern_ {
    int height;
    int width;
    int difficulty;
    int multiplayer;
    int size;
} GameModern;

/* Gets keyboard input without blocking other operations */
char GetKeyBoard(void);
/* Set the console font to ensure that the characters are square words of the same length and width */
void ConsoleSettings(void);
