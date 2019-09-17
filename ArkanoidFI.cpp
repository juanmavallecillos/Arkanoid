// ArkanoidFI.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED

#include <windows.h>
#include "Menu.h"
#include "Joc.h" //Aquest inclou llibreria grafica
#include "TaulaJugadors.h"
#include <conio.h>      /* getch */ 

#define JUGAR '1'
#define CONFIGURAR '2'
#define PUNTUACIO '3'
#define SORTIR '4'

//Arguments necesaris per poder incloure la llibreria i que trobi el main
void main(int argc, char* argv[])
{
	//Instruccions necesaries per poder incloure la llibreria i que trobi el main
	SDL_SetMainReady();
	//SDL_Init(SDL_INIT_VIDEO);
	///////////////////////////////////////////////////////////////////////////
	char opcio;
	int posicio = -1;
	int punts;
	Joc arkanoid;

	char nivell = '1';

	TaulaJugadors millorsJugadors;

	do {
		menuPrincipal();
		opcio = _getch();

		switch (opcio)
		{
		case JUGAR:
			punts = arkanoid.jugar(nivell - '0');
			posicio = millorsJugadors.esMillorPuntuacio(punts);

			if (posicio >= 0)
			{
				system("cls");
				millorsJugadors.desplacaArray(posicio);
				millorsJugadors.emplenaPosicioArray(posicio, punts);
			}
			break;

		case CONFIGURAR:
			do {
				menuNivellDificultat();
				nivell = _getch();
				if ((nivell != '1') && (nivell != '2') && (nivell != '3'))
				{
					printf("Opcio incorrecta.\n");
					Sleep(200);
				}
			} while ((nivell != '1') && (nivell != '2') && (nivell != '3'));
			break;
		case PUNTUACIO:
			millorsJugadors.escriuRanking();
			printf("Prem una tecla per tornar al menu principal");
			_getch();
			break;
		}
	} while (opcio != SORTIR);

	//Instruccio necesaria per poder incloure la llibreria i que trobi el main
	//SDL_Quit();
	///////////////////////////////////////////////////////////////////////////

}

