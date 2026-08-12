#ifndef COLA_H
#define COLA_H

#define MAX_NOMBRE 50

//==============================
// ESTRUCTURA DEL PACIENTE
//==============================

typedef struct Paciente
{
    int turno;
    char nombre[MAX_NOMBRE];
    int urgencia;              // 0 = Normal | 1 = Urgencia

    struct Paciente *sig;

} Paciente;


//==============================
// ESTRUCTURA DE LA COLA
//==============================

typedef struct
{
    Paciente *frente;
    Paciente *final;

    int total;
    int siguienteTurno;

} Cola;


//==============================
// FUNCIONES PRINCIPALES
//==============================

void iniciarCola(Cola *cola);

void enqueue(Cola *cola, char nombre[]);

void enqueueUrgencia(Cola *cola, char nombre[]);

void dequeue(Cola *cola);

void mostrarCola(Cola *cola);

int buscarPaciente(Cola *cola, char nombre[]);

void liberarCola(Cola *cola);


//==============================
// ARCHIVOS
//==============================

void guardarPacientes(Cola *cola);

void cargarPacientes(Cola *cola);

void guardarHistorial(Paciente *paciente);


//==============================
// ESTADÍSTICAS
//==============================

void mostrarEstadisticas(Cola *cola);

#endif