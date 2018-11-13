#ifndef MENUES_H_INCLUDED
#define MENUES_H_INCLUDED



// FUNCIONES DE SUBMENUES // Menu principal en main
void menuUsuario(char  nombreUsuario[]);
void menuAdmin(char archiUsu[], char archiPeli[]);
void menuAdminPelis(char archiUsu[]);
void menuAdminUsuarios(char archiUsu[]);
void subMenuListados();
void loginUser();
void loguinadm();
int menumodif(char archiusu[]);//Menu para administrador para seleccion de campo a modificar
int menuModifPelis(char archiPeli[]); //Menu para administrador para seleccion de campo a modificar

#endif // MENUES_H_INCLUDED
