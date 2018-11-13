#include "libreria.h"

//nodoArbolPelicula*PasaPeliculasDeArchivoToArbol()
//{
//    FILE*archi;
//    stPelicula Aux;
//    nodoArbolPelicula*Arbol=inicArbol();
//    archi=fopen(ARCHIPELI,"rb");
//    if(archi!=NULL)
//    {
//        fseek(archi,0,SEEK_SET);
//        while(fread(&Aux,sizeof(stPelicula),1,archi)>0)
//        {
//
//
//                Arbol=insertaNodoArbol(Arbol,Aux);
//
//
//        }
//
//
//    }
//    else
//    {
//        printf("\nError de apertura.");
//    }
//
//    fclose(archi);
//    return Arbol;
//
//}

nodoArbolPelicula*PasaPeliculasDeArchivoToArbol(nodoArbolPelicula*ArbolPelis)/// Funcion que levanta registros de peliculas y los carga en el arbol
{

    int validosPelisActivas=0;
    int validosPelis=CantidadPelisActivas();///se cuenta la cantidad de registros
    stPelicula ArregloAux[validosPelis];///se crea un arreglo de la dimension del total de peliculas
    validosPelisActivas=cargarArregloPeliculasActivas(ArregloAux, validosPelis);///se carga el arreglo con los registros
    ArbolPelis=balanceoArbol(ArregloAux, 0, validosPelisActivas-1);///se pasan las peliculas desde el arreglo al arbol de manera balanceada
    return ArbolPelis;

}

nodoArbolPelicula*balanceoArbol(stPelicula arregloDePelis[], int primero, int ultimo)///funcion de balanceo del arbol a partir de un arreglo de peliculas
{

    int medio;

    nodoArbolPelicula* aux;

    if (primero > ultimo)

        return NULL;

    medio = (primero + ultimo) / 2; ///genera la raiz a partir de la mitad del archivo para a partir de aqui recursivamente cargar ambos lados del arbol

    aux = crearNodoArbol(arregloDePelis[medio]);

    aux->izq = balanceoArbol(arregloDePelis, primero, medio - 1);

    aux->der = balanceoArbol(arregloDePelis, medio + 1, ultimo);

    return aux;
}

int CantidadPelisActivas()
{

    int cantidad=0;
    FILE*archi=fopen(ARCHIPELI,"rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantidad=ftell(archi)/sizeof(stPelicula);
    }
    else
    {
        printf("\n Error de apertura en archivo de peliculas.");
    }
    fclose(archi);
    return cantidad;

}

//***** TDA LISTAS ******

nodoListaPelicula* inicLista()
{
    return NULL;
}


nodoListaPelicula* crearNodoPeli(stPelicula Peli)
{

    nodoListaPelicula* aux=(nodoListaPelicula*)malloc(sizeof(nodoListaPelicula));
    aux->p=Peli;
    aux->sig=NULL;
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


void imprimirNodoPelis(stPelicula p) /// SE PASA LA ESTRUCTURA A IMPRIMIR DIRECTAMENTE EN LUGAR DE PASAR EL NODO QUE LA CONTIENE
{
    puts("\n\n\t***** PELICULA *****");
    printf("\n\tID PELICULA: %i", p.idPelicula);
    printf("\n\tNOMBRE: %s", p.nombrePelicula);
    printf("\n\tDIRECTOR: %s", p.director);
    printf("\n\tGENERO: %s", p.genero);
    printf("\n\tPAIS: %s", p.pais);
    printf("\n\tANIO: %i", p.anio);
    printf("\n\tVALORACION: %i", p.valoracion);
    printf("\n\tPM: %i\n", p.pm);
    Sleep(150);

}


void mostrarNodoPelis(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg)
        if(seg->p.eliminado==0) // MUESTRA SOLO PELIS ACTIVAS
        {
            imprimirNodoPelis(seg->p);
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

nodoListaPelicula* borrarLista(nodoListaPelicula* listaPelis)
{
    nodoListaPelicula*auxPeli;

    while(listaPelis)
    {
        auxPeli=listaPelis;
        listaPelis=listaPelis->sig;
        free(auxPeli);
    }

    return listaPelis;
}

////***********************************************************************************************************************************//
////                                                        TDA Arboles
////***********************************************************************************************************************************//


nodoArbolPelicula * inicArbol()
{
    return NULL;
}

nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula)
{

    nodoArbolPelicula*Aux = (nodoArbolPelicula*)malloc(sizeof(nodoArbolPelicula));
    Aux->p=Pelicula;
    Aux->der=NULL;
    Aux->izq=NULL;
    return Aux;
}

nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol, stPelicula Pelicula)
{


    if (Arbol==NULL)
    {
        Arbol=crearNodoArbol(Pelicula);
        printf("\n Pelicula agregada correctamente al Arbol \n");
        system("pause");
    }
    else
    {
        if(Pelicula.idPelicula>Arbol->p.idPelicula)
        {
            Arbol->der=insertaNodoArbol(Arbol->der,Pelicula);
        }
        else
        {
            Arbol->izq=insertaNodoArbol(Arbol->izq,Pelicula);
        }
    }
    return Arbol;

}

nodoArbolPelicula*modificarPeliEnArbol(nodoArbolPelicula*ArbolPelis,stPelicula auxPeli)///Funcion que modifica la pelicula en el arbol
{
//    nodoArbolPelicula* nodoAux = (nodoArbolPelicula*)malloc(sizeof(nodoArbolPelicula));
    if(ArbolPelis)
    {
        if(auxPeli.idPelicula==ArbolPelis->p.idPelicula)
        {
            ArbolPelis->p=auxPeli;
        }
        else
        {
            if(ArbolPelis->p.idPelicula<auxPeli.idPelicula)
            {
                ArbolPelis->der=modificarPeliEnArbol(ArbolPelis->der,auxPeli);
            }
            else
            {
                ArbolPelis->izq=modificarPeliEnArbol(ArbolPelis->izq,auxPeli);
            }
        }
    }

    return ArbolPelis;
}

void preOrder(nodoArbolPelicula*Arbol)
{
    if(Arbol!=NULL)
    {
        printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
        printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
        printf("\n---------------Anio: |%d|",Arbol->p.anio);
        printf("\n-------------Genero: |%s|",Arbol->p.genero);
        printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
        printf("\n----Para mayores de: |%d|",Arbol->p.pm);
        printf("\n-----------Director: |%s|",Arbol->p.director);
        printf("\n---------------Pais: |%s|",Arbol->p.pais);
        puts("\n");
        Sleep(300);
        preOrder(Arbol->izq);
        preOrder(Arbol->der);
    }
}

void inOrder(nodoArbolPelicula*Arbol)
{

    if(Arbol!=NULL)
    {
        inOrder(Arbol->izq);
        printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
        printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
        printf("\n---------------Anio: |%d|",Arbol->p.anio);
        printf("\n-------------Genero: |%s|",Arbol->p.genero);
        printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
        printf("\n----Para mayores de: |%d|",Arbol->p.pm);
        printf("\n-----------Director: |%s|",Arbol->p.director);
        printf("\n---------------Pais: |%s|",Arbol->p.pais);
        puts("\n");
        Sleep(300);
        inOrder(Arbol->der);
    }

}

void postOrder(nodoArbolPelicula*Arbol)
{

    if(Arbol!=NULL)
    {
        postOrder(Arbol->izq);
        postOrder(Arbol->der);
        printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
        printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
        printf("\n---------------Anio: |%d|",Arbol->p.anio);
        printf("\n-------------Genero: |%s|",Arbol->p.genero);
        printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
        printf("\n----Para mayores de: |%d|",Arbol->p.pm);
        printf("\n-----------Director: |%s|",Arbol->p.director);
        printf("\n---------------Pais: |%s|",Arbol->p.pais);
        puts("\n");
        Sleep(300);
    }

}

stPelicula buscarPeliculaID(nodoArbolPelicula*Arbol, int id)
{

    stPelicula rta;
    if(Arbol)
    {
        if(id==Arbol->p.idPelicula)
        {
            rta=Arbol->p;
        }
        else
        {
            if(Arbol->p.idPelicula<id)
            {
                rta=buscarPeliculaID(Arbol->der,id);
            }
            else
            {
                rta=buscarPeliculaID(Arbol->izq,id);
            }
        }
    }

    return rta;
}

nodoArbolPelicula*nodoMasDer(nodoArbolPelicula*ArbolPelis)
{

    if (ArbolPelis->der)
    {
        ArbolPelis=nodoMasDer(ArbolPelis->der);
    }
    return ArbolPelis;
}

nodoArbolPelicula*nodoMasIzq(nodoArbolPelicula*ArbolPelis)
{

    if (ArbolPelis->izq)
    {
        ArbolPelis=nodoMasIzq(ArbolPelis->izq);
    }
    return ArbolPelis;
}


nodoArbolPelicula*borrarNodoArbol(nodoArbolPelicula*ArbolPelis, int idPeli)
{

    if(ArbolPelis)
    {
        if(idPeli==ArbolPelis->p.idPelicula)
        {
            if(ArbolPelis->izq)
            {
                nodoArbolPelicula *auxDer=nodoMasDer(ArbolPelis->izq);
                ArbolPelis->p = auxDer->p;
                ArbolPelis->izq=borrarNodoArbol(ArbolPelis->izq, auxDer->p.idPelicula);
            }
            else if(ArbolPelis->der)
            {
                nodoArbolPelicula *auxIzq=nodoMasIzq(ArbolPelis->der);
                ArbolPelis->p=auxIzq->p;
                ArbolPelis->der=borrarNodoArbol(ArbolPelis->der, auxIzq->p.idPelicula);
            }
            else
            {
                free(ArbolPelis);
                ArbolPelis=NULL;
            }
        }
        else if(idPeli>ArbolPelis->p.idPelicula)
        {
            ArbolPelis->der=borrarNodoArbol(ArbolPelis->der, idPeli);
        }
        else
        {
            ArbolPelis->izq=borrarNodoArbol(ArbolPelis->izq, idPeli);
        }
    }
    else
    {
        printf("\nLa pelicula buscada no se encuentra en el arbol");
    }

    return ArbolPelis;
}


nodoArbolPelicula*borrarArbol(nodoArbolPelicula*ArbolPelis)
{

    if(ArbolPelis)
    {
        ArbolPelis->izq=borrarArbol(ArbolPelis->izq);
        ArbolPelis->der=borrarArbol(ArbolPelis->der);
        ArbolPelis=borrarNodoArbol(ArbolPelis,ArbolPelis->p.idPelicula);

    }

    return ArbolPelis;
}

//
//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA PELICULAS
//***********************************************************************************************************************************//

nodoArbolPelicula*altaPelicula(nodoArbolPelicula*ArbolPelis) // Funcion general de alta de pel\EDculas
{
    // Declaracion de variables locales
    int validacionPais=0;
    int validacionDirector=0;
    int validacionGenero=0;
    int peliculaExiste=0;
//    int cantReg=0;
    int i=0;
    char control='s'; // Variable de control para ciclo while principal de solicitud de los datos de peliculas
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal

    FILE *archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(ARCHIPELI, "ab"); //Se chequea el acceso al archivo bajo la modalidad lectura-escritura

    if(archi==NULL) // Chequea si se puede abrir el archivo usando s\F3lo lectura
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
            peliculaExiste=validarPeliExiste(peliAux.nombrePelicula); // Chequea que el nombre de la pelicula en cuesti\F3n no exista en el archivo para evitar que se duplique mediante un flag

            if(peliculaExiste)
            {
                printf("Ya existe una pelicula con ese nombre, desea continuar intentandolo(s/n)?\n");
                fflush(stdin);
                scanf("%c", &control);
                if(control=='s')
                {
                    while((peliculaExiste) && (i<3))
                    {
                        printf("Ingrese el nombre de la pelicula nuevamente: ");
                        fflush(stdin);
                        gets(peliAux.nombrePelicula);
                        peliculaExiste=validarPeliExiste(peliAux.nombrePelicula); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
                        i++;
                    }
                    if(peliculaExiste)
                    {
                        printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                        exit(1);
                    }
                    else
                    {
                        printf("El ingreso ha sido exitoso\n");
                    }
                }
                else
                {
                    exit(1);
                }
            }

            do
            {
                printf("Ingrese el nombre del director de la pelicula(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.director);
                validacionDirector=validarTipoChar(peliAux.director);
            }
            while(!validacionDirector);

            do
            {
                printf("Ingrese el genero(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.genero);
                validacionGenero=validarTipoChar(peliAux.genero);
            }
            while(!validacionGenero);

            do
            {
                printf("Ingrese el pais(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.pais);
                validacionPais=validarTipoChar(peliAux.pais);
            }
            while(!validacionPais);

            do
            {
                printf("Ingrese el anio: ");
                fflush(stdin);
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
                fflush(stdin);
                scanf("%i", &peliAux.pm);
            }
            while((peliAux.pm<0) || (peliAux.pm>18));

            peliAux.idPelicula=CantidadPelisActivas()+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
            peliAux.eliminado=0; // Se asigna negativo como valor predeterminado

            fwrite(&peliAux, sizeof(peliAux), 1, archi); // Se graba los datos capturados en el archivo

            ArbolPelis=insertaNodoArbol(ArbolPelis, peliAux); //Se agrega peli al arbol

            printf("Desea continuar ingresando peliculas(s/n?)"); // Se consulta si se desea continuar ingresando usuarios en esta sesi\F3n
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

    return ArbolPelis;
}


nodoArbolPelicula* bajaPelicula(nodoArbolPelicula*ArbolPelis)//Elimina peliculas pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idPeli=0;

    stPelicula peliAux;

    FILE *archi;

    archi=fopen(ARCHIPELI, "r+b");

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
        fflush(stdin);
        scanf("%i", &idPeli);
        printf("\nEsta seguro de que desea eliminar la pelicula(s/n?"); // Chequea nuevamente si quiere avanzar con la baja de la pelicula
        fflush(stdin);
        scanf("%c", &control);
        if(control=='s') // Si confirma, se avanza
        {
            fseek(archi, (idPeli)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all\ED
            fread(&peliAux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado
            peliAux.eliminado=1; // Se cambia el estado de la pelicula a eliminada
            fseek(archi, -1*sizeof(stPelicula), SEEK_CUR); // Se lleva el cursor al principio del archivo para moverse desde all\ED
            fwrite(&peliAux, sizeof(peliAux), 1, archi); // Escribo el nuevo valor de eliminado en el archivo
            printf("\nLa pelicula se elimino correctamente\n");
            printf("\nNombre de la pelicula: %s", peliAux.nombrePelicula);
            printf("\nEstado: %i", peliAux.eliminado);
            ArbolPelis=borrarNodoArbol(ArbolPelis, peliAux.idPelicula);
        }
        else // Si no confirma, se sale del programa
        {
            exit(1);
        }
        fclose(archi);
    }

    return ArbolPelis;
}

nodoArbolPelicula* mostrarPeliParaModif(nodoArbolPelicula*ArbolPelis)//Modificacion de peliculas para administrador
{
    FILE *archi = fopen(ARCHIPELI,"rb+");
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
        fflush(stdin);
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

            fseek(archi, (id)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all\ED
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
                a=menuModifPelis(ArbolPelis);



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
                    fflush(stdin);
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
                    fflush(stdin);
                    scanf("%i", &aux.valoracion);

                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 7:

                    printf("Ingrese la nueva clasificacion de la pelicula(0 si es ATP - 13 si es para mayores de 13 anios - 16 y 18 respectivamente: \n");
                    fflush(stdin);
                    scanf("%i", &aux.pm);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 8:

                    printf("Ingrese el nuevo estado en catalogo de la pelicula(0 si activa - 1 si eliminada): \n");
                    fflush(stdin);
                    scanf("%i", &aux.eliminado);
                    if(aux.eliminado==0)
                        ArbolPelis=insertaNodoArbol(ArbolPelis, aux);
                    else
                        ArbolPelis=borrarNodoArbol(ArbolPelis, aux.idPelicula);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                default:
                    exit(1);
                    break;

                }
                fseek(archi, (-1)*sizeof(stPelicula), SEEK_CUR); // Se lleva el cursor al principio del archivo para moverse desde all\ED
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado
                if(!aux.eliminado)
                    ArbolPelis=modificarPeliEnArbol(ArbolPelis,aux);
            }
            while(a!=0 && control=='s'); // Mientras se desee continuar
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

    return ArbolPelis;
}

void consultaPeliAdmin()//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(ARCHIPELI,"rb");



    int validos=0, id=0, i = 0, flag=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea consultar: \n");
        fflush(stdin);
        scanf("%i", &id);
        validos=CantidadPelisActivas();
        stPelicula arregloPelis[validos];
        cargarArregloPeliculas(arregloPelis, validos);//se carga el array de usuarios y devuelve los validos

        for (i=0; i<validos; i++)
        {
            if(id==arregloPelis[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("Pelicula: %s \n", arregloPelis[i].nombrePelicula);
                printf("Director: %s \n", arregloPelis[i].director);
                printf("Genero: %s \n", arregloPelis[i].genero);
                printf("Pais: %s \n", arregloPelis[i].pais);
                printf("Anio: %i \n", arregloPelis[i].anio);
                printf("Valoracion: %i \n", arregloPelis[i].valoracion);
                printf("Calificacion: %i \n", arregloPelis[i].pm);
                if(arregloPelis[i].eliminado==1)
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



int cargarArregloPeliculasActivas(stPelicula arregloPelis[], int validosPelis)
{
    FILE *archi;

    archi=fopen(ARCHIPELI, "rb");

    stPelicula peli;

    int i=0;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        while(fread(&peli, sizeof(stPelicula), 1, archi)>0)
        {
            if(!peli.eliminado)
            {
                arregloPelis[i]=peli;
                i++;
            }

        }
        fclose(archi);
    }

    return i;
}

void cargarArregloPeliculas(stPelicula arregloPelis[], int validosPelis)
{
    FILE *archi;

    archi=fopen(ARCHIPELI, "rb");

    stPelicula peli;

    int i;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        for(i=0; fread(&peli, sizeof(stPelicula), 1, archi)>0 && !peli.eliminado && i<validosPelis ; i++)
        {
            arregloPelis[i]=peli;
        }
        fclose(archi);
    }


}

void insertar(stPelicula arregloPelis[], int posicion)
{
    stPelicula auxPeli=arregloPelis[posicion];
    int j=posicion-1;
    while(j>=0 && strcmpi(arregloPelis[j].genero,auxPeli.genero)<0)
    {
        arregloPelis[j+1]=arregloPelis[j];
        j--;
    }
    arregloPelis[j+1]=auxPeli;
}

void ordenarGenero ()
{

    int validosPelis=CantidadPelisActivas();
    int i=0;
    stPelicula arregloPelis[validosPelis];
    cargarArregloPeliculas(arregloPelis, validosPelis);//se carga el array de peliculas
    for(i=1; i<validosPelis; i++) //se recorre el array comparando los generos de las peliculas y ordenando de mayor a menor
    {
        insertar(arregloPelis,i);
    }

    mostrarArregloPelis(arregloPelis, validosPelis);//se muestra el array por pantalla

    system("pause");

}


void ordenarTitulo()
{

    int validosPelis=CantidadPelisActivas();
    stPelicula arregloPelis[validosPelis];
    cargarArregloPeliculas(arregloPelis, validosPelis);//se carga el array de peliculas y se verifican los validos
    ordenacionSeleccion(arregloPelis,validosPelis);//se ordenan por el metodo de ordenacion por seleccion
    mostrarArregloPelis(arregloPelis, validosPelis); //se muestran por pantalla
    system("pause");
}

void ordenacionSeleccion(stPelicula arregloPelis[], int validosPelis)
{
    int posmenor;
    stPelicula aux;
    int i = 0;
    while (i<validosPelis-1)
    {
        posmenor=posicionMenor(arregloPelis,i,validosPelis);
        aux = arregloPelis[posmenor];
        arregloPelis[posmenor]= arregloPelis[i];
        arregloPelis[i]=aux;
        i++;
    }
}

int posicionMenor(stPelicula arregloPelis[], int pos, int validosPelis)
{
    char menor[30];
    strcpy(menor,arregloPelis[pos].nombrePelicula);
    int posmenor=pos;
    int i=pos+1;
    while (i<validosPelis)
    {
        if (strcmpi(menor,arregloPelis[i].nombrePelicula)> 0)
        {
            strcpy(menor, arregloPelis[i].nombrePelicula);
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}

int validarPeliExiste(char nombrePelicula[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(ARCHIPELI, "rb"); // Abre al archivo en modo solo lectura para chequear acceso

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
        fclose(archi); // Cierra el archivo
    }


    return flag; // Devuelve el valor de flag para su proceso en la funci\F3n que la invoca
}

void verPelicula(char nombreUsuario[], stCelda*arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis)
{
    char control='s';
    do
    {
        int id=0;
        printf("\n\tIngrese el ID de la pelicula que desea ver: ");
        fflush(stdin);
        scanf("%i", &id);
        stPelicula auxPeli=buscarPeliculaID(ArbolPelis, id);
        if(auxPeli.idPelicula==id)
        {
            printf("\n\tDisfrute de : \n\n");
            printf("\tPelicula: %s \n", auxPeli.nombrePelicula);
            printf("\tDel Director: %s \n", auxPeli.director);
            printf("\n \n");
            nodoListaPelicula*NodoAux=crearNodoPeli(auxPeli);
            cargarPeliAUser(arregloUsuActivos, validos, nombreUsuario, NodoAux);
            printf("\tDesea buscar otra(s/n)?: ");
            fflush(stdin);
            scanf("%c", &control);

        }

        else //En caso de no encontrar el id
        {
            printf("No se encuentra la pelicula desea buscar otra? \n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while(control=='s');
}

void cargarPeliAUser(stCelda*arregloUsuActivos,int validos, char nombreUsuario[], nodoListaPelicula* Peli)
{
    int posicion=buscarPosicionUsuario(nombreUsuario, arregloUsuActivos, validos);
    arregloUsuActivos[posicion].listaPelis=agregarNodoPpio(arregloUsuActivos[posicion].listaPelis, Peli);
}

//int validarPeliExiste(char nombrePeli[]) // Valida si el nombre de la pelicula ingresada actualmente ya existe en el archivo
//{
//    int flag=buscarPelixNombre(nombrePeli);
//    return flag; // Devuelve el valor de flag para su proceso en la funci\F3n que la invoca
//}

int buscarPelixNombre(nodoArbolPelicula* ArbolPelis,char PeliBuscada[])
{
    int flag=0;
    if(ArbolPelis!=NULL)
    {
        if(strcmp(ArbolPelis->p.nombrePelicula,PeliBuscada)==0)///Si encuentra la pelicula se corta la ejecucion de la funcion
        {
            flag=1;
        }
        else
        {
            flag=buscarPelixNombre(ArbolPelis->der,PeliBuscada);
            flag=buscarPelixNombre(ArbolPelis->izq,PeliBuscada);
        }
    }

    return flag;
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

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como funci\F3n devuelve la cantidad de datos le\EDdos)
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

//void modificarPeliEnArbol(nodoArbolPelicula * ArbolPelis,stPelicula PeliculaToModificar)
//{
//    nodoArbolPelicula * NodoAux=crearNodoArbol(buscarPeliculaID(ArbolPelis, PeliculaToModificar.idPelicula));
//    NodoAux->p=PeliculaToModificar;
//}

void mostrarListaPelis(nodoListaPelicula * lista, char nombreUsuario[])
{

    nodoListaPelicula*aux=lista;

    if(aux)
    {
        printf("\n\tEstas son las peliculas vistas por '%s':\n\n", nombreUsuario);
        Sleep(500);
        while(aux)
        {
            printf("\tID Pelicula: %i \n", aux->p.idPelicula);
            printf("\tPelicula: %s \n", aux->p.nombrePelicula);
            printf("\tDirector: %s \n", aux->p.director);
            printf("\tGenero: %s \n", aux->p.genero);
            printf("\tPais: %s \n", aux->p.pais);
            printf("\tAnio: %i \n", aux->p.anio);
            printf("\tValoracion: %i \n", aux->p.valoracion);
            printf("\tCalificacion: %i \n", aux->p.pm);
            printf("\n \n");
            aux=aux->sig;
            Sleep(500);
        }
    }
    else
        printf("'%s' no ha visto ninguna pelicula todavia\n\n", nombreUsuario);

}

void mostrarArregloPelis(stPelicula array[], int validos)
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
            printf("Anio: %i \n", array[i].anio);
            printf("Valoracion: %i \n", array[i].valoracion);
            printf("Calificacion: %i \n", array[i].pm);
            printf("\n \n");
            Sleep(300);
        }
    }
}
