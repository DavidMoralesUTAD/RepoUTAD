
#include "stdafx.h"

void main()
{
	//Constantes
	const int MOVER_IZQ = 'k';
	const int MOVER_DER = 'l';
	const int DISPARA_IZQ = 'i';
	const int DISPARA_DER = 'o';
	const unsigned int ANCHO_MUNDO = 80;

	//Variables
	int posPlayer = ANCHO_MUNDO / 2;
	int posMonster = -1;
	int posBala = -1;  //Para que no se dibuje la bala nada mas empezar. 
	int teclaPulsada = 0;  //Aqui guardamos la tecla que ha pulsado el jugador.
	bool gameOver = false;  //Comprueba si el personaje está vivo o muerto.

	printf("\n\n\n\n\n\n\n\n\n\n");  //Ponemos el suelo más abajo
	while (true)
	{
		if (_kbhit() && !gameOver)  //Cuando se pulse una tecla, y no estés muerto, entrará en este IF.
		{
			teclaPulsada = _getch();  //La función _getch() devuelve la tecla pulsada.
			if (teclaPulsada != 0)
			{
				if (teclaPulsada == MOVER_IZQ && posPlayer > 0)
					posPlayer = posPlayer - 1;
				if (teclaPulsada == MOVER_DER && posPlayer < ANCHO_MUNDO - 1)
					posPlayer = posPlayer + 1;
				if (teclaPulsada == DISPARA_IZQ && (posBala < 0 || posBala > ANCHO_MUNDO - 1))  //Si pulsa la tecla de disparo y no hay ninguna bala en el mapa
					posBala = posPlayer - 1;
				if (teclaPulsada == DISPARA_DER && (posBala < 0 || posBala > ANCHO_MUNDO - 1))  //Si pulsa la tecla de disparo y no hay ninguna bala en el mapa
					posBala = posPlayer + 1;
			}
		}

		//Calcular donde aparece el monstruo
		if ((posMonster < 0 || posMonster > ANCHO_MUNDO - 1) && !gameOver)  //Si el monstruo no está generado en el mapa y no se ha muerto el player
		{
			posMonster = rand() % 2;  //Aleatoriamente se le asigna 1 de los 2 valores: 0 o 1 (principio o final)
			if (posMonster == 1)
				posMonster = ANCHO_MUNDO - 1;  //Si es 0, se deja en 0 (principio) si es 1, se le asigna el ancho del mundo - 1 (final)
		}

		printf("\r");  //Para que vuelva al principio de la linea y repinte encima de lo que ya había.
		for (int i = 0; i < ANCHO_MUNDO; i++)  //Pinta el mundo
		{
			if (i == posPlayer)
				printf("W");
			else if (i == posBala)
				printf("*");
			else if (i == posMonster)
				printf("X");
			else
				printf("-");
		}

		//Movimiento de la bala
		if (posBala < posPlayer)  //Si la bala está a la izquierda del personaje, significa que ha disparado hacia la izquierda.
			posBala = posBala - 1;  
		else
			posBala = posBala + 1;  

		//Movimiento del monstruo
		if (posMonster > posPlayer)  //Si el monstruo está a la derecha del player, se mueve a la izquierda.
			posMonster = posMonster - 1;
		else if(posMonster < posPlayer && posMonster != -1)  //Si el monstruo está a la izquierda del player, y ya se ha generado, se mueve a la derecha
			posMonster = posMonster + 1;

		//Comprobar colisiones
		if (posMonster == posBala || posMonster + 1 == posBala || posMonster - 1 == posBala)  //Si el monstruo choca contra la bala, desaparecen la bala y el monstruo.
		{
			posMonster = -1;
			posBala = -1;
		}
		if (posMonster == posPlayer || posMonster == posPlayer)  //Si el monstruo choca contra el personaje, desaparece el personaje.
		{
			posPlayer = -1;
			gameOver = true;
		}

		Sleep(50);  //Para que el juego vaya a 20 FPS
	}
}