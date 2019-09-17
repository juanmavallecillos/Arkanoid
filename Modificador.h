#pragma once
#include "lib\libreria.h"

const int NMODIFICADORS = 5;

//Mides del modificador
const int MIDAMODX = 60;
const int MIDAMODY = 30;

class Modificador
{
public:
	Modificador();
	~Modificador();
	void inicialitzar();
	void setMod(int mod);
	int getMod() const;
	void draw();
	void mou(int fiPantallaY);
	void setXY(int x, int y);
	int midaX();
	int midaY();
	int getY();
	int getX();
	bool tocaVaus(int vausX, int midaVausX);
	void setPosibleMod(int num);
	int getPosibleMod();
	void drawLateral(int x, int y, int mod);

private:
	Sprite m_modificadors[NMODIFICADORS];
	int m_nummod;
	int m_x;
	int m_y;
	int m_posibleMod;
};