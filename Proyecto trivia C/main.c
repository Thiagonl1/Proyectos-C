#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "lib.h"


int main()
{
    srand(time(NULL));
    TPregunta *LPreg=NULL;
    TPlayer *LPlayer=NULL;
    TPregunta *LJugable=NULL;

   int opcion;
    do{
        int credibilidad=5;
        printf("\n\tBIENVENIDO AL SUSJUEGO\n\t  Que queres hacer?\n1)Empezar a jugar\n2)Ver la lista de las mejores puntuaciones\n3)Salir del juego\n");
        fflush(stdin);scanf("%d", &opcion);
        switch(opcion){

            case 1:{
                system("cls");
                IngresarPreguntas(&LPreg);
                GenerarListaDePreguntas(&LPreg, &LJugable);
                MuestraDePregunta(LJugable,&credibilidad);
                if(!esVaciaCab(LPreg))
                    InsertarDatosJugador(&LPlayer, IngresaDatos(credibilidad));
                EliminarLista(&LJugable);
                EliminarLista(&LPreg);
                break;

            }
            case 2:{
                system("cls");
                if(esVaciaPlayer(LPlayer)){
                    printf("\nNo se pudieron encontrar datos\n");
                }else{
                    system("cls");
                    MuestraDatosPlayer(LPlayer);
                }
                break;
            }
            case 3:{
                EliminarLista(&LJugable);
                EliminarLista(&LPreg);

                break;
            }
            default:{
                system("cls");
                break;
            }
        }

    }while(opcion!=3);
    return 0;
}
