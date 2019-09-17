#include "Paret.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Constructor
Paret::Paret()
{
	inicialitzar();
}

// Destructor
Paret::~Paret()
{
}

// Inicialitzem les files, les columnes, la paret y els grafics
void Paret::inicialitzar()
{
	// Inicialitzem les files y el numero de maons per cada una
	m_files = MAXMAONSY;
	m_nmaons = MAXMAONSX;

	// Inicialitzem la paret tot a 1 (maons amb 1 vida)
	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_nmaons; j++)
		{
			m_paret[i][j] = rand() % /*MAXTOUGH*/ 2 + 1;
		}
	}

	// Crear grafics per cada vida del mao (0 - 1 vida, 1 - 2 vides, etc.)
	m_grafics[0].Create("data/maoBlau.png");
	m_grafics[1].Create("data/maoGris.png");
	m_grafics[2].Create("data/maoGroc.png");
	m_grafics[3].Create("data/maoRosa.png");
	m_grafics[4].Create("data/maoVerd.png");
	m_grafics[5].Create("data/maoVermell.png");
}

// Dibuixar la paret
void Paret::dibuixar()
{
	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_nmaons; j++)
		{
			if (m_paret[i][j] > 0)
			{
				m_grafics[m_paret[i][j] - 1].Draw(INIPANTALLAX + j*MIDAMAO, INIPANTALLAY + i*MIDAMAOY);
			}
		}
	}
}

// Retorna "true" si hem completat el joc
bool Paret::complet()
{
	bool comp = true;
	int i = 0, j = 0;
	while (i < m_files && comp)
	{
		while (j < m_nmaons && comp)
		{
			if (m_paret[i][j] > 0)
			{
				comp = false;
			}
			j++;
		}
		i++;
	}
	return comp;
}

// retorna l'estat d'un maó
int Paret::getEstatBloc(int i, int j)
{

	return m_paret[i][j];

}

// Modifica l'estat del maó quan la bola impacta i encara no està trencat
void Paret::destruirBloc(int i, int j, Modificador &mod)
{
	int random;
	m_paret[i][j] = m_paret[i][j] - 1;
	if ((m_paret[i][j] == 0) && (mod.getPosibleMod() == 0))
	{
		random = rand() % 10 + 1;
		if (random > VALORRANDOMMOD)
		{
		mod.setPosibleMod(random - VALORRANDOMMOD);
			mod.setXY((j*MIDAMAO) + INIPANTALLAX, (i*MIDAMAOY) + INIPANTALLAY);
			mod.draw();
		}
	}
}

// Comprova si la bola ha de rebotar amb algun maó. Retorna els punts nous que s'aconsegueixen al rebotar
int Paret::checkRebot(Bola &bola, Modificador &mod)
{

	int posBolaMaoXEsq;
	int posBolaMaoXDreta;
	int posBolaMaoY;
	bool tocaBolaDalt;
	bool tocaBolaDreta;
	bool tocaBolaEsq;
	bool tocaDosMaoX;

	// Mirem en quin maó està la bola i si està tocant els extrems d'algun maó per l'esquerra, per la dreta o per dalt.
	posicioBola(bola, posBolaMaoXEsq, posBolaMaoXDreta, posBolaMaoY, tocaBolaDalt, tocaBolaDreta, tocaBolaEsq, tocaDosMaoX);

	int punts = 0;

	if (tocaBolaDalt) // La bola està tocant per dalt amb algun maó
	{
		if (tocaDosMaoX) // La bola toca per dalt a dos maons
		{
			// Mirem si el maó de dalt a l'esquerra no està trencat
			if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXEsq) > 0)
			{
				destruirBloc(posBolaMaoY - 1, posBolaMaoXEsq, mod);
				punts++;
			}
			// Mirem si el maó de dalt a la dreta no està trencat
			if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXDreta) > 0)
			{
				destruirBloc(posBolaMaoY - 1, posBolaMaoXDreta, mod);
				punts++;
			}
			if (punts > 0)
				bola.changeDirY(); // Si la bola toca algun maó canvia de direcció
		}
		else
		{// Només tenim un maó a sobre de la bola
			if (tocaBolaEsq) // Estem tocant un mao a l'esquerra de la bola
			{
				if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXEsq) > 0)
				{ // Si el maó de dalt no està trencat el destruim
					destruirBloc(posBolaMaoY - 1, posBolaMaoXEsq, mod);
					punts++;
					//Mirem si el maó de l'esquerra també està actiu 
					if (getEstatBloc(posBolaMaoY, posBolaMaoXEsq - 1) > 0)
					{//Estem en una cantonada
						bola.changeDirY();
						bola.changeDirX();
					}
					else
					{ // nomes tenim el de dalt pero no el del costat
						bola.changeDirY();
					}
				}
				else
				{// No tenim el de dalt
				 // Mirem si esta el del costat esquerre
					if (getEstatBloc(posBolaMaoY, posBolaMaoXEsq - 1) > 0)
					{ // Tenim el del costat, canviem de direccio
						bola.changeDirX();
					}
					else
					{//No tenim ni el de dalt ni el del costat esquerre
					 //Mirem si esta el de la cantonada superior esquerre
						if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXEsq - 1) > 0)
						{//No tenim el de dalt ni el costat nomes el de la cantonada superior esquerra
							destruirBloc(posBolaMaoY - 1, posBolaMaoXEsq - 1, mod);
							punts++;
							bola.changeDirX();
							bola.changeDirY();
						}
					}
				}
			}
			else
			{//Anem dreta
				if (tocaBolaDreta) // Estem tocant un mao a la dreta de la bola
				{
					if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXEsq) > 0)
					{// Si el maó de dalt no està trencat el destruim
						destruirBloc(posBolaMaoY - 1, posBolaMaoXEsq, mod);
						punts++;
						//Mirem si esta el del costat dret
						if (getEstatBloc(posBolaMaoY, posBolaMaoXDreta) > 0)
						{//Estem en una cantonada
							bola.changeDirY();
							bola.changeDirX();
						}
						else
						{//nomes tenim el de dalt pero no el del costat
							bola.changeDirY();
						}
					}
					else
					{//No tenim el de dalt
					 //Mirem si esta el del costat dret
						if (getEstatBloc(posBolaMaoY, posBolaMaoXDreta) > 0)
						{//tenim el del costat, canviem de direcció
							bola.changeDirX();
						}
						else
						{//No tenim ni el de dalt ni el del costat dret
						 //Mirem si esta el de la cantonada superior dreta
							if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXDreta) > 0)
							{//No tenim el de dalt ni el costat nomes el de la cantonada superior dreta
								destruirBloc(posBolaMaoY - 1, posBolaMaoXDreta, mod);
								punts++;
								bola.changeDirX();
								bola.changeDirY();
							}
						}
					}
				}
				else
				{//toca nomes un a dalt i no te res als 
					if (getEstatBloc(posBolaMaoY - 1, posBolaMaoXDreta) > 0)
					{//No tenim el del costat nomes un adalt
						destruirBloc(posBolaMaoY - 1, posBolaMaoXDreta, mod);
						punts++;
						bola.changeDirY();
					}
				}
			}
		}
	}
	else
	{// No toquem un maó per dalt, mirem els laterals
		if (tocaBolaEsq)// tenim un maó a l'esquerra
		{
			if (getEstatBloc(posBolaMaoY, posBolaMaoXEsq - 1) > 0)
			{//Mirem si esta el de esquerra i rebotem
				bola.changeDirX();
			}
		}
		else
		{
			if (tocaBolaDreta)// tenim un maó a la dreta
			{
				if (getEstatBloc(posBolaMaoY, posBolaMaoXDreta) > 0)
				{//Mirem si esta el de l'esquerra i rebotem
					bola.changeDirX();
				}
			}
		}
	}
	return punts;
}

// Retorna en quin maó està la bola i si està tocant algun dels extrems del maó
void Paret::posicioBola(Bola& bola, int& posBolaMaoXEsq, int& posBolaMaoXDreta, int& posBolaMaoY, bool& tocaBolaDalt, bool& tocaBolaDreta, bool& tocaBolaEsq, bool& tocaDosMaoX)
{
	tocaBolaDalt = false;
	tocaBolaDreta = false;
	tocaBolaEsq = false;
	tocaDosMaoX = false;

	// Calculem columna del maó de l'esquerra i la dreta de la bola
	posBolaMaoXEsq = ((bola.getX() - INIPANTALLAX) / MIDAMAO);
	posBolaMaoXDreta = ((bola.getX() + MIDABOLAX - INIPANTALLAX) / MIDAMAO);
	if (bola.getDirX() < 0) //Anem esquerra
	{ // Comprovem si l'esquerra de la bola toca l'extrem del maó
		if ((((bola.getX() - INIPANTALLAX) % MIDAMAO) < -bola.getDirX()) && (posBolaMaoXEsq != 0))
			tocaBolaEsq = true;
	}
	else
	{//Anem dreta
		if (bola.getDirX() > 0)
		{ // Comprovem si la dreta de la bola toca l'extrem del maó
			if (((bola.getX() + MIDABOLAX - INIPANTALLAX) % MIDAMAO) < bola.getDirX())
				if (posBolaMaoXDreta < m_nmaons)
					tocaBolaDreta = true;
		}
	}
	// Comprovem si toquem dos maons
	if (posBolaMaoXEsq != posBolaMaoXDreta)
		tocaDosMaoX = true;
	// Calculem la fila del maó on està la bola
	posBolaMaoY = ((bola.getY() - INIPANTALLAY) / MIDAMAOY);
	if (bola.getDirY() < 0) //Anem adalt
	{// Comprovem si la part de dalt de la bola toca l'extrem del maó
		if (((bola.getY() - INIPANTALLAY) % MIDAMAOY == 0))
		{
			if (posBolaMaoY != 0)
				tocaBolaDalt = true;
		}
	}
	if (posBolaMaoY == m_files)
	{
		tocaBolaDreta = false;
		tocaBolaEsq = false;
	}

}