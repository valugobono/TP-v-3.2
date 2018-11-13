#ifndef PELISXUSER_H_INCLUDED
#define PELISXUSER_H_INCLUDED

char archiPeli[20]="peliculas.bin";


// ***** ESTRUCTURAS BASICAS *****

typedef struct stPelisVistas
{
    int idPeliVista;
    int idUsuario;
    int idPelicula;
} stPelisVistas;


// FUNCIONES AUXILIARES //
void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion);//Carga de Peliculas vistas por usuario a arreglo de listas
void actualizarPelisVistas(stCelda arregloUsuActivos[], int validosUsuActivos, stCelda arregloUsuInactivos[], int validosUsuInactivos);//Carga de peliculas vistas a archivo

#endif // PELISXUSER_H_INCLUDED
