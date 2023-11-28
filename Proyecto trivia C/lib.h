#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

typedef struct Composicionpregunta{
    char pregunta[150];
    char respuesta1[150];
    char respuesta2[150];
    char respuesta3[150];
    char respuesta4[150];
    int respuestaCorrecta;
}TComposicionpregunta;

typedef struct DatosJugador{
    char Nombre[50];
    int credi;
}TDatosJugador;

typedef struct Player{
    TDatosJugador datos;
    struct Player * sig;
}TPlayer;

typedef struct pregunta{
    TComposicionpregunta dato;
    struct pregunta * sig;
}TPregunta;

TPregunta * generanodo(TComposicionpregunta a);
int esVaciaCab(TPregunta *CabezaPreguntas);
TComposicionpregunta generaDatoPreguntas(TComposicionpregunta dato);
void InsertarNodoPregunta(TComposicionpregunta dato_pregunta, TPregunta **LP);
void IngresarPreguntas(TPregunta **LP);
void PrintPreguntas(TPregunta *L);
int Credibilidad(int *cred);
void MuestraDePregunta(TPregunta *CabezaPreguntas, int *cred);
TDatosJugador IngresaDatos(int cred);
TPlayer *generanodoPlayer(TDatosJugador sus);
int esVaciaPlayer(TPlayer *LP);
void InsertarDatosJugador(TPlayer **LP, TDatosJugador data);
void PrintPlayer(TDatosJugador a);
void MuestraDatosPlayer(TPlayer *LP);
void EliminarLista(TPregunta **LP);
int Longitud(TPregunta *LP);
void RebuscarListaYEliminar(TPregunta **LP, TPregunta **LPJugable, int id);
void GenerarListaDePreguntas(TPregunta **LP, TPregunta **LPJugable);


#endif // LIB_H_INCLUDED
