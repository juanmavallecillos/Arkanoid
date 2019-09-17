#include "Modificador.h"

// Constructor Modificador
Modificador::Modificador()
{
	m_nummod = 0;		// Inicialitzem a 0 quin modificador es
	m_posibleMod = 0;	// No hi ha cap modificador a pantalla
	inicialitzar();		// Inicialitzem els grafics de cada modificador
}

// Destructor Modificador
Modificador::~Modificador()
{
}

// Crear grafics per cada modificador
void Modificador::inicialitzar()
{
	m_modificadors[0].Create("data/ModifStop.png");			// Modificador Pause/Stop
	m_modificadors[1].Create("data/ModifVida.png");			// Modificador Vida
	m_modificadors[2].Create("data/ModifMoviment.png");		// Modificador Moviment Invers
	m_modificadors[3].Create("data/ModifBolaDoble.png");	// Modificador Bola Doble
	m_modificadors[4].Create("data/ModifGlue.png");			// Modificador Glue
}

// Si hem agafat un mod, guardar-lo a l'objecte
void Modificador::setMod(int mod)
{
	m_nummod = mod;
}

// Retorna quin mod guarda aquest objecte
int Modificador::getMod() const
{
	return m_nummod;
}

// Pintar el modificador quan baixa
void Modificador::draw()
{
	if (m_posibleMod != 0)
	{
		m_modificadors[m_posibleMod - 1].Draw(m_x, m_y);
	}
}

// Pintar els modificadors a la dreta de la pantalla
void Modificador::drawLateral(int x, int y, int mod)
{
	m_modificadors[mod - 1].Draw(x, y);
}

// Moviment del modificador quan baixa
void Modificador::mou(int fiPantallaY)
{
	m_y += 1;
}

// Retorna la midaX del modificador
int Modificador::midaX()
{
	return MIDAMODX;
}

// Retorna la midaY del modificador
int Modificador::midaY()
{
	return MIDAMODY;
}

// Retorna la posicióY del modificador
int Modificador::getY()
{
	return m_y;
}

// Retorna la posicióX del modificador
int Modificador::getX()
{
	return m_x;
}

// Si el modificador toca la nau Vaus retorna "true"
bool Modificador::tocaVaus(int vausX, int midaVausX)
{
	return (((m_x > vausX) && (m_x < vausX + midaVausX)) || (((m_x + MIDAMODX) > vausX) && (m_x + MIDAMODX) < vausX + midaVausX));
}

// Inicialitzar la posició del modificador
void Modificador::setXY(int x, int y)
{
	m_x = x;
	m_y = y;
}

// Guardem quin modificador es posible que agafem amb la nau ja que esta baixant encara
void Modificador::setPosibleMod(int num)
{
	m_posibleMod = num;
}

// Retornem el valor del posible modificador que agafem
int Modificador::getPosibleMod()
{
	return m_posibleMod;
}