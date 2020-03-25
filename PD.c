/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PD.c
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Elimina todos los directorios y archivos asociados a los estudiantes 
 * 
 ******************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char command[50]; 

    strcpy(command, "rm -r Estudiantes/");
    system(command); 

    printf("[PD] Directorio y archivos borrados correctamente\n"); 

    printf("[PD] Finalizado\n"); 

    return EXIT_SUCCESS; 
}
