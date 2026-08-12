#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

//========================================
// Inicializar la cola
//========================================

void iniciarCola(Cola *cola)
{
    cola->frente = NULL;
    cola->final = NULL;
    cola->total = 0;
    cola->siguienteTurno = 1;
}

//========================================
// Registrar paciente normal
//========================================

void enqueue(Cola *cola, char nombre[])
{
    Paciente *nuevo;

    nuevo = (Paciente *)malloc(sizeof(Paciente));

    if(nuevo == NULL)
    {
        printf("\nError al reservar memoria.\n");
        return;
    }

    nuevo->turno = cola->siguienteTurno++;

    strcpy(nuevo->nombre, nombre);

    nuevo->urgencia = 0;

    nuevo->sig = NULL;

    if(cola->frente == NULL)
    {
        cola->frente = nuevo;
        cola->final = nuevo;
    }
    else
    {
        cola->final->sig = nuevo;
        cola->final = nuevo;
    }

    cola->total++;

    printf("\n=====================================\n");
    printf(" Paciente registrado correctamente\n");
    printf(" Turno asignado: T-%03d\n", nuevo->turno);
    printf("=====================================\n");
}

//========================================
// Registrar paciente de urgencia
//========================================

void enqueueUrgencia(Cola *cola, char nombre[])
{
    Paciente *nuevo;

    nuevo = (Paciente *)malloc(sizeof(Paciente));

    if(nuevo == NULL)
    {
        printf("\nError al reservar memoria.\n");
        return;
    }

    nuevo->turno = cola->siguienteTurno++;

    strcpy(nuevo->nombre, nombre);

    nuevo->urgencia = 1;

    nuevo->sig = cola->frente;

    cola->frente = nuevo;

    if(cola->final == NULL)
        cola->final = nuevo;

    cola->total++;

    printf("\n=====================================\n");
    printf(" Paciente de URGENCIA registrado\n");
    printf(" Turno asignado: T-%03d\n", nuevo->turno);
    printf("=====================================\n");
}
//========================================
// Guardar historial
//========================================

void guardarHistorial(Paciente *paciente)
{
    FILE *archivo;

    archivo = fopen("historial.txt","a");

    if(archivo == NULL)
        return;

    fprintf(archivo,
            "T-%03d;%s;%s\n",
            paciente->turno,
            paciente->nombre,
            paciente->urgencia ? "URGENTE" : "NORMAL");

    fclose(archivo);
}

//========================================
// Atender paciente
//========================================

void dequeue(Cola *cola)
{
    if(cola->frente == NULL)
    {
        printf("\n=====================================\n");
        printf(" No hay pacientes en espera.\n");
        printf("=====================================\n");

        return;
    }

    Paciente *aux;

    aux = cola->frente;

    guardarHistorial(aux);

    printf("\n=====================================\n");
    printf("        PACIENTE ATENDIDO\n");
    printf("=====================================\n");
    printf("Turno : T-%03d\n", aux->turno);
    printf("Nombre: %s\n", aux->nombre);

    if(aux->urgencia)
        printf("Tipo  : URGENCIA\n");
    else
        printf("Tipo  : NORMAL\n");

    printf("=====================================\n");

    cola->frente = aux->sig;

    if(cola->frente == NULL)
        cola->final = NULL;

    free(aux);

    cola->total--;
}

//========================================
// Mostrar pacientes
//========================================

void mostrarCola(Cola *cola)
{
    if(cola->frente == NULL)
    {
        printf("\n===============================================\n");
        printf(" No hay pacientes registrados.\n");
        printf("===============================================\n");

        return;
    }

    Paciente *aux;

    aux = cola->frente;

    printf("\n");
    printf("====================================================================\n");
    printf("                     PACIENTES EN ESPERA\n");
    printf("====================================================================\n");

    printf("%-10s %-35s %-15s\n",
           "TURNO",
           "NOMBRE",
           "TIPO");

    printf("--------------------------------------------------------------------\n");

    while(aux != NULL)
    {

        printf("T-%03d      %-35s",
               aux->turno,
               aux->nombre);

        if(aux->urgencia)
            printf("URGENTE");
        else
            printf("NORMAL");

        printf("\n");

        aux = aux->sig;

    }

    printf("--------------------------------------------------------------------\n");
    printf("TOTAL DE PACIENTES: %d\n", cola->total);
    printf("====================================================================\n");

}
//========================================
// Buscar paciente
//========================================

int buscarPaciente(Cola *cola, char nombre[])
{
    Paciente *aux;

    int posicion = 1;

    aux = cola->frente;

    while(aux != NULL)
    {
        if(strcmp(aux->nombre, nombre) == 0)
        {
            return posicion;
        }

        posicion++;

        aux = aux->sig;
    }

    return -1;
}

//========================================
// Guardar pacientes
//========================================

void guardarPacientes(Cola *cola)
{
    FILE *archivo;

    Paciente *aux;

    archivo = fopen("pacientes.txt","w");

    if(archivo == NULL)
        return;

    aux = cola->frente;

    while(aux != NULL)
    {
        fprintf(archivo,
                "%d;%s;%d\n",
                aux->turno,
                aux->nombre,
                aux->urgencia);

        aux = aux->sig;
    }

    fclose(archivo);
}

//========================================
// Cargar pacientes
//========================================

void cargarPacientes(Cola *cola)
{
    FILE *archivo;

    archivo = fopen("pacientes.txt","r");

    if(archivo == NULL)
        return;

    Paciente *nuevo;

    int turno;

    int urgencia;

    char nombre[MAX_NOMBRE];

    while(fscanf(archivo,
                 "%d;%49[^;];%d\n",
                 &turno,
                 nombre,
                 &urgencia) == 3)
    {
        nuevo = (Paciente*)malloc(sizeof(Paciente));

        if(nuevo == NULL)
            break;

        nuevo->turno = turno;

        strcpy(nuevo->nombre, nombre);

        nuevo->urgencia = urgencia;

        nuevo->sig = NULL;

        if(cola->frente == NULL)
        {
            cola->frente = nuevo;
            cola->final = nuevo;
        }
        else
        {
            cola->final->sig = nuevo;
            cola->final = nuevo;
        }

        cola->total++;

        if(turno >= cola->siguienteTurno)
            cola->siguienteTurno = turno + 1;
    }

    fclose(archivo);
}
//========================================
// Mostrar estadísticas
//========================================

void mostrarEstadisticas(Cola *cola)
{
    Paciente *aux;

    int normales = 0;
    int urgencias = 0;

    aux = cola->frente;

    while(aux != NULL)
    {
        if(aux->urgencia)
            urgencias++;
        else
            normales++;

        aux = aux->sig;
    }

    printf("\n");
    printf("========================================================\n");
    printf("              ESTADISTICAS DEL SISTEMA\n");
    printf("========================================================\n");
    printf("Pacientes en espera : %d\n", cola->total);
    printf("Pacientes normales  : %d\n", normales);
    printf("Pacientes urgentes  : %d\n", urgencias);
    printf("Siguiente turno     : T-%03d\n", cola->siguienteTurno);
    printf("========================================================\n");
}

//========================================
// Liberar memoria
//========================================

void liberarCola(Cola *cola)
{
    Paciente *aux;

    while(cola->frente != NULL)
    {
        aux = cola->frente;

        cola->frente = cola->frente->sig;

        free(aux);
    }

    cola->frente = NULL;
    cola->final = NULL;
    cola->total = 0;
}