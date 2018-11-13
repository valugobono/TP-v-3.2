#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED
#define ARCHIUSU "usuarios.dat"
#define ARCHIPELI "peliculas.bin"
#define ARCHIPELISUSU "pelisxusu.dat"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#include <conio.h>
#include <windows.h>


// ***** ESTRUCTURAS BASICAS *****

typedef struct stUsuario
{
    int admin;
    int idUsuario;
    char nombreUsuario[15];
    char genero;
    char pais[20];
    int pass[2][5];
    int anioNacimiento;
    int eliminado;
} stUsuario;

typedef struct stPelicula
{
    int idPelicula;
    char nombrePelicula[30];
    char director[20];
    char genero[20];
    char pais[20];
    int anio;
    int valoracion;
    int pm;
    int eliminado;
} stPelicula;

typedef struct nodoListaPelicula
{
    stPelicula p;
    struct nodoListaPelicula * sig;
} nodoListaPelicula;

typedef struct stCelda
{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
} stCelda;

typedef struct nodoArbolPelicula
{
    stPelicula p;
    struct nodoArbolPelicula * izq;
    struct nodoArbolPelicula * der;
} nodoArbolPelicula;

typedef struct stPelisVistas
{
    int idPeliVista;
    int idUsuario;
    int idPelicula;
} stPelisVistas;

///*************************************************************************************************************************************

// FUNCIONES DE VALIDACION
int validarLongPass(char pass[]); // Chequea si la contrasenia supera los 10 caracteres
int validarUserExiste(char nombreUsuario[]); // Chequea si el nombre de usuario ya existe al momento del alta
int validarTipoAlfanumerico(char cadena[]); // Devuelve 1 si el parámetro pasado es cadena ALFANUMERICA, 0 si no lo es
int validarTipoChar(char cadena[]);  // Devuelve 1 si el parámetro pasado es cadena de caracteres, 0 si no lo es
int validacionPass(stCelda*arregloUsuActivos, int validos, char nombre[], char pass[]); // //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada - Retorna true or false
int validacionPassAdmin(char pass[]);//No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario - Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada - Retorna true or false
int validarPeliExiste(char nombrePeli[]);
int validarUsuExisteArrayId(int id, stCelda*arregloUsuActivos, int validos);
int validarUsuActivo(int id, stCelda*arregloUsuActivos, int validos);

int validarIdUsuAndPeli(int idUsr, int idPeli);
//int validarIDPeli(int idPeli);//Funcion utilizada en pelis x usuario
//int validarIDusu(int idUsr); //Funcion utilizada en pelis x usuario


// FUNCION DE CARGA INICIAL
int cargaInicial(nodoArbolPelicula * ArbolPelis, stCelda*arregloUsuActivos, int *validos);
void menuPrincipal();


// FUNCIONES QUE TRABAJAN SOBRE PELICULAS
nodoArbolPelicula*altaPelicula(nodoArbolPelicula*ArbolPelis);
nodoArbolPelicula*bajaPelicula(nodoArbolPelicula*ArbolPelis);
nodoArbolPelicula*mostrarPeliParaModif(nodoArbolPelicula*ArbolPelis);
void consultaPeliAdmin();
void insertar(stPelicula arregloPelis[], int posicion);
void cargarArregloPeliculas(stPelicula arregloPelis[], int validosPelis);
int cargarArregloPeliculasActivas(stPelicula arregloPelis[], int validosPelis);
void ordenarGenero();
void ordenarTitulo();
void ordenacionSeleccion(stPelicula arregloPelis[], int validosPelis);
int posicionMenor(stPelicula arregloPelis[], int pos, int validosPelis);
int validarPeliExiste(char nombrePelicula[]);
void mostrarArregloPelis(stPelicula arregloPelis[], int validos);

// FUNCIONES DE SUBMENUES // Menu principal en main
void menuUsuario(stCelda * arregloUsuActivos, int validos, stUsuario usr, nodoArbolPelicula * ArbolPelis);
nodoArbolPelicula * menuAdmin();
nodoArbolPelicula* menuAdminPelis();
stCelda * menuAdminUsuarios(stCelda*arregloUsuActivos, int * validos);
void subMenuListados(nodoArbolPelicula*ArbolPelis);
void loginUser(stCelda*arregloUsuActivos, int validos, nodoArbolPelicula * ArbolPelis);
nodoArbolPelicula * loguinadm(stCelda**arregloUsuActivos, int * validos, nodoArbolPelicula*ArbolPelis);
void menumodif(stCelda*arregloUsuActivos, int validos); // Menu de modificación de usuarios
int menuModifPelis(nodoArbolPelicula*ArbolPelis); //Menu para administrador para seleccion de campo a modificar
void subMenuMostrarArbol(nodoArbolPelicula * ArbolPelis);


// FUNCIONES AUXILIARES //

void PelisxUsuarioArchivoToADL(stCelda*arregloUsu, int posicion, nodoArbolPelicula * ArbolPelis);//Carga de Peliculas vistas por usuario a arreglo de listas
void actualizarPelisVistas(stCelda*arregloUsuActivos, int validos);//Carga de peliculas vistas a archivo
void mostrarPeliculas(); // Muestra los datos ingresados para ir verificando el funcionamiento del programa
void mostrarPass(int f, int c,int M[f][c]); //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)
void mostrarArregloPelis(stPelicula arregloPelis[], int validosPelis); // Usada para ver por pantalla y verificar el funcionamiento de funciones
int PelisVistasTotales(stCelda*arregloUsuActivos, int validos);
int cantRegistrosTotales();

// ***** FUNCIONES DE LISTAS ******

nodoListaPelicula* inicLista();
nodoListaPelicula* crearNodoPeli(stPelicula Peli);
nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis);
nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
void imprimirNodoPelis(stPelicula nodoPeli);
void mostrarListaPelis(nodoListaPelicula * lista, char nombreUsuario[]);
nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id);

// ***** FUNCIONES DE ARBOLES ******
nodoArbolPelicula * inicArbol();
nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula);
nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol,stPelicula Pelicula);
void preOrder(nodoArbolPelicula*Arbol);
void inOrder(nodoArbolPelicula*Arbol);
void postOrder(nodoArbolPelicula*Arbol);
stPelicula buscarPeliculaID(nodoArbolPelicula*Arbol,int id);
nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P);
nodoArbolPelicula*balanceoArbol(stPelicula arregloDePelis[], int primero, int ultimo);

// ***** FUNCIONES TP2 PELICULAS ******
void verPelicula(char nombreUsuario[], stCelda*arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis);
void cargarPeliAUser(stCelda*arregloUsuActivos,int validos, char nombreUsuario[],nodoListaPelicula* Peli);
int validarPeliExiste(char nombrePeli[]);
int buscarPelixNombre(nodoArbolPelicula* ArbolPelis, char PeliBuscada[]);
nodoArbolPelicula* modificarPeliEnArbol(nodoArbolPelicula * ArbolPelis,stPelicula auxPeli);

int CantidadPelisActivas();
nodoArbolPelicula*PasaPeliculasDeArchivoToArbol(nodoArbolPelicula*ArbolPelis);


// ***** FUNCIONES DE TP2 USUARIOS *****
stCelda* borrarArregloUsu(stCelda*arregloUsuActivos, int *validos);
int cantUsuariosActivos(); // Cuenta la cantidad inicial de usuarios activos en el archivo
int cantUsuariosInactivos(); // Cuenta la cantidad inicial de usuarios inactivos en el archivo
int cantUsuariosTotales(); // Cuenta la cantidad inicial de usuarios totales en el archivo
stCelda * cargarArchiUsuToArreglo(stCelda*arregloUsuActivos, int *validos, nodoArbolPelicula * ArbolPelis); // Pasa los registros activos del archivo al arreglo
stCelda* altaUsuarios(stCelda*arregloUsuActivos, int *validos); // Sesión de alta de usuarios: se ingresan los datos al arreglo y se persisten en el archivo
void bajaUsuario(stCelda*arregloUsuActivos, int validos); // Modifica el campo "Eliminado" del usuario buscado en el arreglo y se persiste en el archivo
void imprimirUsuarioConPass(stUsuario); // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por parámetro - CON PASSWORD P/USUARIO
void imprimirUsuarioSinPass(stUsuario); // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por parámetro - SIN PASSWORD P/ADMIN
void mostrarUsuariosActivos(stCelda*arregloUsuActivos, int validos); // Muestra lista de usuarios activos con sus respectivas películas
int buscarPosicionUsuario(char nombreUsuario[], stCelda*arregloUsuActivos, int validos); // Retorna la posicion en el arreglo del usuario buscando por nombre de usuario
int buscarPosUsuarioPorId(int id, stCelda*arregloUsuActivos, int validos); // Retorna la posicion en el arreglo del usuario buscando por el ID del usuario
void consultarUsuario(stCelda*arregloUsuActivos, int validos); // Muestra por pantalla los datos del usuario consultado por ID o por nombre
int modificarUsuario(stCelda*arregloUsuActivos, int validos); // Solicita el id del usuario y verifica si existe. De existir, continua con el menu "menumodif"
int cambiarNombreUsu(int id, int pos, stCelda*arregloUsuActivos); // Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPassUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarAnioUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarGeneroUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPaisUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarEstadoUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPermisosUsu(int id, int pos, stCelda*arregloUsuActivos);// Función invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int validarUsuExisteNombre(char nombre[], stCelda*arregloUsuActivos, int validos); // Función que valida si el usuario existe en el arreglo recibiendo como parámetro el nombre de usuario
void encriptacionPass(char pass[], int mEncriptada[2][5]); //Funcion para encriptacion de password
void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]); //Funcion para Multiplicacion de Matrices
void desencriptacionPass(int mEncriptada[2][5], char pass[]);//Desencripta el pass para mostrarlo

void recomendarPelis(nodoArbolPelicula*ArbolPelis, nodoListaPelicula*PelisVistas, char nombre[]);
void generoMasVisto(nodoListaPelicula*lista, char *);
int buscarMayorOcurrencia(int ocurrencias[], int validos);
int agregarString(char arregloNombres[][20], char nombre[], int validos);
int buscarPosString(char arregloNombres[][20], char nombre[], int validos);
void listarPelisRecomendadasxGeneroDirector(nodoListaPelicula *PelisVistas,nodoArbolPelicula *ArbolPelis, char *,char *);
int peliVista(int idPelicula,nodoListaPelicula *PelisVistas);
nodoListaPelicula * borrarPeliVistaXid(nodoListaPelicula*PelisVistas, int idUsu, int idPeli);
nodoListaPelicula*borrarUnaPeliVistaLista(nodoListaPelicula*PelisVistas, int idPeli);
void borrarPeliVistaArchivo(int idUsr, int idPeli);

nodoListaPelicula* borrarPelisVistas(nodoListaPelicula*lista);
nodoArbolPelicula*borrarNodoArbol(nodoArbolPelicula*ArbolPelis, int idPeli);
nodoArbolPelicula*nodoMasIzq(nodoArbolPelicula*ArbolPelis);
nodoArbolPelicula*nodoMasDer(nodoArbolPelicula*ArbolPelis);
nodoArbolPelicula*borrarArbol(nodoArbolPelicula*ArbolPelis);



#endif // LIBRERIA_H_INCLUDED
