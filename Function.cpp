#include"Game.h"

int Score = 0;          
int Add = 15;
snakenode *lastfood = NULL;
snakenode *snakehead = NULL;
int ButtonState = 4;
int sleepingtime = 200;

void Position(int x,int y){
	COORD position;
	HANDLE hOutput;
	position.X = x;
	position.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, position);
}

void CreateMap(){
	for (int i = 0; i < 80; i += 2){
		Position(i,0);
		printf("¡ö");
		Position(i,36);
		printf("¡ö");
	}
	for (int i = 1; i < 36; i++){
		Position(0,i);
		printf("¡ö");
		Position(78,i);
		printf("¡ö");
	}
}

void Schedule(int x){
	const int NUM = 50; 
	for (int i = 0; i < NUM; i++){
		Sleep(x);
		Position(50, 23);.
		printf("%.2lf%%\r", i * 100.0 / NUM);
	}
}

void InitSnakeBody(){
	snakenode *snaketail = (snakenode*)malloc(sizeof(snakenode));
	snaketail->x = 20;
	snaketail->y = 4;
	snaketail->next = NULL;
	for (int i = 1; i <= 4; ++i)
	{
		snakehead = (snakenode*)malloc(sizeof(snakenode));
		snakehead->next = snaketail;
		snakehead->x = 20 + 2*i;
		snakehead->y = 4;

		snaketail = snakehead;
	}

	while (snaketail != NULL){
		Position(snaketail->x,snaketail->y);
		printf("¡ö");
		snaketail = snaketail->next;
	}
}


bool EatSelf(){
	snakenode* self = snakehead->next;
	while(self != NULL)
	{
		if (self->x == snakehead->x && self->y == snakehead->y)
			return true;
		self = self->next;
	}
	return false;
}

bool HitTheWall(){
	if (snakehead->y == 0 || snakehead->y == 36 || snakehead->x == 0 || snakehead->x == 78)
		return true;
	else
		return false;
}

void CreateFood(){
	srand((unsigned)time(NULL));

	snakenode* food = (snakenode*)malloc(sizeof(snakenode));
	while ((food->x % 2) != 0)
	{
		food->x = rand() % 76 + 2;
	}
	food->y = rand() % 34 + 1;
	snakenode* cur = snakehead;
	while (cur->next!=NULL){
		if (food->x == cur->x && food->y == cur->y)
		{
			free(food);
			CreateFood();
		}
		cur = cur->next;
	}

	Position(food->x,food->y);
	lastfood = food;
	printf("■");
}


void SnakeMove(){
	snakenode* nexthead = (snakenode*)malloc(sizeof(snakenode));
	nexthead->next = NULL;

	if (ButtonState == UP)
	{
		nexthead->x = snakehead->x;
		nexthead->y = snakehead->y - 1;

		SameAction(nexthead, lastfood);
	}
	if (ButtonState == DOWN)
	{
		nexthead->x = snakehead->x;
		nexthead->y = snakehead->y + 1;

		SameAction(nexthead, lastfood);
	}
	if (ButtonState == LEFT)
	{
		nexthead->x = snakehead->x - 2;
		nexthead->y = snakehead->y;   

		SameAction(nexthead, lastfood);
	}
	if(ButtonState == RIGHT)
	{
		nexthead->x = snakehead->x + 2;
		nexthead->y = snakehead->y;  

		SameAction(nexthead, lastfood);
	}
}

void GameRecycle(){
	while (1)
	{
		if (GetAsyncKeyState(VK_UP) && ButtonState != DOWN)
			ButtonState = UP;
		else if (GetAsyncKeyState(VK_DOWN) && ButtonState != UP)
			ButtonState = DOWN;
		else if (GetAsyncKeyState(VK_LEFT) && ButtonState != RIGHT)
			ButtonState = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) && ButtonState != LEFT)
			ButtonState = RIGHT;
		else if (GetAsyncKeyState(VK_SPACE))
			Pause();
		else if (GetAsyncKeyState(VK_ESCAPE))
			SureRes();
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleepingtime >= 50)
			{
				sleepingtime = sleepingtime - 80;
				Add = Add + 5;
				if (sleepingtime == 320)
				{
					Add = 2;
				}
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleepingtime < 350)
			{
				sleepingtime = sleepingtime + 100;
				Add = Add - 5;
				if (sleepingtime == 350)
				{
					Add = 1;
				}
			}
		}
		Sleep(sleepingtime);
		SnakeMove();
	}
}


void Pause(){
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}


void SureRes(){	
	int num;
	Position(30, 14);
	printf("********************");
	Position(30, 16);
	printf("*    1.Restart    *");
	Position(30, 18);
	printf("*    2.Exit    *");
	Position(30, 20);
	printf("********************");
	Position(30, 22);
	printf("Choose Please\n");
	Position(30, 24);
	scanf("%d", &num);
	switch (num)
	{
	case 1:{system("cls"); GameStart(); }; break;
	case 2:{ ClearCorpse(); exit(1); }; break;
	default:{printf("Please Select again\n"); SureRes(); }; break;
	}
}

void ClearCorpse()
{
	while (snakehead)
	{
		snakenode* destroy = snakehead;
		snakehead = snakehead->next;
		free(destroy);
		destroy = NULL;
	}
}

void GameGuide()
{
	Position(100, 6);
	printf("Guide");
	Position(102, 8);
	printf("1.Rule: Snakes eat food, hit the wall and bite themselves, the game is over!");
	Position(102, 10);
	printf("2.Operation: Up and down and left and right buttons control the movement direction of the snake!");
	Position(100, 12);
	printf("Second, button description:");
	Position(102, 14);
	printf("1.F1 button: medium speed!");
	Position(102, 16);
	printf("2.F2 button: fast, high score!");
	Position(102, 18);
	printf("3.ESC key: The game is over!");
	Position(102, 20);
	printf("4.Spacebar: Game pause");
}

void SameAction(snakenode* nexthead,snakenode* lastfood)
{
	if (nexthead->x == lastfood->x && nexthead->y == lastfood->y)
	{
		nexthead->next = snakehead;
		snakehead = nexthead;
		GameOver();
		snakenode* cur = snakehead;
		while (cur != NULL)
		{
			Position(cur->x, cur->y);
			printf("■");
			cur = cur->next;
		}
		Score = Score + Add;
		Mark();
		CreateFood();
	}
	else
	{
		nexthead->next = snakehead;
		snakehead = nexthead;
		GameOver();
		snakenode* cur = snakehead;
		while (cur->next->next != NULL)
		{
			Position(cur->x, cur->y);
			printf("■");
			cur = cur->next;
		}

		Position(cur->next->x, cur->next->y);
		printf(" ");
		free(cur->next);
		cur->next = NULL;
	}
}


void Mark()
{
	Position(90, 24);
	printf("Here is your score for this round:");
	Position(90, 26);
	printf("┏━━━━━━━━━━━━┓");
	Position(90, 27);
	printf("┃                         ┃");
	Position(90, 28);
	printf("┃  Score: %d              ┃", Score);
	Position(90, 29);
	printf("┃                         ┃");
	Position(90, 30);
	printf("┗━━━━━━━━━━━━┛");
}



