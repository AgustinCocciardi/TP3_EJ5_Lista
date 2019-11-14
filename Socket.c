/*
* Javier Abellan, 20 Jun 2000
*
* Funciones de lectura y escritura en sockets
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <Socket.h>

/*
* Lee datos del socket. Supone que se le pasa un buffer con hueco 
*	suficiente para los datos. Devuelve el numero de bytes leidos o
* 0 si se cierra fichero o -1 si hay error.
*/
int Lee_Socket (int fd, t_socket *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/* 
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{
				/*
				* En caso de error, la variable errno nos indica el tipo
				* de error. 
				* El error EINTR se produce si ha habido alguna
				* interrupcion del sistema antes de leer ningun dato. No
				* es un error realmente.
				* El error EGAIN significa que el socket no esta disponible
				* de momento, que lo intentemos dentro de un rato.
				* Ambos errores se tratan con una espera de 100 microsegundos
				* y se vuelve a intentar.
				* El resto de los posibles errores provocan que salgamos de 
				* la funcion con error.
				*/
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}

/*
* Escribe dato en el socket cliente. Devuelve numero de bytes escritos,
* o -1 si hay error.
*/
int Escribe_Socket (int fd, t_socket *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}

void crearLista(t_lista* plista){
	*plista=NULL;
}

int insertar(t_lista* plista, t_dato* dato){
	t_nodo* nuevo= (t_nodo*) malloc(sizeof(t_nodo));
	if(!nuevo)
		return SIN_MEMORIA;
	nuevo->dato=*dato;
	nuevo->siguiente=NULL;
	while (*plista != NULL)
		plista=&(*plista)->siguiente;
	*plista=nuevo;
	return TODO_BIEN;
}

int listaVacia(const t_lista* plista){
	if (*plista == NULL)
		return LISTA_VACIA;
	return LISTA_NO_VACIA;
}

void vaciarLista(t_lista* plista){
	t_nodo* pEliminar= *plista;
	t_nodo* pSiguiente;

	while (pEliminar != NULL)
	{
		pSiguiente = pEliminar->siguiente;
		free(pEliminar);
		pEliminar = pSiguiente;
	}
	
	plista= NULL;
}

void recorrerLista(t_lista* plista){
	t_dato dato;
	while (*plista)
	{
		strcpy(dato.item_id,(*plista)->dato.item_id);
		strcpy(dato.producto,(*plista)->dato.producto);
		strcpy(dato.articulo,(*plista)->dato.articulo);
		strcpy(dato.marca,(*plista)->dato.marca);
		puts("LLEGUE 4");
		printf("Id: %s\tProducto: %s\tArticulo: %s\tMarca: %s\n", dato.item_id, dato.producto, dato.articulo, dato.marca);
		//printf("Id: %s\tProducto: %s\tArticulo: %s\tMarca: %s\n", &(*plista)->dato.item_id, &(*plista)->dato.producto, &(*plista)->dato.articulo, &(*plista)->dato.marca);
		puts("LLEGUE 5");
		plista= &(*plista)->siguiente;
		puts("LLEGUE 6");
	}
}

/*void recorrerLista(t_lista* plista){
	t_dato dato;
	while (*plista)
	{
		dato = &(*plista)->dato;
		puts("LLEGUE4");
		printf("Id: %s\tProducto: %s\tArticulo: %s\tMarca: %s\n", dato.item_id, dato.producto, dato.articulo, dato.marca);
		puts("LLEGUE5");
		plista= &(*plista)->siguiente;
		puts("LLEGUE6");
	}
}*/