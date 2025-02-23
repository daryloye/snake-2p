#include "Snake.hpp"
#include "Settings.hpp"

bool gameOver = false;

Snake *s1 = new Snake(5, 10, HEAD1, BODY);
Snake *s2 = new Snake(15, 10, HEAD2, BODY);
Fruit *f1 = new Fruit();

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
			mvaddch(y, x, SPACE);

			// draw walls
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				mvaddch(y, x, WALL);

			// draw s1
			if (s1->isHead(x, y))
				mvaddch(y, x, s1->getHeadChar());
			if (s1->isBody(x, y))
				mvaddch(y, x, s1->getBodyChar());

			// draw s2
			if (s2->isHead(x, y))
				mvaddch(y, x, s2->getHeadChar());
			if (s2->isBody(x, y))
				mvaddch(y, x, s2->getBodyChar());

			// draw fruit
			if (f1->isFruit(x, y))
				mvaddch(y, x, FRUIT);

		}
	}

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
	gameOver = true;
	napms(2000);
}

void generateNewFruit()
{
	do {
		delete f1;
		f1 = new Fruit();
	}
	while (
		(s1->isBody(f1->getPositionX(), f1->getPositionY()))
		|| (s1->isHead(f1->getPositionX(), f1->getPositionY()))
		|| (s2->isBody(f1->getPositionX(), f1->getPositionY()))
		|| (s2->isHead(f1->getPositionX(), f1->getPositionY()))
	);
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

	// collision with each other head or bodies
	if (s1->isHead(s2_x, s2_y) || s1->isBody(s2_x, s2_y) || s2->isHead(s1_x, s1_y) || s2->isBody(s1_x, s1_y))
		End();

	// collision with own bodies
	if (s1->isBody(s1_x, s1_y) || s2->isBody(s2_x, s2_y))
		End();

	// collision with fruit
	if (f1->isFruit(s1_x, s1_y))
	{
		s1->eat();
		delete f1;
		f1 = new Fruit();
	}

	if (f1->isFruit(s2_x, s2_y))
	{
		s2->eat();
		delete f1;
		f1 = new Fruit();
	}
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
		napms(refreshRate);
		refresh();
	}
	endwin();

	delete s1;
	delete s2;
	delete f1;

	std::cout << std::endl;
	std::cout.flush();
	
	return 0;
}
