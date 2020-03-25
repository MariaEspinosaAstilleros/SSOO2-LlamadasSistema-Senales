/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PB.c
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Copia en cada directorio del estudiante el modelo de examen que le corresponda. 
 * 
 ******************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <signal.h> 
#include "lecturaFichero.h" 

#define MODELO_EXAMEN "MODELOSEXAMEN/"
#define MODELO "MODELO"
#define PERMISOS 0644
#define TAMBUFFER 255

int copiarFicheros(Alumno al); 

int main(int argc, char *argv[]){

    Alumno lista[NUM_ALUMNO]; 

    leerFichero(lista); 

    printf("[PB] Fichero leído correctamente\n"); 

    /*Copiamos los modelos de examen que le corresponden a cada alumno*/
    
    for(int i=0; i < NUM_ALUMNO; i++){
        copiarFicheros(lista[i]);
    }

    printf("[PB] Copia terminada correctamente\n"); 
    printf("[PB] Finalizado\n"); 

    return EXIT_SUCCESS; 
}

int copiarFicheros(Alumno al){

    int fichero_creado, fichero_destino, num_caracteres; 
    char buffer[TAMBUFFER]; 
    char *source; //modelos de examen que queremos copiar
    char *destination; //directorio destino donde queremos copiar los modelos

    /*Calculamos el tamaño de origen y destino que necesitamos para la copia de directorios*/

    source = malloc(sizeof(MODELO_EXAMEN) + sizeof(MODELO) + sizeof(char) + sizeof(".pdf"));
    sprintf(source, "%s%s%c%s", MODELO_EXAMEN, MODELO, al.modo_examen, ".pdf");

    destination = malloc(sizeof(DIRECTORIO) + sizeof(char[9]) + sizeof(MODELO) + sizeof(char) + sizeof(".pdf")); 
    sprintf(destination, "%s%s/%s%c%s", DIRECTORIO, al.dni, MODELO, al.modo_examen, ".pdf"); 

    /*Comprobamos que podemos abrir el fichero que queremos copiar*/

    if((fichero_creado = open(source, O_RDONLY)) == -1){
        fprintf(stderr, "[PB] Error al abrir el fichero fuente\n");
        exit(EXIT_FAILURE); 
    }

    /*Comprobamos que se ha creado correctamente el fichero destino*/

    if((fichero_destino = creat(destination, PERMISOS)) == -1){
        fprintf(stderr, "[PB] Error en la creación del fichero destino\n"); 
        exit(EXIT_FAILURE); 
    }

    /*Comprobamos que escribimos los ficheros existentes en los ficheros que hemos marcado como destino correctamente*/

    while((num_caracteres = read(fichero_creado, buffer, TAMBUFFER)) > 0){

        if(num_caracteres == -1){
            fprintf(stderr, "[PB] Error al escribir en el fichero de destino\n"); 
            exit(EXIT_FAILURE); 

        }else if((write(fichero_destino, buffer, num_caracteres)) != num_caracteres){
            fprintf(stderr, "[PB] Error al escribir en el fichero de destino\n");
            exit(EXIT_FAILURE); 
        }
    }

    /*Comprobamos que cerramos tanto los ficheros origen como los destino correctamente*/
    
    if(close(fichero_creado) == -1 || close(fichero_destino) == -1){
        fprintf(stderr, "[PB] Error al cerrar los ficheros\n");
        exit(EXIT_FAILURE); 
    }

    return EXIT_SUCCESS; 
}
