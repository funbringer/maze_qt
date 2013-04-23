#ifndef GENERATOR_H
#define GENERATOR_H

#include <QQueue>
#include <QStack>
#include <QTime>
#include <QImage>
#include <QPainter>

#include "Global.h"

class Field {

private:
	CELL_STATE** maze;

	coordinate lab_south(coordinate posit);
	coordinate lab_north(coordinate posit);
	coordinate lab_east(coordinate posit);
	coordinate lab_west(coordinate posit);
	CELL_STATE getCell(coordinate posit);

	bool lab_is_empty(coordinate posit);
	bool posib_nextcell(coordinate posit);
	coordinate get_nextcell(coordinate posit);

	void build_wall(int LIN, int COL);
	coordinate rand_start(int LIN, int COL);
	
public:
	Field();
	~Field();

	int build();

	QImage getImage();
	void setCell(int x, int y, CELL_STATE st);
	CELL_STATE getCell(int x, int y);

	coordinate placeBall();
	void placeFinish();
};

#endif