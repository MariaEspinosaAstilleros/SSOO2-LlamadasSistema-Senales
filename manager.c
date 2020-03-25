/******************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    manager.c
 * 
 * Author:          María Espinosa Astilleros
 * 
 * Date created:    19/2/2019
 * 
 * Purpose:         Creación de los procesos PA, PB y PC, registra la finalización de cada tarea, la nota media de los estudiantes en la primera prueba y crea el archivo log.txt
 * 
 ******************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <signal.h> 
#include "lecturaFichero.h"

#define LECTURA 0
#define ESCRITURA 1
#define FICHERO_LOG "log.txt"

pid_t g_pids[3]; /*3 porque vamos a crear los procesos a, b y c*/
FILE *g_fp; 

void manejador(int signum);

int main(int argc, char * argv[]){

    int a_status, b_status, c_status; 
    int fd[2]; 
    char buffer[50]; 
    char wr_tub[256];

    g_fp = fopen(FICHERO_LOG, "w"); 
    fprintf(g_fp, "********Log del sistema********\n"); 

    signal(SIGINT, manejador); 
    mkdir(DIRECTORIO, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    /*Creamos el proceso PA*/

    if((g_pids[0] = fork()) == -1){
        fprintf(stderr, "[MANAGER] Error al crear el proceso PA\n");
        exit(EXIT_FAILURE); 
    }else if(g_pids[0] == 0){
        execl("PA", "PA", NULL); 
        fprintf(stderr, "[PA] Error al ejecutar el proceso\n");
        exit(EXIT_FAILURE); 
    }

    /*Esperamos que finalice el proceso PA*/

    waitpid(g_pids[0], &a_status, 0); 
    fprintf(g_fp, "Creación de los directorios finalizada.\n"); 

    printf("[MANAGER] Proceso PA %d finalizado\n", g_pids[0]); 

    /*Creamos la tuberia*/

    pipe(fd); 

    sprintf(wr_tub, "%d", fd[ESCRITURA]); 

    /*Creamos los procesos PB y PC*/

    for(int i = 0; i < 2; i++){
        if((g_pids[i + 1] = fork()) == -1){
            fprintf(stderr, "[MANAGER] Error al crear el proceso PB o PC\n"); 
            exit(EXIT_FAILURE); 
        }

        else if(g_pids[i + 1] == 0){
            if(i == 0){
                execl("PB", "PB", NULL); 
                fprintf(stderr, "[PB] Error al ejecutar el proceso\n");
                exit(EXIT_FAILURE); 
            }else{
                execl("PC", "PC", wr_tub, NULL); 
                fprintf(stderr, "[PC] Error al ejecutar el proceso\n");
                exit(EXIT_FAILURE); 
            }
        }
    }

    /*Esperamos que finalice el proceso PB*/

    waitpid(g_pids[1], &b_status, 0); 
    fprintf(g_fp, "Copia de los modelos de examen, finalizada.\n"); 

    printf("[MANAGER] Proceso PB %d finalizado\n", g_pids[1]);

    /*Esperamos que finalice el proceso PC*/

    waitpid(g_pids[2], &c_status, 0); 
    fprintf(g_fp, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada\n"); 

    printf("[MANAGER] Proceso PC %d finalizado\n", g_pids[2]);

    /*Comprobamos que se ha leido correctamente la nota media de la clase a través de la tuberia*/

    if(read(fd[LECTURA], buffer, sizeof(buffer)) < 0){
        fprintf(stderr, "[MANAGER] Error al leer la nota media de la tuberia\n"); 
        exit(EXIT_FAILURE); 
    }
    
    fprintf(g_fp, "La nota media de la clase es: %s\n", buffer); 
    printf("[MANAGER] La nota media se ha leido correctamente\n"); 

    fprintf(g_fp, "FIN DEL PROGRAMA\n"); 
    fclose(g_fp); 

    printf("[MANAGER] Finalizado\n"); 

    return EXIT_SUCCESS; 
}

void manejador(int signum){

    /*Interrumpimos los procesos PA, PB y PC*/
    for(int i = 0; i < 3; i++){
        kill(g_pids[i], SIGINT); 
    }

    printf("[MANAGER] Procesos finalizados\n"); 

    /*Creamos el proceso PD*/

    pid_t pid_d; 
    int d_status; 

    if((pid_d = fork()) == -1){
        fprintf(stderr, "[MANAGER] Error al crear el proceso PD\n");
        exit(EXIT_FAILURE); 
    } else if(pid_d == 0){
        execl("PD", "PD", NULL); 
        fprintf(stderr, "[PD] Error al ejecutar el proceso\n");
        exit(EXIT_FAILURE); 
    }

    /*Esperamos que finalice el proceso PD*/

    waitpid(pid_d, &d_status, 0); 
    fprintf(g_fp, "\n**[CTRL + C] USUARIO HA PRODUCIDO UNA INTERRUPCIÓN**\n");

    printf("[MANAGER] Proceso PD %d finalizado\n", pid_d); 
    fclose(g_fp); 
    
    printf("[MANAGER] Finalizado\n"); 

    exit(EXIT_FAILURE);

}
