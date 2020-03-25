/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PA.c
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Creación de directorios por cada uno de los estudiantes que se obtienen al leer el fichero estudiantes_p1.txt
 * 
 ******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "lecturaFichero.h" 

int main(int argc, char *argv[]){
   
   Alumno lista[NUM_ALUMNO]; 
   char *direc; 
   
   leerFichero(lista); 
   printf("[PA] Fichero leído correctamente\n"); 

   direc = malloc(sizeof(DIRECTORIO) + sizeof(char[9])); //para ver cuantos bytes le damos a nuestro directorio 

    /*Creamos el directorio para cada uno de los alumnos*/
    for(int i = 0; i < NUM_ALUMNO; i++){
	    sprintf(direc, "%s%s", DIRECTORIO, lista[i].dni);
		mkdir(direc, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

    printf("[PA] Directorios creados correctamente\n"); 
    printf("[PA] Finalizado\n"); 
  
    return EXIT_SUCCESS; 
}
