#include "maze.h"

Window::Window() {
	setWindowTitle(tr("Ultimate Maze"));

	const short menu_size = 0;
	setFixedSize(MAZE_SIZE * TILE_SIZE, MAZE_SIZE * TILE_SIZE + menu_size);

	maze = new Screen(this);
	maze->setGeometry(0, 0, MAZE_SIZE * TILE_SIZE, MAZE_SIZE * TILE_SIZE);

	engine = new Engine();
	connect(this, SIGNAL(keyPressed(PRESSED_KEY)), engine, SLOT(keyPressed(PRESSED_KEY)));
	connect(engine, SIGNAL(drawField(QImage)), maze, SLOT(drawField(QImage)));

	engine->run();
}

Window::~Window() {
	delete engine;
}

void Window::keyPressEvent(QKeyEvent* ev) {
	switch(ev->key()) {
	case Qt::Key_Up:
		emit keyPressed(KEY_UP);
		break;
	case Qt::Key_Down:
		emit keyPressed(KEY_DOWN);
		break;
	case Qt::Key_Left:
		emit keyPressed(KEY_LEFT);
		break;
	case Qt::Key_Right:
		emit keyPressed(KEY_RIGHT);
		break;
	}
}
