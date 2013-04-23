#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QImage>

#include "Global.h"
#include "Generator.h"

class Engine : public QObject {
	Q_OBJECT

private:
	Field maze;
	coordinate ball;

	void generate();

public:
	Engine();

	void run();
	void move(PRESSED_KEY k);
	void moveBall(int dx, int dy);

public slots:
	void keyPressed(PRESSED_KEY k);

signals:
	void drawField(QImage img);
};

#endif