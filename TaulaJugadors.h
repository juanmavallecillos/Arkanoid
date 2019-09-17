#include <fstream>
#include <string>
#include "Jugador.h"

using namespace std;

const int MAXMILLORSJUGADORS = 5;

class TaulaJugadors
{
public:
	TaulaJugadors();
	~TaulaJugadors();
	int  esMillorPuntuacio(int punts);
	void desplacaArray(int posicio);
	void emplenaPosicioArray(int posicio, int punts);
	void escriuRanking();
	string getNomFitxer() const;

private:
	Jugador m_jugadors[MAXMILLORSJUGADORS];
	string nomFitxer;
};