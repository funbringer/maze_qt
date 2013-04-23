#include "Generator.h"

Field::Field() {
	maze = new CELL_STATE*[MAZE_SIZE];

	for(int i = 0; i < MAZE_SIZE; i++) {
		maze[i] = new CELL_STATE[MAZE_SIZE];

		for(int j = 0; j < MAZE_SIZE; j++)
			maze[i][j] = ST_WALL;
	}
}

Field::~Field() {
	for(int i = 0; i < MAZE_SIZE; i++) {
		delete[] maze[i];
	}

	delete[] maze;
}

coordinate Field::lab_south(coordinate posit) {
	coordinate temp;
	temp.x = --posit.x;
	temp.y = posit.y;
	return temp;
}

coordinate Field::lab_north(coordinate posit) {
	coordinate temp;
	temp.x = ++posit.x;
	temp.y = posit.y;
	return temp;
}

coordinate Field::lab_east(coordinate posit) {
	coordinate temp;
	temp.x = posit.x;
	temp.y = ++posit.y;
	return temp;
}

coordinate Field::lab_west(coordinate posit) {
	coordinate temp;
	temp.x = posit.x;
	temp.y = --posit.y;
	return temp;
}

bool Field::lab_is_empty(coordinate posit) {
	if (maze[posit.x][posit.y] == ST_WALL)
	{
		coordinate sou = lab_south(posit);
		coordinate nor = lab_north(posit);
		coordinate eas = lab_east(posit);
		coordinate wes = lab_west(posit);

		
		int sum = getCell(sou)+
			getCell(nor)+
			getCell(eas)+
			getCell(wes);

		return (sum % ST_PERM_WALL) <= 1;
	}

	return false;
}

bool Field::posib_nextcell(coordinate posit) {
	return (lab_is_empty(lab_south(posit))
		|| lab_is_empty(lab_north(posit))
		|| lab_is_empty(lab_east(posit))
		|| lab_is_empty(lab_west(posit))
		);
}

coordinate Field::get_nextcell(coordinate posit) {
	coordinate aux;
	bool ok = false;
	while (!ok)
	{

		int gen = (qrand() % 4) + 1;

		switch(gen){
		case 1: aux = lab_south(posit); break;
		case 2: aux = lab_north(posit); break;
		case 3: aux = lab_east(posit);  break;
		case 4: aux = lab_west(posit);  break;
		}
		if (lab_is_empty(aux)) ok = true;
	}
	return aux;
}

void Field::build_wall(int LIN, int COL)
{
	for (int x = 0; x < COL; x++) {
		maze[0][x] = maze[LIN - 1][x] = ST_PERM_WALL;
	}
	for (int y = 0; y < LIN; y++) {
		maze[y][0] = maze[y][COL - 1] = ST_PERM_WALL;
	}
}

coordinate Field::rand_start(int LIN, int COL) {
	coordinate aux;
	
	aux.x = qrand() % (LIN - 1); if (aux.x == 0) aux.x++;
	aux.y = qrand() % (COL - 1); if (aux.y == 0) aux.y++;
	return aux;
}

int Field::build() {
	for(int i = 0; i < MAZE_SIZE; i++)
		for(int j = 0; j < MAZE_SIZE; j++)
			maze[i][j] = ST_WALL;

	QStack<coordinate> trail;

	int LIN = MAZE_SIZE;
	int COL = MAZE_SIZE;

	build_wall(LIN, COL);

	coordinate cell = rand_start(LIN, COL);
	trail.push(cell);

	maze[cell.x][cell.y] = ST_EMPTY;

	while(!trail.empty()) {
		cell = trail.top();

		if (posib_nextcell(cell)) {
			cell = get_nextcell(cell);
			trail.push(cell);
			maze[cell.x][cell.y] = ST_EMPTY;
		} else {
			trail.pop();
		}
	}

	return 0;
}

QImage Field::getImage() {
	QImage image(MAZE_SIZE * TILE_SIZE, MAZE_SIZE * TILE_SIZE, QImage::Format_ARGB32);
	image.fill(Qt::gray);	// BGcolor, unnecessary

	CELL_STATE cell;	// Temporary cell
	QPainter painter(&image);

	// Scaling coefficients
	int cfx = TILE_SIZE;
	int cfy = TILE_SIZE;

	// Draws grid
	for(int i = 1; i < MAZE_SIZE; i++) {
		painter.setOpacity(0.12);
		painter.drawLine(i * cfx, 0, i * cfx, MAZE_SIZE * TILE_SIZE);
		painter.drawLine(0, i * cfy, MAZE_SIZE * TILE_SIZE, i * cfy);
	}
	painter.setOpacity(1.0);

	for(int i = 0; i < MAZE_SIZE; i++) {
		for(int j = 0; j < MAZE_SIZE; j++) {
			cell = maze[i][j];	// For each cell

			switch(cell) {
			case ST_WALL:
				//painter.drawImage(i * cfx, j * cfy, QImage(":/maze/wall"));
				painter.fillRect(i * cfx, j * cfx, MAZE_SIZE, MAZE_SIZE, Qt::black);
			case ST_PERM_WALL:
				//painter.drawImage(i * cfx, j * cfy, QImage(":/maze/wall"));
				painter.fillRect(i * cfx, j * cfx, MAZE_SIZE, MAZE_SIZE, Qt::black);
				break;
			case ST_EMPTY:
				break;
			case ST_FINISH:
				painter.fillRect(i * cfx + 1, j * cfx + 1, MAZE_SIZE - 2, MAZE_SIZE - 2, Qt::darkBlue);
				break;
			case ST_BALL:
				painter.drawImage(i * cfx, j * cfy, QImage(":/maze/ball"));
				break;
			}
		}
	}

	// Returns rendered result
	return image;
}

CELL_STATE Field::getCell(coordinate posit) {
	if((posit.x < 0) || (posit.y < 0) || (posit.x >= MAZE_SIZE) || (posit.y >= MAZE_SIZE))
		return ST_WALL;

	return maze[posit.x][posit.y];
}

CELL_STATE Field::getCell(int x, int y) {
	if((x < 0) || (y < 0) || (x >= MAZE_SIZE) || (y >= MAZE_SIZE))
		return ST_WALL;

	return maze[x][y];
}

void Field::setCell(int x, int y, CELL_STATE st) {
	if((x < 0) || (y < 0) || (x >= MAZE_SIZE) || (y >= MAZE_SIZE))
		return;

	maze[x][y] = st;
}

coordinate Field::placeBall() {
	coordinate temp;
	temp.x = 0;
	temp.y = qrand() % MAZE_SIZE;

	while(getCell(temp.x + 1, temp.y) != ST_EMPTY)
		temp.y = qrand() % MAZE_SIZE;

	maze[temp.x][temp.y] = ST_BALL;

	return temp;
}

void Field::placeFinish() {
	coordinate temp;
	temp.x = MAZE_SIZE - 1;
	temp.y = qrand() % MAZE_SIZE;

	while(getCell(temp.x - 1, temp.y) != ST_EMPTY)
		temp.y = qrand() % MAZE_SIZE;

	maze[temp.x][temp.y] = ST_FINISH;
}
