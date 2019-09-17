#pragma once
#include "lib/libreria.h"
#include "Bola.h"

//Mides i pas de VAUS
const int MIDAVAUSX = 100;
const int MIDAVAUSY = 30;

const int PASVAUSX = 20;

const int COMPROVABOLA = 790;

class Vaus
{
public:
	Vaus();
	~Vaus();
	void draw();
	void setXY(int x, int y);
	int midaX();
	int midaY();
	int getX();
	int pasX();
	void init();
	void mouLeft(int INIPANTALLAX, Bola& bola);
	void mouRight(int FIPANTALLAX, Bola& bola);
	void setMod(bool modificador);
	bool getMod();
	
private:
	Sprite _vaus[2];
	int _x;
	int _y;
	bool _mod;
};