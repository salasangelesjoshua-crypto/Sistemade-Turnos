#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cola.h"

//=========================================
// Mostrar encabezado
//=========================================

void encabezado(Cola *cola)
{
    time_t t;
    struct tm *fecha;

    t = time(NULL);
    fecha = localtime(&t);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("=============================================================\n");
    printf("        SISTEMA DE TURNOS DEL CONSULTORIO MEDICO\n");
    printf("=============================================================\n");

    printf("Fecha: %02d/%02d/%04d",
           fecha->tm_mday,
           fecha->tm_mon + 1,
           fecha->tm_year + 1900);

    printf("          Hora: %02d:%02d\n",
           fecha->tm_hour,
           fecha->tm_min);

    printf("Pacientes en espera: %d\n", cola->total);

    printf("=============================================================\n\n");
}

//=========================================
// Menú principal
//=========================================

void menu()
{
    printf("1. Registrar paciente\n");
    printf("2. Registrar paciente de urgencia\n");
    printf("3. Atender paciente\n");
    printf("4. Mostrar pacientes\n");
    printf("5. Buscar paciente\n");
    printf("6. Estadisticas\n");
    printf("7. Salir\n");

    printf("\nSeleccione una opcion: ");
}

//=========================================
// Programa principal
//=========================================

int main()
{

    Cola cola;

    iniciarCola(&cola);

    cargarPacientes(&cola);

    int opcion;

    int posicion;

    char nombre[MAX_NOMBRE];

    do
    {

        encabezado(&cola);

        menu();

        scanf("%d",&opcion);

        getchar();

        switch(opcion)
        {

                        case 1:

                printf("\nNombre del paciente: ");

                fgets(nombre, MAX_NOMBRE, stdin);

                nombre[strcspn(nombre, "\n")] = '\0';

                if(strlen(nombre) == 0)
                {
                    printf("\nEl nombre no puede estar vacio.\n");
                    break;
                }

                enqueue(&cola, nombre);

                break;


            case 2:

                printf("\nNombre del paciente de urgencia: ");

                fgets(nombre, MAX_NOMBRE, stdin);

                nombre[strcspn(nombre, "\n")] = '\0';

                if(strlen(nombre) == 0)
                {
                    printf("\nEl nombre no puede estar vacio.\n");
                    break;
                }

                enqueueUrgencia(&cola, nombre);

                break;


            case 3:

                dequeue(&cola);

                break;


            case 4:

                mostrarCola(&cola);

                break;


            case 5:

                printf("\nNombre del paciente a buscar: ");

                fgets(nombre, MAX_NOMBRE, stdin);

                nombre[strcspn(nombre, "\n")] = '\0';

                posicion = buscarPaciente(&cola, nombre);

                if(posicion == -1)
                {
                    printf("\nPaciente no encontrado.\n");
                }
                else
                {
                    printf("\n=====================================\n");
                    printf("Paciente encontrado.\n");
                    printf("Posicion en la fila: %d\n", posicion);
                    printf("=====================================\n");
                }

                break;


            case 6:

                mostrarEstadisticas(&cola);

                break;
                            case 7:

                printf("\nGuardando informacion...\n");

                guardarPacientes(&cola);

                printf("Informacion guardada correctamente.\n");

                break;


            default:

                printf("\n=====================================\n");
                printf("Opcion invalida.\n");
                printf("=====================================\n");

        }

        if(opcion != 7)
        {
            printf("\nPresione ENTER para continuar...");
            getchar();
        }

    } while(opcion != 7);

    guardarPacientes(&cola);

    liberarCola(&cola);

    printf("\n===============================================\n");
    printf(" Gracias por utilizar el Sistema de Turnos\n");
    printf("===============================================\n");

    return 0;
}