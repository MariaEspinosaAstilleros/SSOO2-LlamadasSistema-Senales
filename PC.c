/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PC.c
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Calcula la nota que deben obtener en la nueva prueba para que la media alcance la nota de corte 
 * 
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "lecturaFichero.h"

#define NOTA "NotaNuevaPrueba.txt"

int calculoNotaNueva(int n); 

int main(int argc, char *argv[]){

    Alumno lista[NUM_ALUMNO]; 
    FILE *fp; 
    int nota_nueva; 
    float suma_notas; 
    char nota_media[50];
    char *direc;
    char *cadena; 

    leerFichero(lista); 

    printf("[PC] Fichero leído correctamente\n"); 

    direc = malloc(sizeof(DIRECTORIO) + sizeof(char[9]) + sizeof(NOTA)); 
    cadena = malloc(sizeof("La nota que debes obtener en este nuevo examen para superar la prueba es ") + sizeof(int) + sizeof(char)*3);

    /*Calculamos la nueva nota para cada uno de los alumnos*/

    for(int i = 0; i < NUM_ALUMNO; i++){

        nota_nueva = calculoNotaNueva(lista[i].nota); 
        sprintf(direc, "%s%s/%s", DIRECTORIO, lista[i].dni, NOTA); 

        /*Comprobamos que hemos abierto correctamente el fichero para escribir en él*/

        if((fp = fopen(direc, "w")) == NULL){
            fprintf(stderr, "[PC] Error al abrir el fichero para realizar la escritura\n"); 
            exit(EXIT_FAILURE); 
        }

        sprintf(cadena, "%s %d.\n", "La nota que debes obtener en este nuevo examen para superar la prueba es", nota_nueva); 

        /*Comprobamos que hemos escrito la nota nueva correctamente en el fichero*/

        if(fputs(cadena, fp) == EOF){
            fprintf(stderr, "[PC] Error en la escritura del archivo\n"); 
            exit(EXIT_FAILURE); 
        }

        fclose(fp); 
        suma_notas = suma_notas + lista[i].nota; 
    }

    sprintf(nota_media, "%.2f", (suma_notas / NUM_ALUMNO)) ; 

    /*Escribimos la nota media en la tubería para comunicarsela al manager.c*/

    if(write(atoi(argv[1]), nota_media, sizeof(nota_media)) != sizeof(nota_media)){ 
        fprintf(stderr, "[PC] Error al escribir la nota media en la tubería\n"); 
        exit(EXIT_FAILURE); 
    }

    printf("[PC] Nota media calculada correctamente\n"); 
    printf("[PC] Finalizado\n"); 

    return EXIT_SUCCESS; 
}

int calculoNotaNueva(int n){

    int nota_nueva = 10 - n; /*n es la nota sacada en el anterior examen*/

    return nota_nueva; 
}
