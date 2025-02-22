#include "Snake.hpp"

#define WALL '#'
#define SPACE ' '
#define HEAD1 'o'
#define HEAD2 'O'
#define BODY '*'

bool gameOver = false;
const int width = 50;
const int height = 20;
int fruitX, fruitY;
bool hasFruit = false;

Snake *s1 = new Snake(5, 10, N);
Snake *s2 = new Snake(15, 10, N);

void Setup()
{
	initscr();			   // initialise screen
	cbreak();			   // disable line buffering, player don't need to press ENTER to input
	noecho();			   // don't echo input
	keypad(stdscr, TRUE);  // enable special keys
	nodelay(stdscr, TRUE); // getch() won't wait for player input

	srand(time(NULL));
}

void Draw()
{
	clear();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				mvaddch(y, x, WALL); // Walls
			else if (s1->isHead(x, y))
				mvaddch(y, x, HEAD1); // Snake head
			else if (s1->isBody(x, y))
				mvaddch(y, x, BODY);

			else if (s2->isHead(x, y))
				mvaddch(y, x, HEAD2);
			else if (s2->isBody(x, y))
				mvaddch(y, x, BODY);

			else
				mvaddch(y, x, SPACE);
		}
	}

	// if (!hasFruit)
	// {
	// 	int x = rand() % width;
	// 	int y = rand() % height;

	// 	mvaddch(y, x, '&');
	// 	hasFruit = true;
	// }

	printw("\n\nP1 score: %d", s1->getScore());
	printw("\nP2 score: %d", s2->getScore());
}

void End()
{
	int s1_score = s1->getScore();
	int s2_score = s2->getScore();

	if (s1_score > s2_score)
		printw("\n\nPLAYER 1 WINS!");
	else if (s2_score > s1_score)
		printw("\n\nPLAYER 2 WINS!");
	else
		printw("\n\nTIE!");
	refresh();
	pause();
}

void Logic()
{
	int s1_x = s1->getHeadPositionX();
	int s1_y = s1->getHeadPositionY();
	int s2_x = s2->getHeadPositionX();
	int s2_y = s2->getHeadPositionY();

	// wall collisions
	if (s1_x <= 0 || s1_x >= width - 1 || s1_y <= 0 || s1_y >= height - 1)
		End();
	if (s2_x <= 0 || s2_x >= width - 1 || s2_y <= 0 || s2_y >= height - 1)
		End();
	
	// collision with each other bodies
	if (s1->isBody(s2_x, s2_y) || s2->isBody(s1_x, s1_y))
		End();
	
	// collision with own bodies
	if ((s1->isBody(s1_x, s1_y) && !s1->isHead(s1_x, s1_y)) 
		|| (s2->isBody(s2_x, s2_y) && !s2->isHead(s2_x, s2_y)))
		End();
}

void Input()
{
	int ch = getch();
	if (ch == ERR) return ;

	switch(ch)		// get ascii char of key
	{
		case 'a':
			s1->setDirection(LEFT);
			break;
		case 'd':
			s1->setDirection(RIGHT);
			break;
		case KEY_LEFT:
			s2->setDirection(LEFT);
			break;
		case KEY_RIGHT:
			s2->setDirection(RIGHT);
			break;
	}

	// if (!hasFruit)
	// {
	// 	int x = rand() % width;
	// 	int y = rand() % height;

	// 	mvaddch(y, x, '&');
	// 	hasFruit = true;
	// }
}

void Move()
{
	s1->move();
	s2->move();
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Move();
		Logic();
		napms(250);
		refresh();
	}
	endwin();

	delete s1;
	delete s2;
	
	return 0;
}
