#include <Socket_Cliente.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

void main (int argc, char* argv[])
{
	int sock;		/* descriptor de conexión con el servidor */
	int error;		/* error de lectura por el socket */

    t_socket estructura;
    
    t_lista lista= NULL;

	char *ayuda="-Help"; //Uso esta cadena para ver si el usuario quiere ver la ayuda
    if (argc == 2 && strcmp(argv[1],ayuda) == 0) //Muestro la ayuda al usuario
    {
        puts("Este es el proceso consumidor para consultar al archivo Servidor");
        puts("Usted no deberá pasarle ningún parámetro a este programa, solamente deberá llamarlo escribiendo: ./Cliente");
        puts("Posteriormente, usted podrá ingresar por teclado tantas consultas como desee hacerle al Servidor, usando el formato CAMPO=VALOR");
        puts("Ejemplos de ejecución:");
        puts("\tID=4444");
        puts("\tMARCA=GEORGALOS");
        puts("\tPRODUCTO=HELADO");
        puts("Cuando ya no desee hacer mas consultas, bastará con que escriba QUIT y su programa se cerrará");
        exit(3);
    }

    if (argc != 1)
    {
        printf("\nExceso de parámetros");
        printf("\nEscriba './Cliente -Help' (sin las comillas) para recibir ayuda");
        printf("\n");
        exit(1);
	}

	/* Se abre una conexión con el servidor */
	sock = Abre_Conexion_Inet ("localhost", "cpp_java");

	char consulta[100];
    char *campo;
    char *valor;
    char delimitador[2]="=";
    puts("Ingrese su consulta");
    fflush(stdin);
    scanf("%s", consulta);
    while (strcmp(consulta,"QUIT") != 0)
    {
        campo=strtok(consulta,delimitador);
        valor=strtok(NULL,delimitador);
        for (int i = 0; i < strlen(valor); i++)
        {
            if (valor[i] == '.')
            {
                valor[i]= ' ';
            }
        }
		printf("Consulta Ingresada: %s-%s\n", campo, valor);
		strcpy(estructura.campo,campo);
		strcpy(estructura.valor,valor);
		
		Escribe_Socket(sock,&estructura,sizeof(t_socket));
		if ((Lee_Socket (sock, &estructura, sizeof(t_socket)) > 0)){
            lista=estructura.lista;
			if (listaVacia(&lista) == 0)
			{
                recorrerLista(&lista);
                puts("LLEGUE 7");
			}
			else
			{
				puts("Su busqueda no produjo coincidencias\n");
			}
        }
        vaciarLista(&lista);
		puts("Ingrese su consulta");
    	fflush(stdin);
    	scanf("%s", consulta);
	}
}