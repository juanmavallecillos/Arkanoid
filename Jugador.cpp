#include <string.h>
#include <stdio.h>
#include <stdlib.h>     /* system */
#include "Jugador.h"

// Constructor
Jugador::Jugador()
{
}

// Destructor
Jugador::~Jugador()
{
}

// Guardar nom del Jugador
void Jugador::setNom(char nom[])
{
	for (int i = 0; i < MAX_SIZE_NOM_JUGADOR; i++)
	{
		m_nom[i] = nom[i];
	}
}

// Guardar puntuació del Jugador
void Jugador::setPunts(int punts)
{
	m_punts = punts;
}

// Retornar nom del Jugador
void Jugador::getNom(char *nom) const
{
	for (int i = 0; i < MAX_SIZE_NOM_JUGADOR; i++)
	{
		nom[i] = m_nom[i];
	}
}

// Retornar puntuació del Jugador
int Jugador::getPunts() const
{
	return m_punts;
}