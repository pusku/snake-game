#include"Game.h"

void Menu(){
	Position(50, 13);
	printf("**************************************************************\n");
	Position(50, 15);
	printf("**                     -->Welcome                           **\n");
	Position(50, 17);
	printf("**************************************************************\n");
	Position(50, 19);
	printf("Press any key to start...");
	getchar();
	Position(50, 21);
	printf("Loading...");
	
	Schedule(200);
	system("cls");
}

void Start(){
	GameMenu();
	CreateMap();
	GameGuide();
	InitSnakeBody();
	CreateFood();
}

void Control(){
	GameRecycle();
}

void Over(){
	if (EatSelf() || HitTheWall())
	{
		Position(30,10);
		printf("Did you hit the wall? Or bite yourself?:)\n"); 
		Position(30, 12);
		printf("Choose:)\n");
		ClearCorpse();
		SureRes();
	}
}



