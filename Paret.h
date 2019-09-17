#include "lib\libreria.h"
#include "Bola.h"
#include "Modificador.h"

//Mida i nombre maons mur
const int MIDAMAO = 60;
const int MAXMAONSX = 15;
const int MAXMAONSY = 5; //aixo variara
const int MIDAMAOY = 30;
const int MAXTOUGH = 6;

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INIPANTALLAX = 30;
const int INIPANTALLAY = 130;

//========================================================================
// Fi del taulell respecte la cantonada inferior dreta
const int FIPANTALLAX = 930;
const int FIPANTALLAY = 790;

const int VALORRANDOMMOD = 5;

class Paret {
public:
	Paret();
	~Paret();
	void inicialitzar();
	void dibuixar();
	bool complet();
	int getEstatBloc(int i, int j);
	int checkRebot(Bola &bola, Modificador &mod);
	void destruirBloc(int i, int j, Modificador &mod);
	void posicioBola(Bola& bola, int& posBolaMaoXEsq, int& posBolaMaoXDreta, int& posBolaMaoY, bool& tocaBolaDalt, bool& tocaBolaDreta, bool& tocaBolaEsq, bool& tocaDosMaoX);

private:
	int m_nmaons;
	int m_files;
	int m_paret[MAXMAONSY][MAXMAONSX];
	Sprite m_grafics[MAXTOUGH];
};