/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    lecturaFichero.h
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Lectura del fichero estudiantes_p1.text 
 * 
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "estudiantes_p1.text"
#define NUM_ALUMNO 15 
#define DIRECTORIO "Estudiantes/"

typedef struct{
	char dni[9];
	char modo_examen;
	int nota;
} Alumno;

//int leerFichero(Alumno lista[NUM_ALUMNO]); 

int leerFichero(Alumno lista[NUM_ALUMNO]){

    FILE *fp;
    Alumno al; 
    char *frase;
    char cadena[20];  
    int contador = 0; //para ver en que columna del fichero me encuentro 
    int alumno = 0; 

    if((fp = fopen(ARCHIVO, "r")) == NULL){
        fprintf(stderr, "[LECTURA] Error al abrir el fichero\n"); 
        return EXIT_FAILURE; 
    }

    printf("[LECTURA] Archivo abierto correctamente\n"); 

    fgets(cadena, 20, fp);

    while(!feof(fp)){ //mientras que no sea final de archivo
        frase = strtok(cadena, " "); 
        while(frase != NULL){
            if(contador == 0){ //estamos en la primera columna del fichero 
                strcpy(al.dni, frase); 

            }else if(contador == 1){//estamos en la segunda columna del fichero 
                al.modo_examen = frase[0]; 

            }else if(contador == 2){//estamos en la tercera columna del fichero
                al.nota = atoi(frase); 
            }

            contador++; 
            frase = strtok(NULL, " "); 
        }

        lista[alumno] = al;  
        contador = 0;
        alumno++;  

        fgets(cadena, 20, fp); 
    }

    fclose(fp); 

    printf("[LECTURA] Lectura completada correctamente.\n"); 

    return EXIT_SUCCESS;
} 
