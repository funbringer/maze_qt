#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <QImage>

#include "Global.h"

class Screen : public QWidget {
	Q_OBJECT

private:
	void paintEvent(QPaintEvent* ev);

	QImage image;

public:
	explicit Screen(QWidget* parent);

public slots:
	void drawField(QImage img);	

};

#endif