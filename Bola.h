#pragma once
#include "lib/libreria.h"

//Mides i pas de bola
const int MIDABOLAX = 20;
const int MIDABOLAY = 20;

const int PASBOLAX = 5;
const int PASBOLAY = 5;

class Bola
{
public:
	Bola();
	~Bola();
	void init();
	void setXY(int x, int y);
	void setDirX(int dirX);
	void setDirY(int dirY);
	void rebotVaus(int vausX);
	void draw();
	void mou(int iniPantallaX, int fiPantallaX, int iniPantallaY, int fiPantallaY);
	int getY();
	int getX();
	void changeDirY();
	void changeDirX();
	int getDirX();
	int getDirY();
	int midaY();
	bool tocaVaus(int vausX, int midaVausX);
	void setGlue(bool mod);
	bool getGlue() const;
	int getDirXAux() const;
	void setDirXAux();

private:
	Sprite _bola[2];
	int _x;
	int _y;
	int _dirX;
	int _dirY;
	bool _teGlue;
	int _dirXAux;
};