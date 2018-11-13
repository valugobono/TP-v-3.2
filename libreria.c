#include "libreria.h"



stCelda*arregloUsuActivos;
stCelda*arregloUsuInactivos;


// FUNCIONES VALE TP 2*******************************************************************************************************************************************************************


void cargaInicial()//le agregagria retornor para verificar carga correcta
{

int cantActivosIniciales=0; //Ver con profe donde va
    cantActivosIniciales=cargarArchivoUsuariosActivosToArreglo(archiUsu,arregloUsuActivos);
    cargarArchivoUsuariosInactivosToArreglo(archiUsu, arregloUsuInactivos);




}

int cantUsuariosActivos(char archiUsu[])
{

    int cantUsuarios=0;
    stCelda aux;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {
        while(fread(&aux,sizeof(stCelda),1,archi)>0)
        {
            if(aux.usr.eliminado==0)
            {
                cantUsuarios++;
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cantUsuariosInactivos(char archiUsu[])
{

    int cantUsuarios=0;
    stCelda aux;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {
        while(fread(&aux,sizeof(stCelda),1,archi)>0)
        {
            if(aux.usr.eliminado==1)
            {
                cantUsuarios++;
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cantUsuariosTotales(char archiUsu[])
{

    int cantUsuarios=0;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {

        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo

        if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
        {
            cantUsuarios=0; // Se le asigna el valor 1 al primer registro
        }
        else
        {
            cantUsuarios=(ftell(archi)/sizeof(stUsuario)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura

        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cargarArchivoUsuariosActivosToArreglo(char archiUsu[], stCelda*arregloUsuActivos)
{
    int i=0;
    int dim=cantUsuariosActivos(archiUsu);
    stUsuario aux;

//    stCelda*arregloUsuActivos=NULL; // Inicializo a Null para dejarlo en limpio -- PASADA al main

    arregloUsuActivos=(stCelda*)malloc(sizeof(stCelda)*dim);

    if(arregloUsuActivos==NULL)
    {
        puts("No se puede continuar por error de asignacion de memoria");
        exit(-1);
    }

    else
    {
        FILE*archi;

        archi=fopen(archiUsu, "rb");

        if(archi)
        {

            while(fread(&aux, sizeof(stUsuario), 1, archi)>0)
            {
                if(aux.eliminado==0)
                {
                    arregloUsuActivos[i].usr=aux;
                    arregloUsuActivos[i].listaPelis=inicLista();
                    i++;
                }
            }
            fclose(archi);
        }
        else
        {
            printf("No se pudo abrir el archivo de usuarios");
        }
    }
    return i; //Retorna usuarios activos pasados al arreglo en primera instancia
}


stCelda* cargarArchivoUsuariosInactivosToArreglo(char archiUsu[])
{

    int i=0;
    int dim=cantUsuariosInactivos(archiUsu);
    stCelda aux;

//    stCelda*arregloUsuInactivos=NULL; // Inicializo a Null para dejarlo en limpio -- Pasada al main

    stCelda * arregloUsuInactivos= malloc(sizeof(stCelda)*dim);

    if(arregloUsuInactivos==NULL)
    {
        puts("No se puede continuar por error de asignacion de memoria");
        exit(-1);
    }

    else
    {

        FILE*archi;

        archi=fopen(archiUsu, "rb");

        if(archi)
        {

            while(!feof(archi) && i<dim)
            {
                fread(&aux, sizeof(stCelda), 1, archi);
                if(!feof(archi))
                {
                    fread(&aux, sizeof(stCelda), 1, archi);
                    if(aux.usr.eliminado==1)
                    {
                        arregloUsuInactivos[i]=aux;
                        arregloUsuInactivos[i].listaPelis=inicLista();
                    }
                }
                i++;
            }
            fclose(archi);
        }

        else
        {
            printf("No se pudo abrir el archivo de usuarios");
        }
    }
    return arregloUsuInactivos;
}


//int calcularTamanioArrayUsuarios(stCelda arreglo[])
//{
//
//    int tamanio=sizeof(arreglo)/sizeof(stCelda);
//
//    return tamanio;
//}


// ***** TDA LISTAS ******

nodoListaPelicula* inicLista()
{
    return NULL;
}


nodoListaPelicula* crearNodoPeli(stPelicula Peli)
{

    nodoListaPelicula* aux=(nodoListaPelicula*)malloc(sizeof(nodoListaPelicula));
    aux->p=Peli;

    return aux;
}


nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        nuevoNodo->sig=listaPelis;
        listaPelis=nuevoNodo;
    }

    return listaPelis;

}


nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }

    return seg;

}


nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        nodoListaPelicula*ultimo=buscarUltimoNodo(listaPelis);
        ultimo->sig=nuevoNodo;
    }

    return listaPelis;
}


nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        if(strcmp(listaPelis->p.nombrePelicula, nuevoNodo->p.nombrePelicula)<0)
            listaPelis=agregarNodoPpio(listaPelis, nuevoNodo);

        else
        {
            nodoListaPelicula*ante=listaPelis;
            nodoListaPelicula*seg=listaPelis->sig;
            while(!seg && strcmp(seg->p.nombrePelicula, nuevoNodo->p.nombrePelicula)>=0)
            {
                ante=seg;
                seg=seg->sig;
            }
            nuevoNodo->sig=seg;
            ante->sig=nuevoNodo;
        }
    }

    return listaPelis;

}


void imprimirNodoPelis(nodoListaPelicula* nodoPeli)
{

    system("cls");
    puts("\n\n\t***** PELICULA/S *****\n");
    printf("\n\tNOMBRE: %s", nodoPeli->p.nombrePelicula);
    printf("\n\tDIRECTOR: %s", nodoPeli->p.director);
    printf("\n\tGENERO: %s", nodoPeli->p.genero);
    printf("\n\tPAIS: %s", nodoPeli->p.pais);
    printf("\n\tANIO: %i", nodoPeli->p.anio);
    printf("\n\tVALORACION: %i", nodoPeli->p.valoracion);
    printf("\n\tPM: %i", nodoPeli->p.pm);

}


void mostrarNodoPelis(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg)
        if(seg->p.eliminado==0) // MUESTRA SOLO PELIS ACTIVAS
        {
            imprimirNodoPelis(seg);
            seg=seg->sig;
        }
}


nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id)
{

    nodoListaPelicula*seg;
    nodoListaPelicula*ante;

    if((listaPelis) && (id==listaPelis->p.idPelicula))
    {
        nodoListaPelicula*aux=listaPelis;
        listaPelis=listaPelis->sig;
        free(aux);
    }

    else
    {
        seg=listaPelis;
        while((!seg) && (id!=listaPelis->p.idPelicula))
        {
            ante=seg;
            seg=seg->sig;
        }
        if(!seg)
        {
            ante->sig=seg->sig;
            free(seg);
        }
    }

    return listaPelis;
}


// *************************************** DEFINICION DE FUNCIONES ********************************************

//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA USUARIOS
//***********************************************************************************************************************************//


void altaUsuario(char archiUsu[], stCelda arregloUsuActivos[]) // Funcion general de alta de usuario
{

    // Declaración de variables locales
    int validacionPais=0;
    int usuarioExiste=0;
    int longPass=0;
    int i=0;
    int tamanioArray=0;
    long cantReg=0;
    char passAux[11];
    char control='s'; // Variable de control para ciclo while principal de solicitud de datos de usuarios
    stUsuario usuAux; // Se crea estructura auxiliar para trabajo temporal

    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tREGISTRO DE NUEVO USUARIO");
    printf("\n*****************************************************");
    printf("\n");

    while(control=='s')
    {

        printf("Ingrese el nombre de usuario: ");
        fflush(stdin);
        gets(usuAux.nombreUsuario);
        usuarioExiste=validarUserExiste(archiUsu, usuAux.nombreUsuario); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag

        if(usuarioExiste!=0)
        {
            printf("Ese usuario ya existe, tiene 3 intentos mas\n");

            while((usuarioExiste!=0) && (i<3))
            {
                printf("Ingrese un nuevo nombre de usuario: ");
                fflush(stdin);
                gets(usuAux.nombreUsuario);
                usuarioExiste=validarUserExiste(archiUsu, usuAux.nombreUsuario); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
                i++;
            }
            if(usuarioExiste!=0)
            {
                printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                exit(1);
            }
            else
            {
                printf("El ingreso ha sido exitoso\n");
            }
        }

        printf("Ingrese la contrasenia(maximo 10 caracteres): ");
        fflush(stdin);
        gets(passAux);
        longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag

        if(longPass!=0)
        {
            printf("La contrasenia debe tener 10 caracteres como maximo, tiene 3 intentos mas\n");

            while((longPass!=0) && (i<3))
            {
                printf("Ingrese una nueva contrasenia: ");
                fflush(stdin);
                gets(passAux);
                longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag
                i++;;
            }

            if(longPass==0)
            {
                printf("El ingreso ha sido exitoso\n");
            }

            else
            {
                printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                exit(1);
            }
        }

        encriptacionPass(passAux, usuAux.pass);

        printf("Ingrese anio de nacimiento: ");
        scanf("%i", &usuAux.anioNacimiento);

        printf("Ingrese el genero(m/f): ");
        fflush(stdin);
        scanf("%c", &usuAux.genero);

        do
        {
            printf("Ingrese el pais(Solo caracteres): ");
            fflush(stdin);
            gets(usuAux.pais);
            validacionPais=validarTipoChar(usuAux.pais);
        }
        while(validacionPais!=0);


//        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo
//
//        if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
//        {
//            usuAux.idUsuario=1; // Se le asigna el valor 1 al primer registro
//        }
//        else
//        {
//            cantReg=(ftell(archi)/sizeof(stUsuario)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura
//            usuAux.idUsuario=cantReg+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
//        }

        usuAux.eliminado=0; // Se asigna negativo como valor predeterminado

        usuAux.admin=0; // Por defecto NO es administrador


        usuAux.idUsuario=cantUsuariosTotales(archiUsu)+1; ///CHEQUEAR COMO FUNCIONA


        // ver como se usa realloc

        tamanioArray=calcularTamanioArrayUsuarios(arregloUsuActivos); ///Reemplazar funcion con la de Nahuel

        arregloUsuActivos=realloc(arregloUsuActivos, sizeof(stCelda)*(tamanioArray+1));

        arregloUsuActivos[tamanioArray].usr=usuAux;




        printf("Desea continuar ingresando usuarios(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesión
        fflush(stdin);
        scanf("%c", &control);

        if(control=='s')
        {
            system("cls");
            puts("****** ALTA DE OTRO USUARIO ******\n");
        }

    }

//        fclose(archi); // Cierre del archivo
//    }
}



void bajaUsuario(char archiUsu[]) //Elimina usuarios pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idUsu=0;

    stUsuario usuAux;

    FILE *archi;

    archi=fopen(archiUsu, "r+b");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tBAJA DE USUARIOS");
        printf("\n*****************************************************");
        printf("\n");

        printf("\nIngrese el ID del usuario a eliminar: ");
        scanf("%i", &idUsu);
        printf("\nEsta seguro de que desea eliminar el usuario(s/n?"); // Chequea nuevamente si quiere avanzar con la baja de la pelicula
        fflush(stdin);
        scanf("%c", &control);
        if(control=='s') // Si confirma, se avanza
        {
            fseek(archi, (idUsu-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&usuAux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
            usuAux.eliminado=1; // Se cambia el estado del usuario a a eliminar
            fseek(archi, (idUsu-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fwrite(&usuAux, sizeof(usuAux), 1, archi); // Escribo el nuevo valor de eliminado en el archivo
            printf("\nEl usuario se elimino correctamente\n");
            printf("\nNombre del usuario: %s", usuAux.nombreUsuario);
            printf("\nEstado: %i", usuAux.eliminado);
        }
        else // Si no confirma, se sale del programa
        {
            exit(1);
        }
        fclose(archi);
    }
}


void mostrarUserParaModif(char archiUsu[])//Modificacion de usuario para administrador
{
    FILE *archi = fopen(archiUsu,"rb+");
    stUsuario aux;
    //  int dim=30;
    //  int pelisVistas[dim];
//    int cantPelisVistas=0;
    int i=0, flag=0, id=0, a=0;
    char control='s', passAux[10];
    if(archi!=NULL)
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMODIFICACION DE USUARIOS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\nIngrese la ID que desea buscar \n");

        scanf("%i", &id);

        while (!feof(archi)&&flag==0) //Busqueda por id de usuario
        {
            fread(&aux,sizeof(stUsuario),1,archi);
            if(id==aux.idUsuario)
            {
                flag=1;
            }
        }

        if(flag==1) //En caso de que se encuentre el usuario se muestra por pantalla y se procede a seleccionar el campo a modificar
        {

            fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&aux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado

            printf("Los datos del usuario son los siguientes: \n");
            printf("El nombre del Usuario es: %s \n", aux.nombreUsuario);
            desencriptacionPass(aux.pass, passAux);
            printf("Password: %s\n", passAux);
            printf("El anio de nacimiento del Usuario es: %i \n", aux.anioNacimiento);
            printf("El genero del Usuario es: %c \n", aux.genero);
            printf("El nombre del Usuario es: %s \n", aux.pais);
            printf("IDs de Peliculas vistas: \n");
            if(aux.eliminado==1)
            {
                printf("El usuario ha sido marcado como eliminado de la base\n");
            }
            else
            {
                printf("El usuario esta activo\n");
            }
//            for(i=0; i<aux.cantVistas; i++)
//            {
//                printf("%i \n", aux.peliculasVistas[i]);
//            }
            system("pause");

            do
            {
                a=menumodif(archiUsu);

                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fread(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

                switch (a)
                {

                case 1:

                    printf("Ingrese el nuevo nombre del usuario: \n");
                    fflush(stdin);
                    gets(aux.nombreUsuario);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 2:

                    printf("Ingrese el nuevo password del usuario: \n");
                    fflush(stdin);
                    gets(passAux);
                    encriptacionPass(passAux, aux.pass);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 3:

                    printf("Ingrese el nuevo anio de nacimiento del usuario: \n");
                    scanf("%i", &aux.anioNacimiento);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 4:

                    printf("Ingrese el nuevo genero del usuario: \n");
                    fflush(stdin);
                    scanf ("%c", &aux.genero);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 5:

                    printf("Ingrese el nuevo pais del usuario: \n");
                    fflush(stdin);
                    gets(aux.pais);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 6:

                    printf("Ingrese el nuevo estado en la base del usuario(0 si activo - 1 si eliminado): \n");
                    scanf("%i", &aux.eliminado);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

//               case 7:
                    //                 cantPelisVistas=registroPelisVistas(pelisVistas[dim], dim);
                    //               printf("El usuario ha visto %i peliculas", cantPelisVistas);

                    break;

                default:
                    exit(1);
                    break;

                }

                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

            }
            while(a!=0&&control=='s');
        }

        else
        {

            printf("No se encuentra la ID en el archivo \n");
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR \n");
    }
}

void mostrarUser(char archiUsu[], char nombreUsuario[])//Se Muestra info almacenada al Usuario
{
    FILE *archi = fopen(archiUsu,"rb+");
    stUsuario aux;
    int i=0, flag=0;
    char passAux[10];
    if(archi!=NULL)
    {
        while (!feof(archi)&&flag==0) //Busqueda por nombre del usuario para luego mostrar por pantalla
        {
            fread(&aux,sizeof(stUsuario),1,archi);
            if(strcmp(nombreUsuario,aux.nombreUsuario)==0)
            {
                printf("Sus datos son los siguientes: \n");
                printf("Nombre del Usuario es: %s \n", aux.nombreUsuario);
                desencriptacionPass(aux.pass, passAux);
                printf("Password: %s\n", passAux);
                printf("Su anio de nacimiento es: %i \n", aux.anioNacimiento);
                printf("Su genero es: %c \n", aux.genero);
                printf("Su Pais de nacimiento es: %s \n", aux.pais);
//                printf("IDs de sus Peliculas vistas: \n");
//                for(i=0; i<aux.cantVistas; i++)
//                {
//                    printf("%i \n", aux.peliculasVistas[i]);
//                }
                flag=1;

            }
            else
                printf("Error \n");
            fclose(archi);
        }
    }
    else
        printf("ERROR \n");
}


//void desencriptacionPass(int mEncriptada[2][5], char pass[])
//{
//    int i=0,j=0,k=0;
//
//    int inversa[2][2]= {{5,-3}, {-3,2}};   //Matriz inversa de Matriz LLave
//
//    int  desencriptada[2][5];
//
//    char passbeta[10];
//
//    mostrarPass(2,5,mEncriptada);
//
//    system("pause");
//
//    for (j=0; j<5; j++)
//    {
//        for (i=0; i<2; i++)
//        {
//            productoDeMatrices(inversa,mEncriptada,desencriptada); //Multiplicacion por la inversa para desencriptacion
//        }
//    }
//
//      mostrarPass(2,5,desencriptada);
//
//    system("pause");
//
//    for(j=0; j<5; j++)     //Conversion de matriz a arreglo
//    {
//        for(i=0; i<2; i++)
//        {
//            pass[k]=desencriptada[i][j]; //Conversion de enteros a char
//            k++;
//        }
//    }
//
//}


void desencriptacionPass(int mEncriptada[2][5], char pass[])
{
    int i=0,j=0,k=0;

    int inversa[2][2]= {{5,-3}, {-3,2}};   ///Matriz inversa de Matriz LLave

    int  desencriptada[2][5];

    ///char passbeta[10];

    ///mostrarPass(2,5,mEncriptada);

    ///system("pause");

    for (j=0; j<5; j++)
    {
        for (i=0; i<2; i++)
        {
            productoDeMatrices(inversa,mEncriptada,desencriptada); ///Multiplicacion por la inversa para desencriptacion
        }
    }

    ///  mostrarPass(2,5,desencriptada);

    ///system("pause");

    for(j=0; j<5; j++)     ///Conversion de matriz a arreglo
    {
        for(i=0; i<2; i++)
        {
            pass[k]=desencriptada[i][j]; ///Conversion de enteros a char
            k++;
        }
    }

}

//void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]) //Funcion para Multiplicacion de Matrices
//{
//    int i,j;
//
//    for (i=0; i<2; i++)
//    {
//        for (j=0; j<5; j++)
//        {
//            Prod[i][j]=(Mat[i][0]*Pass[0][j]+Mat[i][1]*Pass[1][j]);
//        }
//    }
//}

void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]) ///Funcion para Multiplicacion de Matrices
{
    int i,j;

    for (i=0; i<2; i++)
    {
        for (j=0; j<5; j++)
        {
            Prod[i][j]=(Mat[i][0]*Pass[0][j]+Mat[i][1]*Pass[1][j]);
        }
    }
}


//void encriptacionPass(char pass[], int mEncriptada[2][5]) //Funcion para encriptacion de password
//{
//    int validos,j, i, k=0;
//
//    // Definimos la matriz llave con la que encriptamos el password
//    // en nuestro caso le asginamos el valor numerico de las primeras cuatro letras del nombre del grupo GUMT
//
//    int matrizLLave[2][2]= {{2,3},{3,5}};
//
//    int matrizPass[2][5];
//
//    // Validamos la longitud del password para que en caso de ser inferior a 10 caracteres completar con espacios la matriz
//
//    validos=strlen(pass);
//
//    if (validos<10)
//    {
//        for (i=validos; i<10; i++)
//        {
//            pass[i]='\0';
//        }
//    }
//
//    if (validos==10)
//    {
//        pass[validos+1]='\0';
//    }
//
//    //Conversion de password a Matriz para su posterior multiplicacion
//
//    for(j=0; j<5; j++)
//    {
//        for(i=0; i<2; i++)
//        {
//            for(i=0; i<2; i++)
//            {
//                matrizPass[i][j]=pass[k];
//                k++;
//            }
//        }
//    }
//
//
//    //Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente
//
//    //mostrarPass(2,5,matrizPass);
//
//    //system("pause");
//
//
//    //Encriptacion de matrices a traves de multiplicacion de password por matriz llave
//
//    productoDeMatrices(matrizLLave, matrizPass, mEncriptada);
//
//    //Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente
//
//    //mostrarPass(2,5,mEncriptada);
//
//    //system("pause");
//}

void encriptacionPass(char pass[], int mEncriptada[2][5]) ///Funcion para encriptacion de password
{
    int validos,j, i, k=0;

    /// Definimos la matriz llave con la que encriptamos el password
    /// en nuestro caso le asginamos el valor numerico de las primeras cuatro letras del nombre del grupo GUMT

    int matrizLLave[2][2]= {{2,3},{3,5}};

    int matrizPass[2][5];

    /// Validamos la longitud del password para que en caso de ser inferior a 10 caracteres completar con espacios la matriz

    validos=strlen(pass);

    if (validos<10)
    {
        for (i=validos; i<10; i++)
        {
            pass[i]='\0';
        }
    }

    if (validos==10)
    {
        pass[validos+1]='\0';
    }

    ///Conversion de password a Matriz para su posterior multiplicacion

    for(j=0; j<5; j++)
    {
        for(i=0; i<2; i++)
        {
            for(i=0; i<2; i++)
            {
                matrizPass[i][j]=pass[k];
                k++;
            }
        }
    }


    ///Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente

    ///mostrarPass(2,5,matrizPass);

    ///system("pause");


    ///Encriptacion de matrices a traves de multiplicacion de password por matriz llave

    productoDeMatrices(matrizLLave, matrizPass, mEncriptada);

    ///Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente

    ///mostrarPass(2,5,mEncriptada);

    ///system("pause");
}


void mostrarArrayUsuarios(stUsuario array[], int validos)//Muestra los datos de usuarios por pantalla
{
    //stUsuario aux;
    int i=0, j=0;
    char passAux[10];
    printf("El listado actual de usuarios existentes es el siguiente:\n\n");
    for (i=0; i<validos; i++)
    {
        if(array[i].eliminado!=1)
        {
            printf("El ID del Usuario es: %i \n", array[i].idUsuario);
            printf("El nombre del Usuario es: %s \n", array[i].nombreUsuario);
            desencriptacionPass(array[i].pass, passAux);
            printf("Password: %s \n", passAux);
            printf("El anio de nacimiento del Usuario es: %i \n", array[i].anioNacimiento);
            printf("El genero del Usuario es: %c \n", array[i].genero);
            printf("El nombre del Usuario es: %s \n", array[i].pais);
            printf("IDs de Peliculas vistas: \n");
//            for(j=0; j<array[i].cantVistas; j++)
//            {
//                printf("%i \n", array[i].peliculasVistas[j]);
//            }
            printf("\n \n");
        }
    }

}

int cargarArrayUsuarios(char archiUsu[], stUsuario array[])//Se pasan los datos de usuarios a un arreglo y devuelve la cantidad de registros almacenados(validos)
{
    FILE *archi;

    archi=fopen(archiUsu, "rb");

    stUsuario aux;

    int i=0, validos=0;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        for(i=0; !feof(archi); i++)
        {
            fread(&aux, sizeof(stUsuario), 1, archi);

            if(!feof(archi))
            {
                array[i]=aux;
            }
        }
        fclose(archi);
    }

    validos=i-1;

    return validos;
}

void listadoUsuarios(char archiUsu[])//Se Muestra Listado de Usuarios al Admin
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario arraydeusuarios[50];

    int validos=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayUsuarios(archiUsu, arraydeusuarios);//se carga el array de usuarios y devuelve los validos
        mostrarArrayUsuarios(arraydeusuarios, validos);//se muestra el array por pantalla
    }

    system("pause");

    fclose(archi);

}

void consultaUsuarioAdmin(char archiUsu[])//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario arraydeusuarios[50];

    int validos=0, id=0, i = 0, j=0, flag=0;

    char passAux[10];

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID del usuario que desea consultar la informacion: \n");
        scanf("%i", &id);
        validos=cargarArrayUsuarios(archiUsu, arraydeusuarios);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==arraydeusuarios[i].idUsuario&&arraydeusuarios[i].eliminado!=1)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("El nombre del Usuario es: %s \n", arraydeusuarios[i].nombreUsuario);
                desencriptacionPass(arraydeusuarios[i].pass, passAux);
                printf("Password: %s", passAux);
                printf("El anio de nacimiento del Usuario es: %i \n", arraydeusuarios[i].anioNacimiento);
                printf("El genero del Usuario es: %c \n", arraydeusuarios[i].genero);
                printf("El Usuario es de: %s \n", arraydeusuarios[i].pais);
                printf("\n \n");
                flag=1;
            }
        }
        if(flag==0) //Flag en caso de no encontrar el id
        {
            printf("No se encuentra el id \n");
        }

        fclose(archi);

    }

    system("pause");

}

void consultaUsuario(char archiUsu[], char nombreUsuario [])//Se Muestra info por Nombre al Usuario
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario usuAux;

    int j=0, flag=0;

    char passAux[10];

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        fread(&usuAux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
        while(!feof(archi)&&flag!=1)
        {
            if(strcmpi(nombreUsuario,usuAux.nombreUsuario)==0)//busqueda en el array hasta encontrar el nombre y mostrarlo por pantalla
            {
                printf("Nombre: %s \n", usuAux.nombreUsuario);
                desencriptacionPass(usuAux.pass, passAux);
                printf("Password: %s \n", passAux);
                printf("Anio de nacimiento: %i \n", usuAux.anioNacimiento);
                printf("Genero: %c \n", usuAux.genero);
                printf("Pais de nacimiento: %s \n", usuAux.pais);
                printf("\n \n");
                flag=1;
            }
            else
            {
                fread(&usuAux, sizeof(stUsuario), 1, archi);
            }
        }
        if(flag==0) //Flag en caso de no encontrar el usuario
        {
            printf("Error \n");
        }

        fclose(archi);

    }

    system("pause");

}

void cargarIdPeliAUser(int id, char nombreUsuario[],char archiUsu[])
{
    FILE *archi;
    archi=fopen(archiUsu, "rb+");
    stUsuario usuAux;
    int flag=0;
    if(archi==NULL)
    {
        printf("ERROR");
        exit(1);
    }
    else
    {
        fread(&usuAux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
        while(!feof(archi)&&flag!=1)
        {
            if(strcmpi(usuAux.nombreUsuario,nombreUsuario)==0)
            {
                printf("validacion usuario encontrado\n");
//                usuAux.peliculasVistas[usuAux.cantVistas]=id;
//                usuAux.cantVistas+=1;
                flag=1;
                fseek(archi, (usuAux.idUsuario-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fwrite(&usuAux, sizeof(usuAux), 1, archi); // Escritura del registro indicado
            }
            else
            {
                printf("busqueda activa\n");
                fread(&usuAux, sizeof(stUsuario), 1, archi);
            }

        }

        fclose(archi);
    }
}



//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA PELICULAS
//***********************************************************************************************************************************//

void altaPelicula(char archiPeli[]) // Funcion general de alta de películas
{
    // Declaración de variables locales
    int validacionPais=0;
    int validacionDirector=0;
    int validacionGenero=0;
    int peliculaExiste=0;
    int cantReg=0;
    int i=0;
    char control='s'; // Variable de control para ciclo while principal de solicitud de los datos de peliculas
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal

    FILE *archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(archiPeli, "a+b"); //Se chequea el acceso al archivo bajo la modalidad lectura-escritura

    if(archi==NULL) // Chequea si se puede abrir el archivo usando sólo lectura
    {
        printf("\nNo se pudo abrir el archivo");
        exit(1); // Sale del programa si no se pudo abrir el archivo
    }

    else
    {
        system("cls"); // Limpio pantalla
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tALTA DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");

        while(control=='s')
        {

            printf("Ingrese el nombre de la pelicula: ");
            fflush(stdin);
            gets(peliAux.nombrePelicula);
            peliculaExiste=validarPeliExiste(archiPeli, peliAux.nombrePelicula); // Chequea que el nombre de la pelicula en cuestión no exista en el archivo para evitar que se duplique mediante un flag

            if(peliculaExiste!=0)
            {
                printf("Ya existe una pelicula con ese nombre, desea continuar intentandolo(s/n)?\n");
                fflush(stdin);
                gets(peliAux.nombrePelicula);

                while((peliculaExiste!=0) && (i<3))
                {
                    printf("Ingrese el nombre de la pelicula nuevamente: ");
                    fflush(stdin);
                    gets(peliAux.nombrePelicula);
                    peliculaExiste=validarPeliExiste(archiPeli, peliAux.nombrePelicula); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
                    i++;
                }
                if(peliculaExiste!=0)
                {
                    printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                    exit(1);
                }
                else
                {
                    printf("El ingreso ha sido exitoso\n");
                }
            }

            do
            {
                printf("Ingrese el nombre del director de la pelicula(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.director);
                validacionDirector=validarTipoChar(peliAux.director);
            }
            while(validacionDirector!=0);

            do
            {
                printf("Ingrese el genero(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.genero);
                validacionGenero=validarTipoChar(peliAux.genero);
            }
            while(validacionGenero!=0);

            do
            {
                printf("Ingrese el pais(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.pais);
                validacionPais=validarTipoChar(peliAux.pais);
            }
            while(validacionPais!=0);

            do
            {
                printf("Ingrese el anio: ");
                scanf("%i", &peliAux.anio);
            }
            while(peliAux.anio<1895 || peliAux.anio>2018);

            do
            {
                printf("Ingrese la valoracion(Escala del 1 al 5: 1 pesima - 5 excelente): ");
                scanf("%i", &peliAux.valoracion);
            }
            while((peliAux.valoracion<0) || (peliAux.valoracion>5));

            do
            {
                printf("Ingrese la categoria de la pelicula(0 si es ATP - 13 si es para mayores de 13 anios - 16 y 18 respectivamente): ");
                scanf("%i", &peliAux.pm);
            }
            while(peliAux.pm<0 || peliAux.pm>18);

            fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo

            if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
            {
                peliAux.idPelicula=1; // Se le asigna el valor 1 al primer registro
            }
            else
            {
                cantReg=(ftell(archi)/sizeof(stPelicula)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura
                peliAux.idPelicula=cantReg+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
            }

            peliAux.eliminado=0; // Se asigna negativo como valor predeterminado

            fwrite(&peliAux, sizeof(stPelicula), 1, archi); // Se graba los datos capturados en el archivo

            printf("Desea continuar ingresando peliculas(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesión
            fflush(stdin);
            scanf("%c", &control);

            if(control=='s')
            {
                system("cls"); // Inicia nueva pantalla de carga de peliculas
                puts("****** ALTA DE OTRA PELICULA ******\n");
            }
        }
        fclose(archi); // Cierre del archivo
    }
}


void bajaPelicula(char archiPeli[])//Elimina peliculas pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idPeli=0;

    stPelicula peliAux;

    FILE *archi;

    archi=fopen(archiPeli, "r+b");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tBAJA DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");

        printf("\nIngrese el ID de la pelicula a eliminar: ");
        scanf("%i", &idPeli);
        printf("\nEsta seguro de que desea eliminar la pelicula(s/n?"); // Chequea nuevamente si quiere avanzar con la baja de la pelicula
        fflush(stdin);
        scanf("%c", &control);
        if(control=='s') // Si confirma, se avanza
        {
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&peliAux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado
            peliAux.eliminado=1; // Se cambia el estado de la pelicula a eliminada
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fwrite(&peliAux, sizeof(peliAux), 1, archi); // Escribo el nuevo valor de eliminado en el archivo
            printf("\nLa pelicula se elimino correctamente\n");
            printf("\nNombre de la pelicula: %s", peliAux.nombrePelicula);
            printf("\nEstado: %i", peliAux.eliminado);
        }
        else // Si no confirma, se sale del programa
        {
            exit(1);
        }
        fclose(archi);
    }
}

void mostrarPeliParaModif(char archiPeli[])//Modificacion de peliculas para administrador
{
    FILE *archi = fopen(archiPeli,"rb+");
    stPelicula aux;
    int flag=0, id=0, a=0;
    char control='s';
    if(archi!=NULL)
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMODIFICACION DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\nIngrese la ID que desea buscar \n");

        scanf("%i", &id);

        while (!feof(archi)&&flag==0) //Busqueda por id de pelicula
        {
            fread(&aux,sizeof(stPelicula),1,archi);
            if(id==aux.idPelicula)
            {
                flag=1;
            }
        }

        if(flag==1) //En caso de que se encuentre la pelicula se muestra por pantalla y se procede a seleccionar el campo a modificar
        {

            fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&aux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado

            printf("Los datos de la pelicula son los siguientes: \n");
            printf("El nombre de la pelicula es: %s \n", aux.nombrePelicula);
            printf("El director de la pelicula es: %s \n", aux.director);
            printf("El anio de filmacion de la pelicula es: %i \n", aux.anio);
            printf("El genero de la pelicula es: %s \n", aux.genero);
            printf("El pais de origen de la pelicula es: %s \n", aux.pais);

            printf("La valoracion de la pelicula es: %i \n", aux.valoracion);
            printf("La clasificacion de la pelicula es: %i \n", aux.pm);
            if(aux.eliminado==1)
            {
                printf("La pelicula ha sido marcada como eliminada de catalogo\n");
            }
            else
            {
                printf("La pelicula esta en catalogo\n");
            }

            system("pause");

            do
            {
                a=menuModifPelis(archiPeli);

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fread(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

                switch (a)
                {

                case 1:

                    printf("Ingrese el nuevo nombre de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.nombrePelicula);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 2:
                    printf("Ingrese el nuevo director de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.director);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 3:

                    printf("Ingrese el nuevo anio de filmacion de la pelicula: \n");
                    scanf("%i", &aux.anio);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 4:

                    printf("Ingrese el nuevo genero de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.genero);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 5:

                    printf("Ingrese el nuevo pais de origen de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.pais);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 6:

                    printf("Ingrese la nueva valoracion de la pelicula(Escala del 1 al 5: 1 pesima - 5 excelente): \n");
                    scanf("%i", &aux.valoracion);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 7:

                    printf("Ingrese la nueva clasificacion de la pelicula(0 si es ATP - 13 si es para mayores de 13 anios - 16 y 18 respectivamente: \n");
                    scanf("%i", &aux.pm);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 8:

                    printf("Ingrese el nuevo estado en catalogo de la pelicula(0 si activa - 1 si eliminada): \n");
                    scanf("%i", &aux.eliminado);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                default:
                    exit(1);
                    break;

                }

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

            }
            while(a!=0&&control=='s'); // Mientras se desee continuar
        }

        else
        {

            printf("No se encuentra la ID en el archivo \n"); // Muestra este error en caso que ese ID no se encuentre graado en el archivo
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR \n"); // Muestra error si no se pudo abrir el archivo
    }
}

void consultaPeliAdmin(char archiPeli[])//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula array[50];

    int validos=0, id=0, i = 0, flag=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea consultar: \n");
        scanf("%i", &id);
        validos=cargarArrayPeliculas(archiPeli, array);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==array[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("Pelicula: %s \n", array[i].nombrePelicula);
                printf("Director: %s \n", array[i].director);
                printf("Genero: %s \n", array[i].genero);
                printf("Pais: %s \n", array[i].pais);
                printf("Año: %i \n", array[i].anio);
                printf("Valoracion: %i \n", array[i].valoracion);
                printf("Calificacion: %i \n", array[i].pm);
                if(array[i].eliminado==1)
                {
                    printf("La pelicula fue marcada como eliminada en el catalogo");
                }
                else
                {
                    printf("La pelicula figura activa en el catalogo");
                }
                printf("\n \n");
                flag=1;
            }
        }
        if(flag==0) //Flag en caso de no encontrar el id
        {
            printf("No se encuentra el id \n");
        }

        fclose(archi);

    }

    system("pause");

}


void insertar(stPelicula array[], int i)
{
    stPelicula aux=array[i+1];

    while(i>=0 && strcmpi(array[i+1].genero,array[i].genero)<0)
    {
        array[i+1]=array[i];
        i--;
    }
    array[i+1]=aux;
}


int cargarArrayPeliculas(char archiPeli[], stPelicula array[])
{
    FILE *archi;

    archi=fopen(archiPeli, "rb");

    stPelicula peli;

    int i=0, validos=0;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        for(i=0; !feof(archi); i++)
        {
            fread(&peli, sizeof(stPelicula), 1, archi);

            if(!feof(archi))
            {
                array[i]=peli;
            }
        }
        fclose(archi);
    }

    validos=i-1;

    return validos;
}


void ordenarGenero (char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula arraydepeliculas[50];

    int validos=0;

    int i = 0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayPeliculas(archiPeli, arraydepeliculas);//se carga el array de peliculas

        while (i<validos-1)//se recorre el array comparando los generos de las peliculas y ordenando de mayor a menor
        {
            insertar(arraydepeliculas,i);
            i++;
        }

        mostrarArrayPeliculas(arraydepeliculas, validos);//se muestra el array por pantalla
        fclose(archi);
    }

    system("pause");

}


void ordenarTitulo(char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula arraydepeliculas[50];

    int validos=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayPeliculas(archiPeli,arraydepeliculas);//se carga el array de peliculas y se verifican los validos
        ordenacionSeleccion(arraydepeliculas,validos);//se ordenan por el metodo de ordenacion por seleccion
        mostrarArrayPeliculas(arraydepeliculas, validos); //se muestran por pantalla
        fclose(archi);
    }
    system("pause");
}

void ordenacionSeleccion(stPelicula array[], int validos)
{
    int posmenor;
    stPelicula aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor=posicionMenor(array,i,validos);
        aux = array[posmenor];
        array[posmenor]= array[i];
        array[i]=aux;
        i++;
    }
}

int posicionMenor(stPelicula array[], int pos, int validos)
{
    char menor[30];
    strcpy(menor,array[pos].nombrePelicula);
    int posmenor=pos;
    int i=pos+1;
    while (i<validos)
    {
        if (strcmpi(menor,array[i].nombrePelicula)> 0)
        {
            strcpy(menor, array[i].nombrePelicula);
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}

int verPelicula(char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb+");

    stPelicula array[50];

    int validos=0, id=0, i = 0, flagid=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea ver: \n");
        scanf("%i", &id);
        validos=cargarArrayPeliculas(archiPeli, array);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==array[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                flagid=1;
                printf("Disfrute de : \n\n");
                printf("Pelicula: %s \n", array[i].nombrePelicula);
                printf("Del Director: %s \n", array[i].director);
                printf("\n \n");
            }
        }
        if(flagid==0) //Flag en caso de no encontrar el id
        {
            printf("No se encuentra la pelicula \n");
            id=0; //En caso de no encontrar la pelicula retornara ID=0, es decir Falso
        }
        fclose(archi);

    }

    system("pause");
    return id;
}

//***********************************************************************************************************************************//
//                                                  FUNCIONES DE VALIDACION
//***********************************************************************************************************************************//

//int validarLongPass(char pass[])  // Valida si la contraseña ingresada tiene más de 10 caracteres
//{
//    int flag=0;
//
//    if(strlen(pass)>10)  //Chequea la longitud del nombre de usuario ya que el máximo son 10 caracteres. Devuelve 1 si positivo
//    {
//        flag=1;
//    }
//    return flag;
//}

int validarLongPass(char pass[])  /// Valida si la contrase�a ingresada tiene m�s de 10 caracteres
{
    int flag=0;

    if(strlen(pass)>10)  ///Chequea la longitud del nombre de usuario ya que el m�ximo son 10 caracteres. Devuelve 1 si positivo
    {
        flag=1;
    }
    return flag;
}

int validarUserExiste(char archiUsu[], char nombreUsuario[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stUsuario usuAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(archiUsu, "rb"); // Abre al archivo en modo sólo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si el usuario ya existe");
        exit(1);
    }

    else
    {

        while((fread(&usuAux, sizeof(stUsuario), 1, archi)>0) && (flag!=1))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(strcmp(usuAux.nombreUsuario, nombreUsuario)==0)  //Chequea si ambos strings son iguales
            {
                flag=1; // Si ambos strings son iguales, asigno valor 1 a flag como positivo
            }
        }
    }

    fclose(archi); // Cierra el archivo

    return flag; // Devuelve el valor de flag para su proceso en la función que la invoca
}

int validarTipoAlfanumerico(char cadena[])  // Devuelve 1 si la variable analizada es cadena, 0 si no lo es
{

    int i=0;
    int j=0;
    int flag=0;

    j=strlen(cadena);

    while((i<j) && (flag==0))
    {
        if(isalnum(cadena[i])!=0)
        {
            i++;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}


int validarTipoChar(char cadena[])  // Devuelve 1 si la variable analizada es cadena, 0 si no lo es
{

    int i=0;
    int j=0;
    int flag=0;

    j=strlen(cadena);

    while((i<j) && (flag==0))
    {
        if(isalpha(cadena[i])!=0)
        {
            i++;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}

//int validacionPass(char archiUsu[], char nombre[], char pass[])
//{
//    //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada
//    //Retorna true or false
//
//    stUsuario usuario;
//
//    int coincidencia=0;
//
//    char passGuardado[11];
//
//    FILE *archi;
//
//    archi=fopen(archiUsu, "rb");
//
//    if (archi==NULL)
//    {
//        printf("No se pudo abrir el archivo");
//    }
//    else
//    {
//        while ((fread(&usuario, sizeof(stUsuario), 1,archi)>0 && coincidencia==0))
//        {
//            if(strcmpi(usuario.nombreUsuario,nombre)==0) //Validacion nombre de usuario
//            {
//                desencriptacionPass(usuario.pass, passGuardado);
//                if(strcmpi(pass,passGuardado)==0)//Validacion Password
//                {
//                    coincidencia=1;//flag
//                }
//
//            }
//            else
//            {
//                coincidencia=0;
//            }
//        }
//
//        fclose(archi);
//    }
//
//    return coincidencia;
//}


int validacionPass(stCelda arregloUsuActivos[], char nombre[], char pass[]) // Pasa por parámetro la estructura en lugar del archivo
{
    ///Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada
    ///Retorna true or false

    int coincidencia=0, i, validos;

    validos=calcularValidos(arregloUsuActivos); // Esta función no está incluida

    char passGuardado[11];

    for(i=0; i<validos&&coincidencia==0; i++)
    {
        if(strcmpi(arregloUsuActivos[i].usr.nombreUsuario,nombre)==0) ///Validacion nombre de usuario
        {
            desencriptacionPass(arregloUsuActivos[i].usr.pass, passGuardado);
            if(strcmpi(pass,passGuardado)==0)///Validacion Password
            {
                coincidencia=1;///flag
            }

        }
        else
        {
            coincidencia=0;
        }
    }


    return coincidencia;
}

//int validacionPassAdmin(char pass[]) //No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario
//{
//    //Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada y comparacion con la ingresada
//    //Retorna true or false
//
//    int coincidencia=0;
//
//    char passAdmin[11];
//
//    int passEncriptada[2][5]= {{557,566,499,208,0},{894,907,798,312,0}};
//
//    FILE *archi;
//
//    archi=fopen(archiUsu, "rb");
//
//    if (archi==NULL)
//    {
//        printf("No se pudo abrir el archivo");
//    }
//    else
//    {
//        desencriptacionPass(passEncriptada, passAdmin);
//        if(strcmpi(pass,passAdmin)==0)//Validacion Password
//        {
//            coincidencia=1;//flag
//        }
//
//        else
//        {
//                coincidencia=0;
//        }
//    }
//
//    return coincidencia;
//}


int validacionPassAdmin(char pass[]) ///No se pasa por parametro el nombre del administrador ya que el admin poseen un solo nombre de usuario
{
    ///Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada y comparacion con la ingresada
    /// Retorna true or false

    int coincidencia=0;

    char passAdmin[11];

    int passEncriptada[2][5]= {{557,566,499,208,0},{894,907,798,312,0}};

    desencriptacionPass(passEncriptada, passAdmin);
    if(strcmpi(pass,passAdmin)==0)//Validacion Password
    {
        coincidencia=1;//flag
    }

    else
    {
        coincidencia=0;
    }


    return coincidencia;
}

int validarPeliExiste(char nombrePelicula[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(archiPeli, "rb"); // Abre al archivo en modo sólo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {

        while((fread(&peliAux, sizeof(stPelicula), 1, archi)>0) && (flag!=1))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(strcmp(peliAux.nombrePelicula, nombrePelicula)==0)  //Chequea si ambos strings son iguales
            {
                flag=1; // Si ambos strings son iguales, asigno valor 1 a flag como positivo
            }
        }
    }

    fclose(archi); // Cierra el archivo

    return flag; // Devuelve el valor de flag para su proceso en la función que la invoca
}
//***********************************************************************************************************************************//
//                                                  FUNCIONES DE SUBMENUES / LOGIN
//***********************************************************************************************************************************//

void loguinadm()
{
    int login=0;
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE ADMINISTRADOR");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE EL PASSWORD DE ADMINISTRADOR\n\n");
    fflush(stdin);
    gets(passaux);
    login=validacionPassAdmin(passaux);
    if(login==1)
    {
        menuAdmin(archiUsu, archiPeli);
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}

void loginUser()
{
    int login=0;
    char nombreaux[30];
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE USUARIO");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE SU NOMBRE DE USUARIO\n\n");
    fflush(stdin);
    gets(nombreaux);
    printf("\n\tINGRESE SU NOMBRE PASSWORD\n\n");
    fflush(stdin);
    gets(passaux);
    login=validacionPass(arregloUsuActivos, nombreaux, passaux);
    if(login==1)
    {
        menuUsuario(nombreaux);
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}


void menuUsuario(char nombreUsuario[])
{


    int opcion=0, id=0,repetir=0;

    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE USUARIO");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) VER PERFIL");
        printf("\n\t 2) LISTADOS DE PELICULAS");
        printf("\n\t 3) BUSCAR PELICULA");
        printf("\n\t 4) VER PELICULAS RECOMENDADAS");

        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            consultaUsuario(archiUsu, nombreUsuario);
            repetir=1;
            break;

        case 2:
            subMenuListados();
            break;

        case 3:
            id=verPelicula(archiPeli);
            if(id!=0)
            {
                cargarIdPeliAUser(id, nombreUsuario, archiUsu);
            }
            repetir=1;
            break;

        case 4:

            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdmin(char archiUsu[], char archiPeli[])
{

    int opcion=0,repetir=0;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE ADMINISTRADOR\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) GESTIONAR PELICULAS");
        printf("\n\t 2) GESTIONAR USUARIOS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            menuAdminPelis(archiPeli);
            repetir=1;
            break;

        case 2:
            menuAdminUsuarios(archiUsu);
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdminPelis(char archiUsu[])
{

    int opcion=0,repetir=0;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE PELICULAS");
        printf("\n\t 2) BAJA DE PELICULAS");
        printf("\n\t 3) MODIFICACION DE PELICULAS");
        printf("\n\t 4) CONSULTA DE PELICULAS");
        printf("\n\t 5) LISTADOS DE PELICULAS");
        printf("\n\t 0) SALIR DEL PROGRAMA");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            altaPelicula(archiPeli);
            repetir=1;
            break;

        case 2:
            bajaPelicula(archiPeli);
            repetir=1;
            break;

        case 3:
            mostrarPeliParaModif(archiPeli);
            repetir=1;
            break;

        case 4:
            consultaPeliAdmin(archiPeli);
            repetir=1;
            break;

        case 5:
            subMenuListados();
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}

void menuAdminUsuarios(char archiUsu[])
{

    int opcion=0, repetir=0;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE USUARIOS\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE USUARIOS");
        printf("\n\t 2) BAJA DE USUARIOS");
        printf("\n\t 3) MODIFICACION DE USUARIOS");
        printf("\n\t 4) CONSULTA DE USUARIOS");
        printf("\n\t 5) LISTADOS DE USUARIOS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            altaUsuario(archiUsu, arregloUsuActivos);
            repetir=1;
            break;

        case 2:
            bajaUsuario(archiUsu);
            repetir=1;
            break;

        case 3:
            mostrarUserParaModif(archiUsu);
            repetir=1;
            break;

        case 4:
            consultaUsuarioAdmin(archiUsu);
            repetir=1;
            break;

        case 5:
            listadoUsuarios(archiUsu);
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void subMenuListados()
{
    int opcionlistados=0;
    char control='s';
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t L I S T A D O S\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ORDENADOS POR TITULO");
        printf("\n\t 2) ORDENADOS POR GENERO");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        scanf("%i", &opcionlistados);

        switch(opcionlistados)
        {

        case 1:

            ordenarTitulo(archiPeli);
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            break;

        case 2:

            ordenarGenero(archiPeli);
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            break;

        }

    }
    while(control=='s');
}


int menumodif(char archiUsu[])//Menu para administrador para seleccion de campo a modificar
{
    int resp;

    do
    {

        system("CLS");
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Password:\n\t");
        printf("[3]- Anio Nacimiento:\n\t[4]- Genero:\n\t[5]- Pais:\n\t[6]- Estado en la base:\n\t[0]- Salir\n\t");
        scanf("%i", &resp);

    }
    while (0>resp && resp <6);

    return resp;
}

int menuModifPelis(char archiPeli[])//Menu para administrador para seleccion de campo a modificar
{
    int resp;

    do
    {

        system("CLS");
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Director:\n\t");
        printf("[3]- Anio de Filmacion:\n\t[4]- Genero:\n\t[5]- Pais de origen:\n\t[6]- Valoracion:\n\t[7]- Clasificacion:\n\t[8]- Estado en catalogo:\n\t[0]- Salir\n\t");
        scanf("%i", &resp);

    }
    while (0>resp && resp <6);

    return resp;
}

//***********************************************************************************************************************************//
//                                                  FUNCIONES AUXILIARES
//***********************************************************************************************************************************//

void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion) //Carga de peliculas vistas a arreglo de listas de peliculas
{

    FILE*archi;
    archi=fopen(archiPelisUsu, "rb");

    if(archi)
    {
        fseek(archi, 0, SEEK_SET);
        while(!feof(archi))
        {
            stPelisVistas aux;
            fread(&aux, sizeof(stPelisVistas), 1, archi);
            if(!feof(archi))
            {
                if(aux.idUsuario==arregloUsu[posicion].usr.idUsuario)
                {
                    nodoArbolPelicula*auxPeli=buscarPelicula(aux.idPelicula);
                    arregloUsu[posicion].listaPelis=agregarNodoFinal(arregloUsu[posicion].listaPelis, crearNodoPeli(auxPeli->p));
                }
                fread(&aux, sizeof(stPelisVistas), 1, archi);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }
}

void actualizarPelisVistas(stCelda arregloUsuActivos[], int validosUsuActivos, stCelda arregloUsuInactivos[], int validosUsuInactivos) //Pasaje de peliculas vistas a archivo
{
    FILE*archi;
    archi=fopen(archiPelisUsu, "wb");
    int i=0, idLocal=1;

    if(archi)
    {

        stPelisVistas aux;
        for(i=0; i<validosUsuActivos; i++)
        {
            while(arregloUsuActivos[i].listaPelis)
            {
                aux.idUsuario=arregloUsuActivos[i].usr.idUsuario;
                aux.idPelicula=arregloUsuActivos[i].listaPelis->p.idPelicula;
                aux.idPeliVista=idLocal;
                fwrite(&aux, sizeof(stPelisVistas), 1, archi);
                arregloUsuActivos[i].listaPelis=arregloUsuActivos[i].listaPelis->sig;
                idLocal++;

            }
        }
        for(i=0; i<validosUsuInactivos; i++)
        {
            while(arregloUsuInactivos[i].listaPelis)
            {
                aux.idUsuario=arregloUsuInactivos[i].usr.idUsuario;
                aux.idPelicula=arregloUsuInactivos[i].listaPelis->p.idPelicula;
                aux.idPeliVista=idLocal;
                fwrite(&aux, sizeof(stPelisVistas), 1, archi);
                arregloUsuInactivos[i].listaPelis=arregloUsuInactivos[i].listaPelis->sig;
                idLocal++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }
}

void mostrarUsuarios(char archiUsu[]) // Funcion auxiliar usada para chequear que el sistema funcione correctamente visualizando los registros ingresados por pantalla -
{
    char passAux[11];

    stUsuario usuAux;

    FILE * archi;

    archi=fopen(archiUsu, "rb");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo");
    }

    else
    {

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como función devuelve la cantidad de datos leídos)
        {
            fread(&usuAux, sizeof(stUsuario), 1, archi);
            if(!feof(archi)&&usuAux.eliminado!=1) //Validacion de fin de archivo y usuario no eliminado
            {
                printf("ID: %i\n", usuAux.idUsuario);
                printf("Nombre de usuario: %s\n", usuAux.nombreUsuario);
                desencriptacionPass(usuAux.pass, passAux);
                printf("Password: %s\n", passAux);
                printf("Anio de nacimiento: %i\n", usuAux.anioNacimiento);
                printf("Genero: %c\n", usuAux.genero);
                printf("Pais: %s\n", usuAux.pais);
                printf("Estado en la base: %i\n\n", usuAux.eliminado);
            }
        }

        fclose(archi);

    }

}


void mostrarPeliculas(char archiPeli[]) // Funcion auxiliar usada para chequear que el sistema funcione correctamente visualizando los registros ingresados por pantalla -
{
    stPelicula peliAux;

    FILE * archi;

    archi=fopen(archiPeli, "rb");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo");
    }

    else
    {

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como función devuelve la cantidad de datos leídos)
        {
            fread(&peliAux, sizeof(stPelicula), 1, archi);
            if(!feof(archi)&&peliAux.eliminado!=1)//Validacion de fin de archivo y pelicula no eliminada
            {
                printf("ID: %i\n", peliAux.idPelicula);
                printf("Nombre de peli: %s\n", peliAux.nombrePelicula);
                printf("Anio: %i\n", peliAux.anio);
                printf("Genero: %s\n", peliAux.genero);
                printf("Pais: %s\n", peliAux.pais);
                printf("Director %s\n", peliAux.director);
                printf("Valoracion: %i\n", peliAux.valoracion);
                printf("PM: %i\n", peliAux.pm);
                printf("Estado en la base: %i\n\n", peliAux.eliminado);

            }
        }
        fclose(archi);
    }
}


void mostrarPass(int f,int c,int M[f][c]) //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)
{
    int i, j;

    printf("\n");

    printf("*********\n");

    for (i=0; i<f; i++)
    {
        for (j=0; j<c; j++)
        {
            printf("%i  ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n*********");
}


void mostrarArrayPeliculas(stPelicula array[], int validos)
{
    int i;
    printf("El listado actual de peliculas existentes es el siguiente:\n\n");
    for (i=0; i<validos; i++)
    {
        if(array[i].eliminado!=1)
        {
            printf("ID Pelicula: %i \n", array[i].idPelicula);
            printf("Pelicula: %s \n", array[i].nombrePelicula);
            printf("Director: %s \n", array[i].director);
            printf("Genero: %s \n", array[i].genero);
            printf("Pais: %s \n", array[i].pais);
            printf("Año: %i \n", array[i].anio);
            printf("Valoracion: %i \n", array[i].valoracion);
            printf("Calificacion: %i \n", array[i].pm);
            printf("\n \n");
        }
    }
}



