#include "Screen.h"

void Screen::paintEvent(QPaintEvent* ev) {
	QPainter painter(this);

	painter.fillRect(0,0, width(), height(), Qt::darkGray);
	painter.drawImage(0, 0, image);
}

Screen::Screen(QWidget* parent) {
	setParent(parent);
}

void Screen::drawField(QImage img) {
	image = img;
	this->update();
}
