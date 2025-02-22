#ifndef SNAKE_HPP
#define SNAKE_HPP

# include "Settings.hpp"

enum Direction
{
	N, // 0
	E, // 1
	S, // 2
	W, // 3
};

const int LEFT = -1;
const int RIGHT = +1;

class Fruit
{
	private:
		int _posX, _posY;
	
	public:
		Fruit() {
			_posX = rand() % (width - 2) + 1;
			_posY = rand() % (height - 2) + 1;
		};

		bool isFruit(int x, int y) { return (x == _posX && y == _posY); };

		int getPositionX() { return _posX; };
		int getPositionY() { return _posY; };
};

class Body
{
	private:
		int _posX, _posY;

	public:
		Body(int posX, int posY): _posX(posX), _posY(posY) {};

		void setPositionX(int x) { _posX = x; };
		void setPositionY(int y) { _posY = y; };
		
		void increasePositionX() { _posX++; };
		void decreasePositionX() { _posX--; };

		void increasePositionY() { _posY++; };
		void decreasePositionY() { _posY--; };

		int getPositionX() { return _posX; };
		int getPositionY() { return _posY; };
};

class Snake
{
	private:
		int _direction = N;
		int _score = 0;
		char _headChar, _bodyChar;
		std::deque<Body*> _body;

	public:
		Snake(int startX, int startY, char headChar, char bodyChar)
			: _headChar(headChar), _bodyChar(bodyChar) {

			_body.push_back(new Body(startX, startY));
			_body.push_back(new Body(startX, startY + 1));
			_body.push_back(new Body(startX, startY + 2));
			_body.push_back(new Body(startX, startY + 3));
		};

		bool isHead(int x, int y) { 
			return (
				x == _body.front()->getPositionX() 
				&& y == _body.front()->getPositionY()
				);
			};
		
		bool isBody(int x, int y) {
			for (std::deque<Body*>::const_iterator iter = _body.begin() + 1;
				iter != _body.end(); ++iter)
			{
				if ( x == (*iter)->getPositionX() && y == (*iter)->getPositionY())
					return true;
			}
			return false;
		};

		void move()
		{
			// move the other body parts up
			for (std::deque<Body*>::const_iterator iter = _body.end() - 1;
				iter != _body.begin(); iter--)
			{
				(*iter)->setPositionX((*(iter - 1))->getPositionX());
				(*iter)->setPositionY((*(iter - 1))->getPositionY());
			}

			// move the head
			switch (_direction)
			{
				case N:
					_body.front()->decreasePositionY();
					break;
				case S:
					_body.front()->increasePositionY();
					break;
				case W:
					_body.front()->decreasePositionX();
					break;
				case E:
					_body.front()->increasePositionX();
					break;
			}
		};

		void eat() {
			int newBodyPositionX = _body.back()->getPositionX();
			int newBodyPositionY = _body.back()->getPositionY();
			
			move();
			_body.push_back(new Body(newBodyPositionX, newBodyPositionY));
			_score++;
		}

		char getHeadChar() { return _headChar; };
		char getBodyChar() { return _bodyChar; };

		void setDirection(int key) { _direction = (_direction + key + 4) % 4; };
		int getDirection() { return _direction; };

		int getScore() { return _score; };

		int getHeadPositionX() { return _body.front()->getPositionX(); };
		int getHeadPositionY() { return _body.front()->getPositionY(); };
};

#endif