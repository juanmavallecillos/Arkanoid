#include "Joc.h"

Joc::Joc()
{
	inicialitzarGrafics();
}

Joc::~Joc()
{
}

// Inicialitzar totes les variables del Joc.
void Joc::inicialitzarJoc()
{

	vaus.setXY(aleatori(INIPANTALLAX, (FIPANTALLAX - vaus.midaX()), vaus.pasX()), FIPANTALLAY); // Inicialitzem la posició de la Vaus
	bola.setXY(vaus.getX(), FIPANTALLAY - vaus.midaY());										// Inicialitzem la posició de la Bola
	mod.setPosibleMod(0);																		// Inicialitzem el posible modificador a 0
	_bolaAux = false;																			// Inicialitzem sense cap bola auxiliar
	bola.setDirX(aleatori(-1, 1, 1));															// Inicialitzem la direccióX de moviment de la Bola 
	bola.setDirY(-1);																			// Inicialitzem la direccióY de moviment de la Bola
	cua_mod.~CuaModificador();																	// Inicialitzem sense modificadors la nostra cua de modificadors
	vaus.setMod(false);																			// Inicialitzem la Vaus sense cap modificador agafat
	for (int i = 0; i < MAXMODSLATERALS; i++)													// Inicialitzem la llista de modificadors de la dreta tots a 0
	{
		mods_Laterals[i] = 0;
	}
	_cambiarControls = false;																	// Els controls s'inicialitzem per default
	bola.setGlue(false);																		// Modificador Glue desactivat
	_modActiu = 0;																				// No hi ha cap modificador actiu quan inicialitzem el joc
}

// Inicialitzar el mur de maons.
void Joc::inicialitzarParet()
{
	mur.inicialitzar();
}

// Inicialitzar els Marcadors i la velocitat del joc
void Joc::inicialitzarParametres(int level)
{
	velocitatJoc = INITVELOCITATJOC;	// Inicialitzem la velocitat de Joc
	vides = INITVIDES;					// Inicialitzem les vides
	punts = INITPUNTS;					// Inicialitzem els punts
	nivell = level;						// Inicialitzem el nivell
}

// Pintar els 5 modificadors següents a la dreta de la pantalla
void Joc::pintarCua() 
{
	if (mods_Laterals[0] != 0)
	{
		mod.drawLateral(INIMODLATERALX, INIMODLATERALY, mods_Laterals[0]);											// Pintem el primer modificador
		if (mods_Laterals[1] != 0)
		{
			mod.drawLateral(INIMODLATERALX, INIMODLATERALY + MODLATERALYOFFSET, mods_Laterals[1]);					// Pintem el segon modificador
			if (mods_Laterals[2] != 0)
			{
				mod.drawLateral(INIMODLATERALX, INIMODLATERALY + 2*MODLATERALYOFFSET, mods_Laterals[2]);			// Pintem el tercer modificador
				if (mods_Laterals[3] != 0)
				{
					mod.drawLateral(INIMODLATERALX, INIMODLATERALY + 3*MODLATERALYOFFSET, mods_Laterals[3]);		// Pintem el quart modificador
					if (mods_Laterals[4] != 0)
					{
						mod.drawLateral(INIMODLATERALX, INIMODLATERALY + 4*MODLATERALYOFFSET, mods_Laterals[4]);	// Pintem el cinquè modificador
					}
				}
			}
		}
	}
}

// Cada vegada que s'agafa o s'activa un modificador,
// hem d'actualitzar la llista dels modificadors de la dreta de la pantalla
void Joc::actualitzarModsLaterals()
{
	NodeModificador* aux;
	aux = cua_mod.getNode();
	if (!cua_mod.esBuida())
	{
		mods_Laterals[0] = (*aux).getValor().getMod();						// Diem el primer modificador
		aux = (*aux).getNext();
		if (aux != NULL)
		{
			mods_Laterals[1] = (*aux).getValor().getMod();					// Diem el segon modificador
			aux = (*aux).getNext();
			if (aux != NULL)
			{
				mods_Laterals[2] = (*aux).getValor().getMod();				// Diem el tercer modificador
				aux = (*aux).getNext();
				if (aux != NULL)
				{
					mods_Laterals[3] = (*aux).getValor().getMod();			// Diem el quart modificador
					aux = (*aux).getNext();
					if (aux != NULL)
					{
						mods_Laterals[4] = (*aux).getValor().getMod();		// Diem el cinquè modificador
					}
				}
			}
		}
	}
}

// Inicialitzar tots els grafics del joc (bola, vaus, fons, modificadors, digits)
void Joc::inicialitzarGrafics()
{
	fons.Create("data/fons.png");						// Inicialitzar fons
	bola.init();										// Inicialitzar pilota
	bolaAux.init();										// Inicialitzar pilota auxiliar
	vaus.init();										// Inicialitzar Vaus
	mod.inicialitzar();									// Inicialitzar modificadors
	digits[0].Create("data/numeros/numero0000.png");	//////////////////////////////////////
	digits[1].Create("data/numeros/numero0001.png");	//
	digits[2].Create("data/numeros/numero0002.png");	//
	digits[3].Create("data/numeros/numero0003.png");	//
	digits[4].Create("data/numeros/numero0004.png");	// Inicialitzar numeros dels marcadors
	digits[5].Create("data/numeros/numero0005.png");	//
	digits[6].Create("data/numeros/numero0006.png");	//
	digits[7].Create("data/numeros/numero0007.png");	//
	digits[8].Create("data/numeros/numero0008.png");	//
	digits[9].Create("data/numeros/numero0009.png");	//////////////////////////////////////
}

// Dibuixem tots els elements del joc
void Joc::dibuixarElements()
{
	fons.Draw(0, 0);		// Pintem Fons
	vaus.draw();			// Pintem vaus
	bola.draw();			// Pintem Pilota
	if (_bolaAux)			// Pintem bola auxiliar si modificador activat
	{
		bolaAux.draw();
	}
	mur.dibuixar();			// Dibuixar mur
	mod.draw();				// Pintem modificador
	pintarCua();			// Pintem els proxims modificadors a la dreta de la pantalla
}

// Moviment de la Vaus a l'esquerra
void Joc::mouVausLeft()
{
	vaus.mouLeft(INIPANTALLAX, bola);
}

// Moviment de la Vaus a la dreta
void Joc::mouVausRight()
{
	vaus.mouRight(FIPANTALLAX, bola);
}

// Moviment de les dues boles
void Joc::moureBola()
{
	bola.mou(INIPANTALLAX, FIPANTALLAX, INIPANTALLAY, FIPANTALLAY); // Movem la bola principal
	if (_bolaAux)
	{
		bolaAux.mou(INIPANTALLAX, FIPANTALLAX, INIPANTALLAY, FIPANTALLAY); // Si hi ha segona bola, mourela independentment de la primera
	}
}

// Moure el modificador quan cau del mur
void Joc::moureMod()
{
	mod.mou(FIPANTALLAY);
}

// Restar vides quan perdem
void Joc::actualizarVides()
{
	vides--;
}

// Comprovar si la Bola toca la Vaus o no
void Joc::comprovaBolaInferior()
{
	// Comprovació de la bola principal
	if (bola.getY() == FIPANTALLAY - bola.midaY())
	{
		if (bola.tocaVaus(vaus.getX(), vaus.midaX()))
		{
			bola.rebotVaus(vaus.getX());
			if (bola.getGlue())			// Si tenim el mod Glue actiu
			{
				bola.setDirY(0);		// La pilota no es mou verticalment
				bola.setDirXAux();		// Guardem la direcció X en la que hauria d'anar
				bola.setDirX(0);		// Tampoc es mou horitzontalment
			}
		}
		else
		{
			if (_bolaAux)				// Si perdem la bola principal i hi ha una segona bola en joc
			{
				bola = bolaAux;			// La vola auxiliar pasa a ser la principal
				_modActiu = 0;			// Es desactiva el modificador Bola Doble
				setBolaAux(false);		// Diem a la clase Joc que no hi ha bola doble
			}
			else						// Si perdem la bola principal i no hi ha segona bola
			{
				vides--;				// Decrementem les vides
				inicialitzarJoc();		// Tornem a inicialitzar el joc
			}
		}
	}
	if (_bolaAux)
	{
		if (bolaAux.getY() == FIPANTALLAY - bola.midaY())
		{
			if (bolaAux.tocaVaus(vaus.getX(), vaus.midaX()))
			{
				bolaAux.rebotVaus(vaus.getX());
			}
			else
			{
				setBolaAux(false);
				_modActiu = 0;
			}
		}
	}
}

// Comprovar si hem agafat el modificador amb la Vaus o no
void Joc::comprovaModInferior()
{
	if (mod.getY() == FIPANTALLAY - mod.midaY())
	{
		if (mod.tocaVaus(vaus.getX(), vaus.midaX()))
		{
			vaus.setMod(true);					// Si el mod toca la nau Vaus, aquesta l'agafa i canvia de color
			mod.setMod(mod.getPosibleMod());	// Indiquem quin modificador hem agafat
			mod.setPosibleMod(0);				// Desapareix el bloc del modificador de la pantalla
			cua_mod.afegeix(mod);				// Afegim el modificador a la cua de modificadors
			actualitzarModsLaterals();			// Actualitzem els modificadors de la llista de la dreta de la pantalla
		}
		else
		{
			mod.setPosibleMod(0);				// Si no agafem el modificador, s'elimina de la pantalla de joc
		}

	}
}

// Comprovar si hem trencat el Mur
void Joc::comprovaMurComplet()
{
	if (mur.complet())
	{
		punts *= 2;				// Si el mur esta complet, es multipliquen
		nivell++;				// els punts actuals x2, augmenta el nivell
		inicialitzarJoc();		// i es torna a inicialitzar tant el joc
		inicialitzarParet();	// com la paret
	}
}

// Retorna el nivell actual
int Joc::getNivell()
{
	return nivell;
}

// Retorna un nombre aleatori entre min i max amb un pas enter
// si donem min = 1 max=100 i pas=10 donara nombres possibles:1,10,20,30,40,50,60,70,80,90,100
int Joc::aleatori(int min, int max, int pas)
{
	int aleat = ( ( rand() %( ((max-min)/pas) - 1) ) * pas ) + min; 
	return aleat;
}

// Dibuixa un numero a la pantalla, a la posicío (posX,posY) utilitzant els gràfics de la llibreria
// S'utilitza per mostrar la puntuació
void Joc::drawNombre(int valor, int posX, int posY)
{
	int divisor = 100;
	int posXActual = posX;
	int nActual = valor;
	bool primerDigit = true;
	int pasDigit = 20;

	while (divisor > 0)
	{
		int d = nActual / divisor;
		nActual = nActual % divisor;
		divisor = divisor / 10;

		if ((d > 0) || !primerDigit || (divisor == 0))
		{
			digits[d].Draw(posXActual, posY);
			primerDigit = false;
		}

		posXActual += pasDigit;
	}
}

// Pintar els marcadors (punts, vides, nivell actual)
void Joc::pintarMarcadors()
{
	drawNombre(punts, INIPUNTSX, INIPUNTSY); // Pintar punts
	drawNombre(vides, INIVIDESX, INIVIDESY); // Pintar vides
	drawNombre(nivell, ININIVELLX, ININIVELLY); // Pintar nivell
}

// Quan premem la tecla M s'activa el primer modificador de la cua
void Joc::activaMod(int &pause)
{
	bool treu = false; // Aquesta variable serveix per no alliberar el modificador de la bola doble en cas de que ja hi hagi dues boles en el joc
	if (cua_mod.getPrimer().getMod() == 1) // Modificador Pause
	{
		pause = 1500;
		treu = true;
	}
	else
	{
		if (cua_mod.getPrimer().getMod() == 2) // Modificador Vides
		{
			vides += 1;
			treu = true;
		}
		else
		{
			if (cua_mod.getPrimer().getMod() == 3) // Modificador Moviment (cambia el sentit dels controls), si es torna a activar el mateix mod,  es desactiva
			{
				if (!_cambiarControls)
				{
					_cambiarControls = true;
				}
				else
				{
					_cambiarControls = false;
				}
				treu = true;
			}
			else
			{
				if ((cua_mod.getPrimer().getMod() == 4) && (!_bolaAux) && (_modActiu != 2)) // Modificador Doble Bola, només es pot tenir 2 boles en joc i el mod Glue no ha d'estar actiu
				{
					setBolaAux(true);
					_modActiu = 1;
					treu = true;
				}
				else
				{
					if ((cua_mod.getPrimer().getMod() == 5) && (_modActiu != 1)) // Modificador Glue. No pot estar actiu mentre tenim 2 boles en joc
					{
						bola.setGlue(true);
						_modActiu = 2;
						treu = true;
					}
				}
			}
		}
	}
	if (treu) // Cal posar aquesta comprovació per a que no s'activin certs modificadors quan no toca
	{
		cua_mod.treu();
		treureMod();
		actualitzarModsLaterals();
	}
}

// Treure modificador de la llista dels 5 próxims modificadors
void Joc::treureMod()
{
	mods_Laterals[0] = mods_Laterals[1]; // Mod 2 pasa a la posició 1
	mods_Laterals[1] = mods_Laterals[2]; // Mod 3 pasa a la posició 2
	mods_Laterals[2] = mods_Laterals[3]; // Mod 4 pasa a la posició 3
	mods_Laterals[3] = mods_Laterals[4]; // Mod 5 pasa a la posició 4
	mods_Laterals[4] = 0;				 // Es posa a 0  la posició 5
}

// Quan activem el mod DobleBola, posar en marcha la segona bola
void Joc::setBolaAux(bool activar)
{
	_bolaAux = activar; // Activem la segona bola
	if (_bolaAux)
	{
		bolaAux.setXY(vaus.getX(), FIPANTALLAY - vaus.midaY()); // Inicialitzem els parametres de la bola auxiliar
		bolaAux.setDirX(aleatori(-1, 1, 1));					// de manera que el seu moviment es independent
		bolaAux.setDirY(-1);									// al de la bola principal
	}
}

//-----------------------------------------
// joc: porta el control de tot el joc, pantalles, vides etc
// ara nomes acaba si perdem totes les vides (3) perque no tenim el mur
// quan tinguem el mur al destruir-la tota ens augmentara el nivell i ens donara punts
// in: nivell: segons sigui mes alt la bola anira mes depressa
//-----------------------------------------
int Joc::jugar(int nivell)
{
	int modPause = 0;
	// ********************************************
	// Inicialització de la part gràfica del joc
	// *******************************************
	//Inicialitza Part grafica
	Game jocLib(MIDAX, MIDAY);
	// Inicialitzacions necessàries
	jocLib.Init();

	inicialitzarGrafics();

	// ************************************************************
	// Inicialitzacions dels paràmetres del joc
	// ************************************************************
	inicialitzarParametres(nivell);
	int contVBola;
	int contVMod;
	//Inizialitzar llavor per a la funció rand()
	srand((unsigned)time(NULL));


	// ****************************************************************************
	// Bucle principal del joc
	// Hi ha dos bucles anidats: l'exterior controla tota la partida mentre que 
	// l'interior controla un nivell del joc fins que ens quedem sense vides
	// *****************************************************************************
	do{
		inicialitzarJoc();
		inicialitzarParet();


		// ***********************************************************************
		//Mostrem finestra
		jocLib.Video_ShowWindow();
	
		dibuixarElements();

		// Pintem marcadors
		pintarMarcadors();

		// Actualitza la pantalla i ara veiem tot el que hem pintat
		jocLib.VideoUpdate();

		// Inicialització de variable que permet indicar velocitat de la bola segons nivell
		// quan contbola arriba a zero permet moure la bola. aixo deixa temps per moure la vaus.
		contVBola = velocitatJoc / getNivell();
		contVMod = (velocitatJoc / getNivell()) * 2;

		do
		{
			// ******************************************************************
			// Captura i processa les tecles que s'hagin pressionat
			// ******************************************************************
			
			// Captura els events que s'han produit en el darrer cicle
			jocLib.ProcessEvents(); 

			// Captura del moviment de la nau vaus fet pel jugador
			if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
			{
				if (_cambiarControls)
				{
					mouVausRight();
				}
				else
				{
					//si hem donat a fletxa esquerra nou la vaus a esquerra si no sortim de tauler
					mouVausLeft();
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
			{
				if (_cambiarControls)
				{
					mouVausLeft();
				}
				else
				{
					//si hem donat a fletxa dreta nou la vaus a dreta si no sortim de tauler
					mouVausRight();
				}
			}
			// ********************************************************************************
			// PER AFEGIR: Comprovar si s'ha pressionat la tecla ESPAI per fer una pausa al joc
			// Recordeu que s'ha de fer un jocLib.ProcessEvents(); cada cop que voleu llegir events de teclat
			else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
			{
				jocLib.ProcessEvents();

				while (!Keyboard_GetKeyTrg(KEYBOARD_SPACE))
				{
					jocLib.ProcessEvents();
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_M))
			{
				//si hem donat a la tecla M alliberem modificador
				if (vaus.getMod())
				{
					activaMod(modPause);
					if (cua_mod.esBuida())
					{
						vaus.setMod(false);
					}
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
			{
				if ((bola.getGlue()) && (bola.getDirY() == 0))
				{
					bola.setDirY(-1);
					bola.setDirX(bola.getDirXAux());
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
			{
				if (_modActiu == 2)
				{
					_modActiu = 0;
					bola.setGlue(false);
					if (bola.getY() == FIPANTALLAY - bola.midaY())
					{
						bola.setDirY(-1);
						bola.setDirX(bola.getDirXAux());
					}
				}
			}
			// ********************************************************************************

			// ********************************************************************************
			// MOVIMENT DE LA BOLA
			// ********************************************************************************
			// Moviment de la pilota amb retard respecte la nau, controlat per contVBola
			contVBola--;

			if(!contVBola && (!modPause))
			{
				// movem la bola segons dirX i dirY controlant marges
				moureBola();
				//posa comptador una altra vegada a inici per poder moure vaus
				contVBola = velocitatJoc / getNivell();
			
				// ******************************************************************************
				// PER MODIFICAR: Quan tinguem el mur s'haurà de comprovar si la bola toca el mur
				// i si és així, mirar si destrueix algun dels blocs
				// ******************************************************************************
				// Comprovem si la bola arriba al límit superior del tauler
				if (bola.getY() <= INIPANTALLAY + (MIDAMAOY * 5))
				{
					if (_cambiarControls)
					{
						punts += (2 * mur.checkRebot(bola, mod));
					}
					else
					{
						punts += mur.checkRebot(bola, mod);
					}
				}
				//Si hi ha bola auxiliar, comprovem si la bola arriba al límit superior del tauler
				if (_bolaAux)
				{
					if (bolaAux.getY() <= INIPANTALLAY + (MIDAMAOY * 5))
					{
						if (_cambiarControls)
						{
							punts += (2 * mur.checkRebot(bolaAux, mod));
						}
						else
						{
							punts += mur.checkRebot(bolaAux, mod);
						}
					}
				}
			
				// Comprovem si la bola arriba al límit inferior de la pantalla i, en aquest cas
				// si rebota a la nau o s'escapa i perdem una vida
				comprovaBolaInferior();
			
				// **************************************************************************
				// PER AFEGIR: Comprovar si s'ha destruit el mur. En aquest cas, sumar punts,
				// crear de nou el mur i canviar de nivell
				comprovaMurComplet();
				// **************************************************************************
			}
			else
			{
				if (modPause > 0)
				{
					modPause--;
					contVBola = velocitatJoc / getNivell();
				}
			}
			// ********************************************************************************
			// MOVIMENT DEL MODIFICADOR
			// ********************************************************************************
			if (mod.getPosibleMod() != 0)
			{
				contVMod--;
				if (!contVMod)
				{
					moureMod();
					//posa comptador una altra vegada a inici per poder moure vaus
					contVMod = (velocitatJoc / getNivell()) * 2;

					// Comprovem si el modificador arriba al límit inferior de la pantalla i, en aquest cas
					// si l'agafa la nau o s'escapa
					comprovaModInferior();
				}
			}

			// ***********************************************************************
			// Dibuixar tots els gràfics del joc
			// ***********************************************************************
			dibuixarElements();
			// ***********************************************************************
			//Pintem Marcadors
			pintarMarcadors();

			// Actualitza la pantalla
			jocLib.VideoUpdate();
		
			// ***********************************************************************
			// Sortirem del primer bucle si pressionem ESC o ens quedem sense vides
			// ***********************************************************************
		}while( (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (vides>0) /*&& modPause >= 0*/); 
		// ********************************************************************************
		// PER AFEGIR: Sortirem del bucle també si s'ha destruit tot el mur. En aquest cas
		// incrementarem de nivell
		// *********************************************************************************

		// *********************************************************************************
		// Sortirem del segon bucle quan haguem superat tots els nivells, pressionem ESC
		// o ens quedem sense vides
		// *********************************************************************************
	}while((getNivell()<4) && (vides>0) && (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)));
	
	system("PAUSE");

	return punts;
}