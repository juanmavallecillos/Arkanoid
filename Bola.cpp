#include "Bola.h"

// Constructor
Bola::Bola()
{
	init();
}

// Destructor
Bola::~Bola()
{
}

// Inicialitzaci� de l'objecte Bola
void Bola::init()
{
	_bola[0].Create("data/bola.png");		// Grafic Bola normal
	_bola[1].Create("data/bolaGlue.png");	// Grafic Bola amb modificador Glue
	_teGlue = false;						// Inicialitzem la Bola sense Glue
}

// Inicialitzem la posici� de la Bola
void Bola::setXY(int x, int y)
{
	_x = x;
	_y = y;
}

// Inicialitzem la direcci�X de moviment de la Bola
void Bola::setDirX(int dirX)
{
	_dirX = dirX;
}

// Inicialitzem la direcci�Y de moviment de la Bola
void Bola::setDirY(int dirY)
{
	_dirY = dirY;
}

// Pintem la Bola
void Bola::draw()
{
	if (_teGlue)
	{
		_bola[1].Draw(_x, _y);	// Si te Glue
	}
	else
	{
		_bola[0].Draw(_x, _y);	// Si no te Glue
	}
}

// Moviment de la Bola vigilant que no surti dels limits de joc
void Bola::mou(int iniPantallaX, int fiPantallaX, int iniPantallaY, int fiPantallaY)
{
	_y += _dirY;
	_x += _dirX;

	if (_x <= iniPantallaX || _x >= fiPantallaX - MIDABOLAX)
	{
		_dirX *= -1;
		_x += _dirX;
	}

	if (_y == iniPantallaY || _y == fiPantallaY - MIDABOLAY)
		_dirY *= -1;
}

// Retorna la posici�Y de la Bola
int Bola::getY()
{
	return _y;
}

// Retorna la posici�X de la Bola
int Bola::getX()
{
	return _x;
}

// Canvia de direcci�Y la Bola
void Bola::changeDirY()
{
	_dirY *= -1;
}

// Canvia la direcci�X de la Bola
void Bola::changeDirX()
{
	_dirX *= -1;
}

// Retorna la midaY de la Bola
int Bola::midaY()
{
	return MIDABOLAY;
}

// Retorna la direcci�X de la Bola
int Bola::getDirX()
{
	return _dirX;
}

// Retorna la direcci�Y de la Bola
int Bola::getDirY()
{
	return _dirY;
}

// Retorna "true" si la Bola toca la nau Vaus
bool Bola::tocaVaus(int vausX, int midaVausX)
{
	return ((_x >= (vausX - (MIDABOLAX / 2))) && (_x <= (vausX + midaVausX + (MIDABOLAX / 2))));
}

// Canvia la direcci�X de la Bola segons la posici� de rebot a la nau Vaus
void Bola::rebotVaus(int vausX)
{
	int aux = (vausX - _x) / 10;
	
	if (aux >= -1)
		_dirX = -2;
	else if (aux >= -3)
		_dirX = -1;
	else if (aux >= -5)
		_dirX = -0;
	else if (aux >= -7)
		_dirX = 1;
	else if (aux >= -9)
		_dirX = 2;
}

// Posem Glue a la Bola
void Bola::setGlue(bool mod)
{
	_teGlue = mod;
}

// Retornem "true" si la Bola te Glue
bool Bola::getGlue() const
{
	return _teGlue;
}

// Retorna la direcci� que tenia la Bola avans d'aturar-se
int Bola::getDirXAux() const
{
	return _dirXAux;
}

// Guarda la direcci�X que t� la Bola en el mateix instant
void Bola::setDirXAux()
{
	_dirXAux = _dirX;
}