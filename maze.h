#ifndef MAZE_H
#define MAZE_H

#include <QMainWindow>
#include <QImage>

#include "Screen.h"
#include "Global.h"
#include "Logic.h"

class Window : public QMainWindow {
	Q_OBJECT

private:
	Screen* maze;
	Engine* engine;

	void keyPressEvent(QKeyEvent* ev);

public:
	Window();
	~Window();

signals:
	void keyPressed(PRESSED_KEY p);
};

#endif
