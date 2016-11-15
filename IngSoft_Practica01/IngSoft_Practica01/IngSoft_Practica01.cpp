// IngSoft_Practica01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void main()
{
	//Constantes
	const int moverIzq   = 'k';
	const int moverDer   = 'l';
	const int disparaIzq = 'i';
	const int disparaDer = 'o';
	const unsigned int anchoMundo = 80;

	//Variables
	int posPlayer = anchoMundo/2;
	int posBala = -1;  //Para que no se dibuje la bala nada mas empezar. 
	int teclaPulsada = 0;   //Aqui guardamos la tecla que ha pulsado el jugador.

	printf("\n\n\n\n\n\n\n\n\n\n"); //Ponemos el suelo más abajo
	while (true)
	{
		if (_kbhit())   //Cuando se pulse una tecla, entrará en este IF.
		{
			teclaPulsada = _getch();   //La función _getch() devuelve la tecla pulsada.
			if (teclaPulsada != 0)  
			{
				if (teclaPulsada == moverIzq && posPlayer > 0)
					posPlayer = posPlayer - 1;
				if (teclaPulsada == moverDer && posPlayer < anchoMundo - 1)
					posPlayer = posPlayer + 1;
				if (teclaPulsada == disparaIzq && (posBala < 0 || posBala > 79))   //Si pulsa la tecla de disparo y no hay ninguna bala en el mapa
					posBala = posPlayer - 1;
				if (teclaPulsada == disparaDer && (posBala < 0 || posBala > 79))   //Si pulsa la tecla de disparo y no hay ninguna bala en el mapa
					posBala = posPlayer + 1;
			}
		}
		printf("\r");   //Para que vuelva al principio de la linea y repinte encima de lo que ya había.
		for (int i = 0; i < anchoMundo; i++)  //Pinta el mundo
		{
			if (i == posPlayer)
				printf("W");
			else if (i == posBala)
				printf("*");
			else
				printf("-");
		}
		
		if (posBala < posPlayer) //Si la bala está a la izquierda del personaje, significa que ha disparado hacia la izquierda.
			posBala = posBala - 1;  //La bala se mueve hacia la izquierda.
		else
			posBala = posBala + 1;  //La bala se mueve hacia la derecha.

		Sleep(50);  //Para que el juego vaya a 20 FPS
	}
}