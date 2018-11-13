#ifndef PELICULAS_H_INCLUDED
#define PELICULAS_H_INCLUDED

char archiPeli[20]="peliculas.bin";


// ***** ESTRUCTURAS BASICAS *****


typedef struct stPelicula
{
    int idPelicula;
    char nombrePelicula[60];
    char director[30];
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

typedef struct nodoArbolPelicula
{
    stPelicula p;
    struct nodoArbolPelicula * izq;
    struct nodoArbolPelicula * der;
} nodoArbolPelicula;

// FUNCIONES QUE TRABAJAN SOBRE PELICULAS
void altaPelicula(char archiPeli[]);
void bajaPelicula(char archiPeli[]);
void mostrarPeliParaModif(char archiPeli[]);
void consultaPeliAdmin(char archiPeli[]);
void insertar(stPelicula array[], int i);
int cargarArrayPeliculas(char archiPeli[], stPelicula array[]);
void ordenarGenero (char archiPeli[]);
void ordenarTitulo(char archiPeli[]);
void ordenacionSeleccion(stPelicula array[], int validos);
int posicionMenor(stPelicula array[], int pos, int validos);
// ***** FUNCIONES TP2 ******
stPelicula verPelicula();
int buscarPelixNombre(char PeliBuscada[]);

// FUNCIONES AUXILIARES //
void mostrarArrayPeliculas(stPelicula array[], int validos); // Usada para ver por pantalla y verificar el funcionamiento de funciones
void mostrarPeliculas(char archiPeli[]); // Muestra los datos ingresados para ir verificando el funcionamiento del programa

// ***** FUNCIONES DE LISTAS ******
nodoListaPelicula* inicLista();
nodoListaPelicula* crearNodoPeli(stPelicula Peli);
nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis);
nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
void imprimirNodoPelis(nodoListaPelicula* nodoPeli);
void mostrarNodoPelis(nodoListaPelicula* listaPelis);
nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id);


// ***** FUNCIONES DE ARBOLES ******
nodoArbolPelicula * inicArbol();
nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula);
nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol,stPelicula Pelicula);
void preOrder(nodoArbolPelicula*Arbol);
void inOrder(nodoArbolPelicula*Arbol);
void postOrder(nodoArbolPelicula*Arbol);
nodoArbolPelicula*buscarPeliculaID(nodoArbolPelicula*Arbol,stPelicula Pelicula);
nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P);

// ***** FUNCIONES TP2 ******

#endif // PELICULAS_H_INCLUDED
