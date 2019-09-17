#include "Vaus.h"

// Constructor
Vaus::Vaus()
{
	init();
}

// Destructor
Vaus::~Vaus()
{
}

// Pintar la nau Vaus
void Vaus::draw()
{
	if (_mod)
	{
		_vaus[1].Draw(_x, _y);	// Si te modificador agafat
	}
	else
	{
		_vaus[0].Draw(_x, _y);	// Si no en te modificador agafat
	}

}

// Inicialitzar la posició de la nau Vaus
void Vaus::setXY(int x, int y)
{
	_x = x;
	_y = y;

}

// Moviment de la Vaus cap a l'esquerra
void Vaus::mouLeft(int iniPantallaX, Bola& bola)
{
	if ((bola.getGlue()) && (_x >= iniPantallaX + PASVAUSX) && (bola.getY() == COMPROVABOLA - bola.midaY())) // En cas de que la Bola tingui Glue, es moura juntament amb la nau Vaus
	{
		_x -= PASVAUSX;
		bola.setXY(bola.getX() - PASVAUSX, bola.getY());
	}
	else
	{
		if (_x >= iniPantallaX + PASVAUSX)																	// Si no, es moura unicament la nau Vaus
			_x -= PASVAUSX;
	}
}

// Moviment de la Vaus cap a la dreta
void Vaus::mouRight(int fiPantallaX, Bola& bola)
{
	if ((bola.getGlue()) && (_x <= (fiPantallaX - (MIDAVAUSX + PASVAUSX))) && (bola.getY() == COMPROVABOLA - bola.midaY()))	// En cas de que la Bola tingui Glue, es moura juntament amb la nau Vaus
	{
		_x += PASVAUSX;
		bola.setXY(bola.getX() + PASVAUSX, bola.getY());
	}
	else
	{
		if (_x <= (fiPantallaX - (MIDAVAUSX + PASVAUSX)))																	// Si no, es moura unicament la nau Vaus
			_x += PASVAUSX;
	}
}

// Inicialització de l'objecte
void Vaus::init()
{
	_vaus[0].Create("data/vaus.png");		// Vaus normal
	_vaus[1].Create("data/vausMod.png");	// Vaus amb modificador
	_mod = false;							// Inicialment no te cap modificador
}

// Retorna la midaX de la Vaus
int Vaus::midaX()
{
	return MIDAVAUSX;
}

// Retorna la posicóX de la Vaus
int Vaus::getX()
{
	return _x;
}

// Retorna la midaY de la Vaus
int Vaus::midaY()
{
	return MIDAVAUSY;
}

// Retorna el PasX de la Vaus
int Vaus::pasX()
{
	return PASVAUSX;
}

// Es guarda "true" en cas d'agafar un modificador
void Vaus::setMod(bool modificador)
{
	_mod = modificador;
}

// Retorna "true" si tenim algun modificador per activar
bool Vaus::getMod()
{
	return _mod;
}
