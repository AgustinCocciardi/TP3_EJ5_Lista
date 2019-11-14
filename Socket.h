#ifndef _SOCKET_H
#define _SOCKET_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define VALOR 100
#define SIN_MEMORIA 0
#define TODO_BIEN 1
#define LISTA_VACIA 1
#define LISTA_NO_VACIA 0

typedef struct dato
{
    char item_id[10];
    char articulo[60];
    char producto[60];
    char marca[40];
} t_dato;

typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo* siguiente;
} t_nodo;

typedef t_nodo* t_lista;

typedef struct socket
{
    char campo[9];
    char valor[60];
    t_lista* lista;
} t_socket;

int Lee_Socket (int fd, t_socket *Datos, int Longitud);
int Escribe_Socket (int fd, t_socket *Datos, int Longitud);

void crearLista(t_lista* plista);
int insertar(t_lista* plista, t_dato* dato);
int listaVacia(const t_lista* plista);
void vaciarLista(t_lista* plista);
void recorrerLista(t_lista* plista);

#endif
