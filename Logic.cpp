#include "Logic.h"

void Engine::generate() {
		maze.build();
		ball = maze.placeBall();
		maze.placeFinish();
}

Engine::Engine() {
	generate();
}

void Engine::run() {
	generate();

	emit drawField(maze.getImage());
}

void Engine::move(PRESSED_KEY k) {
	switch(k) {
	case KEY_UP:
		moveBall(0, -1);
		break;
	case KEY_DOWN:
		moveBall(0, 1);
		break;
	case KEY_LEFT:
		moveBall(-1, 0);
		break;
	case KEY_RIGHT:
		moveBall(1, 0);
		break;
	}

	emit drawField(maze.getImage());
}

void Engine::keyPressed(PRESSED_KEY k) {
	move(k);
}

void Engine::moveBall(int dx, int dy) {
	coordinate temp;
	temp.x = ball.x + dx;
	temp.y = ball.y + dy;

	if(maze.getCell(temp.x, temp.y) == ST_EMPTY) {
		maze.setCell(ball.x, ball.y, ST_EMPTY);
		maze.setCell(temp.x, temp.y, ST_BALL);
		ball = temp;

		emit drawField(maze.getImage());
	} else if(maze.getCell(temp.x, temp.y) == ST_FINISH) {
		run();
	}
}