#include "TaulaJugadors.h"

// Constructor. Cada vegada que inicialitzem el Joc s'importa
// la llista de millors puntuacions del Joc
TaulaJugadors::TaulaJugadors()
{
	nomFitxer = "LlistaJugadors.txt";
	ifstream fitxerJugadors;
	fitxerJugadors.open(nomFitxer);

	if (fitxerJugadors.is_open())
	{
		char nom[MAX_SIZE_NOM_JUGADOR];
		char espai[2];
		int punts;
		fitxerJugadors.getline(nom, MAX_SIZE_NOM_JUGADOR, '\n');
		fitxerJugadors >> punts;
		fitxerJugadors.getline(espai, '\n');
		int i = 0;
		while (!fitxerJugadors.eof() && i < MAXMILLORSJUGADORS)
		{
			m_jugadors[i].setNom(nom);
			m_jugadors[i].setPunts(punts);
			fitxerJugadors.getline(nom, MAX_SIZE_NOM_JUGADOR, '\n');
			fitxerJugadors >> punts;
			fitxerJugadors.getline(espai, '\n');
			i++;
		}
		m_jugadors[i].setNom(nom);
		m_jugadors[i].setPunts(punts);
		fitxerJugadors.close();
	}
}

// Destructor
TaulaJugadors::~TaulaJugadors()
{
}

// Retorna el nom del fitxer
string TaulaJugadors::getNomFitxer() const
{
	return nomFitxer;
}

// Retorna la posicio de la llista a la que anira la puntuacio
// en cas que estigui al top 5
int TaulaJugadors::esMillorPuntuacio(int punts)
{
	int i = 0;
	int trobat = 0;

	do
	{
		if (m_jugadors[i].getPunts()<punts)
		{
			trobat = 1;
		}
		i++;

	} while ((i<MAXMILLORSJUGADORS) && (!trobat));

	if (trobat)
	{
		return (i - 1);
	}
	else
	{
		return -1;
	}
}

// Desplaçem les posicions del array de puntuacions per afegir-hi una nova
void TaulaJugadors::desplacaArray(int posicio)
{
	int i;

	for (i = MAXMILLORSJUGADORS - 1; i>posicio; i--)
	{
		char nom[MAX_SIZE_NOM_JUGADOR];
		m_jugadors[i - 1].getNom(nom);
		m_jugadors[i].setNom(nom);
		m_jugadors[i].setPunts(m_jugadors[i - 1].getPunts());
	}
}

// Emplenem la posició buida de l'array
void TaulaJugadors::emplenaPosicioArray(int posicio, int punts)
{
	char nom[MAX_SIZE_NOM_JUGADOR];
	system("cls");
	printf("Entra el teu nom\n");
	gets_s(nom);
	m_jugadors[posicio].setNom(nom);
	m_jugadors[posicio].setPunts(punts);

	ofstream fitxerJugadors;
	fitxerJugadors.open(getNomFitxer());
	if (fitxerJugadors.is_open())
	{
		int i = 0;
		char nom[MAX_SIZE_NOM_JUGADOR];
		int punts;
		while (i < MAXMILLORSJUGADORS - 1)
		{
			m_jugadors[i].getNom(nom);
			punts = m_jugadors[i].getPunts();
			fitxerJugadors << nom << endl;
			fitxerJugadors << punts << endl;
			i++;
		}
		m_jugadors[i].getNom(nom);
		punts = m_jugadors[i].getPunts();
		fitxerJugadors << nom << endl;
		fitxerJugadors << punts;
		fitxerJugadors.close();
	}
}

// Mostrar per pantalla el Ranking
void TaulaJugadors::escriuRanking()
{
	int i;
	char nom[MAX_SIZE_NOM_JUGADOR];
	system("cls");
	for (i = 0; i<MAXMILLORSJUGADORS; i++)
	{
		m_jugadors[i].getNom(nom);
		printf("%d.- %s %d\n", i + 1, nom, m_jugadors[i].getPunts());
	}

}
