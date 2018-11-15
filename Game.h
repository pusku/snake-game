#pragma once

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


struct snakenode{
	int x;
	int y;
	snakenode *next;
};

void Position(int x, int y);
void CreateMap();
void Schedule(int x);
void InitSnakeBody();
void Start();
void Control();
void Over();
bool EatSelf();
bool HitTheWall();
void CreateFood();

void SnakeMove();
void Pause();
void GameRecycle();
void ClearCorpse();
void SureRes();
void GameGuide();
void SameAction(snakenode* nexthead, snakenode* lastfood);
void Mark();