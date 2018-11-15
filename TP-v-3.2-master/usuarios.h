#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

char archiUsu[20]="usuarios.dat";


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


typedef struct stCelda
{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
} stCelda;


// FUNCIONES QUE TRABAJAN SOBRE USUARIOS
void altaUsuario(char archiUsu[], stCelda arregloUsuActivos[]); // Da de alta a nuevos usuarios, invocando a las funciones pedidoDatosUsuario, validarUserExiste, AsignarId
void bajaUsuario(char archiUsu[]); // Modifica el campo "eliminado" con un 1 para indicar verdadero
void mostrarUserParaModif(char archiUsu[]);//Modificacion de usuario para administrador
void mostrarUser(char archiUsu[], char nombreUsuario[]);//Se Muestra info almacenada al Usuario
void encriptacionPass(char pass[], int mEncriptada[2][5]); //Funcion para encriptacion de password
void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]); //Funcion para Multiplicacion de Matrices
void desencriptacionPass(int mEncriptada[2][5], char pass[]);//Desencripta el pass para mostrarlo
void mostrarArrayUsuarios(stUsuario array[], int validos);//Muestra los datos de usuarios por pantalla
int cargarArrayUsuarios(char archiUsu[], stUsuario array[]);//Se pasan los datos de usuarios a un arreglo y devuelve la cantidad de registros almacenados(validos)
void listadoUsuarios(char archiUsu[]);  //Se Muestra Listado de Usuarios al Admin
void cargarIdPeliAUser(int id, char nombreUsuario[], char archiUsu[]);
void consultaUsuarioAdmin(char archiUsu[]);//Se Muestra info por ID al Admin
void consultaUsuario(char archiUsu[], char nombreUsuario[]);//Se Muestra info por Nombre al Usuario

// FUNCIONES DE VALIDACION
int validarLongPass(char pass[]); // Chequea si la contrasenia supera los 10 caracteres
int validarUserExiste(char archiUsu[], char nombreUsuario[]); // Chequea si el nombre de usuario ya existe al momento del alta
//int validarTipoAlfanumerico(char cadena[]); // Devuelve 1 si el parámetro pasado es cadena ALFANUMERICA, 0 si no lo es
//int validarTipoChar(char cadena[]);  // Devuelve 1 si el parámetro pasado es cadena de caracteres, 0 si no lo es
int validacionPass(stCelda arregloUsuActivos[], char nombre[], char pass[]); // //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada - Retorna true or false
int validacionPassAdmin(char pass[]);//No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario - Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada - Retorna true or false
int validarPeliExiste(char archiPeli[], char nombrePelicula[]);

// FUNCIONES AUXILIARES //
void mostrarUsuarios(char archiUsu[]); // Muestra los datos ingresados para ir verificando el funcionamiento del programa
void mostrarPass(int f,int c,int M[f][c]); //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)

// ***** FUNCIONES DE TP2: USUARIOS *****
int cantUsuariosActivos(char archiUsu[]);
int cantUsuariosInctivos(char archiUsu[]);
int cantUsuariosTotales(char archiUsu[]);
int cargarArchivoUsuariosActivosToArreglo(char archiUsu[], stCelda*);
stCelda* cargarArchivoUsuariosInactivosToArreglo(char archiUsu[]);
int calcularTamanioArrayUsuarios(stCelda arreglo[]);


#endif // USUARIOS_H_INCLUDED
