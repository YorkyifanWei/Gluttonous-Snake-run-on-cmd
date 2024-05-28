/* Another method to solve the problem of screen splash */
void GotoXY(int x, int y);
char *WinnerName(void);
/* gets keyboard input without blocking other operations */
char GetKeyBoard(void);
void PrintTitle(void);
/* initialize blocks and modern */
void Initial(void);
/* processing input, pause or end or turn */
char KeyProcess(char key);
/* print it to the screen */
void PrintScreen(void);
/* regardless of overlap */
void SnakeMove(int player_code);
/* to detect whether the snake hit sth */
int SnakeHit(int player_code);
/* to refresh new food randomly */
void FoodRefresh(void);
