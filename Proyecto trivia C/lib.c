#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "lib.h"


TPregunta * generanodo(TComposicionpregunta a){
    TPregunta * nuevo = malloc(sizeof(TPregunta));
    nuevo->dato=a;
    nuevo->sig=NULL;
    return nuevo;
}


int esVaciaCab(TPregunta *CabezaPreguntas){
    return CabezaPreguntas==NULL;
}


TComposicionpregunta generaDatoPreguntas(TComposicionpregunta dato){
    TComposicionpregunta a;
    a=dato;
    return a;
}

void InsertarNodoPregunta(TComposicionpregunta dato_pregunta, TPregunta **LP){
    TPregunta * nuevo = generanodo(dato_pregunta);
    if(esVaciaCab(*LP)){
        *LP=nuevo;
    }else{
        TPregunta * pact = *LP;
        while(pact->sig!=NULL){
            pact=pact->sig;
        }
        pact->sig=nuevo;
    }
}

void IngresarPreguntas(TPregunta **LP){
    TComposicionpregunta a;
    FILE *archivoPreguntas = fopen("sus.txt", "r");
    if(archivoPreguntas==NULL){
        printf("\nNo tenemos base de datos..\n");
    }else{
        while(feof(archivoPreguntas)==0){
            fgets(a.pregunta, sizeof(a.pregunta),archivoPreguntas);
            fgets(a.respuesta1, sizeof(a.respuesta1),archivoPreguntas);
            fgets(a.respuesta2, sizeof(a.respuesta2),archivoPreguntas);
            fgets(a.respuesta3, sizeof(a.respuesta3),archivoPreguntas);
            fgets(a.respuesta4, sizeof(a.respuesta4),archivoPreguntas);
            fscanf(archivoPreguntas, "%d\n", &a.respuestaCorrecta);
            InsertarNodoPregunta(a, &(*LP));
        }
    }
    fclose(archivoPreguntas);
}



void PrintPreguntas(TPregunta *L){
    printf("\n\t%s\n%s\n%s\n%s\n%s\n", L->dato.pregunta, L->dato.respuesta1, L->dato.respuesta2, L->dato.respuesta3, L->dato.respuesta4);
}

int Credibilidad(int *cred){
    *cred-=1;
    return *cred;
}


void MuestraDePregunta(TPregunta *CabezaPreguntas, int *cred){          //ESTO ESTA MAL, TENES QUE HACERLO CON RECURSIVIDAD ASI NO GASTAS MUCHO CODIGO
    if (!esVaciaCab(CabezaPreguntas)){                                   // Y SI QUERES HACERLO RECURSIVO VAS A TENER QUE SACAR EL ESVACIA Y CAMBIAR UN PAR DE COSAS
        int respuesta_usuario;
        PrintPreguntas(CabezaPreguntas);
        do{
            printf("\nCual es tu respuesta?\n");
            fflush(stdin);scanf("%d", &respuesta_usuario);
        }while(respuesta_usuario>4&&respuesta_usuario<1);

        if(respuesta_usuario==CabezaPreguntas->dato.respuestaCorrecta){
            printf("\n[Interesante..]\n");
        }else{
            Credibilidad(&(*cred));
            printf("\n[Ya veo...]\n");
        }
        system("cls");
        MuestraDePregunta(CabezaPreguntas->sig, cred);
    }
}

TDatosJugador IngresaDatos(int cred){
    TDatosJugador data;
    printf("\nNombre\n");
    fflush(stdin);gets(data.Nombre);
    data.credi=cred;
    return data;
}

TPlayer *generanodoPlayer(TDatosJugador sus){
    TPlayer * nuevo=malloc(sizeof(TPlayer));
    nuevo->datos = sus;
    nuevo->sig=NULL;
    return nuevo;
}

int esVaciaPlayer(TPlayer *LP){
    return LP==NULL;
}

void InsertarDatosJugador(TPlayer **LP, TDatosJugador data){
    TPlayer * nuevo = generanodoPlayer(data);
    if(esVaciaPlayer(*LP)){
        *LP=nuevo;
    }else{
        TPlayer * pact= *LP;
        if(nuevo->datos.credi > pact->datos.credi){
            nuevo->sig = pact;
            *LP=nuevo;
        }else{
            while(pact->sig!=NULL && pact->sig->datos.credi > nuevo->datos.credi){
                pact=pact->sig;
            }
            if(pact->sig!=NULL){
                nuevo->sig=pact->sig;
            }
            pact->sig=nuevo;
        }
    }

}

void PrintPlayer(TDatosJugador a){
    printf("\nUsuario: %s\nCredibilidad total: %d\n", a.Nombre, a.credi);
}

void MuestraDatosPlayer(TPlayer *LP){
    if(!esVaciaPlayer(LP)){
        PrintPlayer(LP->datos);
        MuestraDatosPlayer(LP->sig);
    }
}

void EliminarLista(TPregunta **LP){
    if(!esVaciaCab(*LP)){
        TPregunta * target=*LP;
        *LP=target->sig;
        free(target);
        EliminarLista(*(&LP));
    }
}

int Longitud(TPregunta *LP){
    int longitud=1;
    TPregunta *pact=LP;
    while(pact!=NULL){
        pact=pact->sig;
        longitud++;
    }
    return longitud;
}

void RebuscarListaYEliminar(TPregunta **LP, TPregunta **LPJugable, int id){
    if(!esVaciaCab(*LP)){
       int contador=1;
       TPregunta * pact= *LP;
       while(contador!=id){
            pact=pact->sig;
            contador++;
       }
       if(pact==*LP){
            InsertarNodoPregunta(pact->dato, *(&LPJugable));
            *LP=pact->sig;
            free(pact);
       }else{
           InsertarNodoPregunta(pact->dato, *(&LPJugable));
           TPregunta * notarget = *LP;
           while(notarget->sig!=pact){
                notarget=notarget->sig;
           }
           notarget->sig=pact->sig;
           free(pact);
       }
    }
}

void GenerarListaDePreguntas(TPregunta **LP, TPregunta **LPJugable){
    int max,pregrandom;
    //Verificar la cantidad de espacios de la lista

    //Elegir una pregunta random
    for(int i=0;i<5;i++){
        max=Longitud(*LP);

        pregrandom=1+rand()%(max+1-1);
        //Buscar la pregunta en una lista, y pasarla a la otra
        RebuscarListaYEliminar(*(&LP), *(&LPJugable), pregrandom);
    }
}
