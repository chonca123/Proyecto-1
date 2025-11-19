#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SistemaVotacion {
    struct NodoElectoral *elecciones;
    char convocatoria[1000];  
    struct Fecha FechaInicioCampana;
    struct Fecha FechaVotacion;
};


struct NodoElectoral {
    struct Elecciones *Elecciones;
    struct NodoElectoral *sig;
};

struct Elecciones {
    int NunmeroVuelta[1];
    struct TodosCandidatos *Candidatos;
    struct NodoMesa *ant;
};

struct TodosCandidatos {
    struct Candidato*Candidato;
};

struct Candidato{
    int Rut[12];
    char NombreCandidato[256];
    char Nacionalidad[25];
    int edad[3];
    char PartidoPolitico[50];
    char ProgramaGobierno[1000];
};

struct NodoMesa{
    struct Mesa*Mesa;
    struct NodoMesa*sig;
};

struct Mesa{
    char NombreVocales[216];
    int PadronMesa[20];
    struct NodoVotante*votantes;  
};

 struct NodoVotante{
    struct Votante *votantes;
    struct nodo_imputado *izq;
    struct nodo_imputado *der;
};

struct votante{
    struct Candidato*Candidatos;
    char Nombre[100];
    int Edad[3];
    char Nacionalidad[10];
    int RUT[10];
    char PadronMesa[20];
};

struct Fecha {
    int dia;
    int mes;
    int anio;
};



//FUNCIONES SISTEMA VOTACIONES 
struct SistemaVotacion *NuevaVotacion() {
    struct SistemaVotacion *Nueva;

    Nueva = malloc(sizeof(struct SistemaVotacion));
    if (Nueva == NULL)
        return NULL;

    Nueva->elecciones = NULL;

    Nueva->convocatoria[0] = '\0';

    Nueva->FechaInicioCampana.dia = 0;
    Nueva->FechaInicioCampana.mes = 0;
    Nueva->FechaInicioCampana.anio = 0;

    Nueva->FechaVotacion.dia = 0;
    Nueva->FechaVotacion.mes = 0;
    Nueva->FechaVotacion.anio = 0;

    return Nueva;
};

void IngresarDatosVotacion(struct SistemaVotacion *sistema) {
    printf("Ingrese mensaje de convocatoria:\n");
    scanf(" %[^\n]", sistema->convocatoria);  

    printf("Ingrese fecha inicio campaña (dia mes año): ");
    scanf("%d %d %d", 
        &sistema->FechaInicioCampana.dia,
        &sistema->FechaInicioCampana.mes,
        &sistema->FechaInicioCampana.anio
    );

    printf("Ingrese fecha de votación (dia mes año): ");
    scanf("%d %d %d", 
        &sistema->FechaVotacion.dia,
        &sistema->FechaVotacion.mes,
        &sistema->FechaVotacion.anio
    );
}






