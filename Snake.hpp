#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <deque>

enum Direction
{
	N, // 0
	E, // 1
	S, // 2
	W, // 3
};

const int LEFT = -1;
const int RIGHT = +1;

class Body
{
	private:
		int _posX, _posY;
		bool _isHead;

	public:
		Body(int posX, int posY, int isHead): _posX(posX), _posY(posY), _isHead(isHead) {};

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
		int _direction;
		int _score = 0;
		std::deque<Body*> _body;

	public:
		Snake(int startX, int startY, int startDirection)
			: _direction(startDirection) {
			
			// TODO: create body based on start direction
			_body.push_back(new Body(startX, startY, true));
			_body.push_back(new Body(startX, startY + 1, false));
			_body.push_back(new Body(startX, startY + 2, false));
			_body.push_back(new Body(startX, startY + 3, false));
		};

		bool isHead(int x, int y) { 
			return (
				x == _body.front()->getPositionX() 
				&& y == _body.front()->getPositionY()
				);
			};
		
		bool isBody(int x, int y) {
			for (std::deque<Body *>::const_iterator iter = _body.begin();
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
			for (std::deque<Body *>::const_iterator iter = _body.end() - 1;
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

		// TODO: handle fruit
		void eat() {

			// create a new tail at the end
			_body.push_back(new Body(
				_body.back()->getPositionX(),
				_body.back()->getPositionY(),
				false
				)
			);

			increaseScore();
		}

		void setDirection(int key) { _direction = (_direction + key + 4) % 4; };
		int getDirection() { return _direction; };

		void increaseScore() { _score++; };
		int getScore() { return _score; };

		int getHeadPositionX() { return _body.front()->getPositionX(); };
		int getHeadPositionY() { return _body.front()->getPositionY(); };
};

#endif