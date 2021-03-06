#include <conio.h>
#include <windows.h>
#include <stdio.h>

bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum mode {NORMAL, WALL};

eDirecton dir;


int ModeSelect()
{
	int g_mode = NULL;
	printf("Select your mode\n[1] - Normal\n[2] - No Wall Collision\n\n$-");
	switch(_getch()){
	case '1':
		g_mode = NORMAL;
		break;
	case '2':
		g_mode = WALL;
		break;
	default:
		system("cls");
		ModeSelect();
		break;
	}

	return g_mode;
}

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls"); 
	for (int i = 0; i < width + 2; i++)
		printf("#");
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				printf("#");
			if (i == y && j == x)
				printf("O");
			else if (i == fruitY && j == fruitX)
				printf("X");
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						printf("o");
						print = true;
					}
				}
				if (!print)
					printf(" ");
			}


			if (j == width - 1)
				printf("#");
		}
		printf("\n");
	}

	for (int i = 0; i < width + 2; i++)
		printf("#");
	printf("\nScore: %d", score);
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic(int game_mode)
{

	enum orientation {UP, DOWN, LEFT, RIGHT};
	int current_orientation = NULL;

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		{
			current_orientation = orientation::LEFT;
			if(current_orientation != orientation::RIGHT)
				x--;
		}
		break;
	case RIGHT:
		{
			current_orientation = orientation::RIGHT;
			if(current_orientation != orientation::LEFT)
				x++;
		}
		break;
	case UP:
		{
			current_orientation = orientation::UP;
			if(current_orientation != orientation::DOWN)
				y--;
		}
		break;
	case DOWN:
		{
			current_orientation = orientation::DOWN;
			if(current_orientation != orientation::UP)
				y++;
		}
		break;
	default:
		break;
	}

	if(game_mode == NORMAL) // Wall collision mode ( NORMAL )
	{
		if (x > width || x < 0 || y > height || y < 0)
			gameOver = true;

	}
	else if (game_mode == WALL) // No Wall Collision mode ( WALL )
	{
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= height) y = 0; else if (y < 0) y = height - 1;
	}

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	system("color a0");
	Setup();
	int current_mode = ModeSelect();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic(current_mode);
		Sleep(10); //sleep(10);
	}

	system("color c0");
	printf("\n            Game over!\n");
	Sleep(2000);
	system("pause");

	return 0;
}
