#include "maze.h"

#include <QTime>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	qsrand(QTime::currentTime().msec());

	Window w;
	w.show();

	return a.exec();
}
