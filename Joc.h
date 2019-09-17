
///////////////////////////////////////////////////////////////////////////
//Llibreria grafica
#include "lib/libreria.h"
///////////////////////////////////////////////////////////////////////////

#include <conio.h>      /* getch */ 
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include <stdlib.h>

#include "Bola.h"
#include "Vaus.h"
#include "Paret.h"
#include "CuaModificador.h"

//========================================================================
// Mida Pantalla
const int MIDAX = 1080;
const int MIDAY = 850;
//Constants inicialitzacio jocs
const int INITVELOCITATJOC = 4;
const int INITVIDES = 3;
const int INITPUNTS = 0;
//========================================================================
//POSICIONS MARCADORS
const int INIPUNTSX = 700;
const int INIPUNTSY = 50;
const int INIVIDESX = 200;
const int INIVIDESY = 20;
const int ININIVELLX = 200;
const int ININIVELLY = 50;
// Localitzacions Mods Laterals
const int INIMODLATERALX = 987;
const int INIMODLATERALY = 290;
const int MODLATERALYOFFSET = 45;
const int MAXMODSLATERALS = 5;


class Joc
{
public:
	Joc();
	~Joc();
	void inicialitzarJoc();
	void dibuixarElements();
	void inicialitzarGrafics();
	void inicialitzarParametres(int level);
	void mouVausLeft();
	void mouVausRight();
	void moureBola();
	void moureMod();
	void actualizarVides();
	void comprovaBolaInferior();
	void comprovaModInferior();
	void comprovaMurComplet();
	void inicialitzarParet();
	int getNivell();
	void drawNombre(int valor, int posX, int posY);
	void pintarMarcadors();
	int jugar(int nivell);
	int aleatori(int min, int max, int pas);
	void activaMod(int &pause);
	void setBolaAux(bool activar);
	void pintarCua();
	void actualitzarModsLaterals();
	void treureMod();

private:
	Vaus vaus;
	Bola bola;
	Bola bolaAux;
	Sprite fons;
	Paret mur;
	Sprite digits[10];
	Modificador mod;
	CuaModificador cua_mod;
	int mods_Laterals[MAXMODSLATERALS];
	bool _bolaAux;
	int velocitatJoc;
	int contVBola;
	int nivell;
	int vides;
	int punts;
	bool _cambiarControls;
	int _modActiu;
};